#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testBloom()
{
    initGlfw();
    if (!createWindow())
    {
        glfwTerminate();
        return -1;
    }
    if (!initFlad())
        return -1;

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/bloom.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/bloom.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/bloom.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/bloom_light.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/gaussian_blur.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/gaussian_blur.fs");
    auto shader4 = new HOpenGLShaderProgram(this);
    shader4->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/bloom_final.vs");
    shader4->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/bloom_final.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/wood.png", true);
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/container.png", true);

    // configure (floating point) framebuffers
    unsigned int hdrFBO, rboDepth, colorBuffers[2];
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    colorBuffers[0] = HOpenGLHelper::createTextureF(d_ptr->width, d_ptr->height);
    colorBuffers[1] = HOpenGLHelper::createTextureF(d_ptr->width, d_ptr->height);
    rboDepth = HOpenGLHelper::createRenderDepth(d_ptr->width, d_ptr->height);
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffers[0], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, colorBuffers[1], 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    glDrawBuffers(2, attachments);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "Framebuffer not complete!";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ping-pong-framebuffer for blurring
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];
    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        pingpongColorbuffers[i] = HOpenGLHelper::createTextureF(d_ptr->width, d_ptr->height);
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
        // also check if framebuffers are complete (no need for depth buffer)
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            qDebug() << "Framebuffer not complete!";
    }

    // lighting info
    QVector<QVector3D> lightPositions, lightColors;
    lightPositions << QVector3D( 0.0f, 0.5f,  1.5f); // back light
    lightPositions << QVector3D(-4.0f, 0.5f, -3.0f);
    lightPositions << QVector3D( 3.0f, 0.5f,  1.0f);
    lightPositions << QVector3D(-0.8f, 2.4f, -1.0f);
    lightColors << QVector3D( 5.0f, 5.0f,  5.0f);
    lightColors << QVector3D(10.0f, 0.0f,  0.0f);
    lightColors << QVector3D( 0.0f, 0.0f, 15.0f);
    lightColors << QVector3D( 0.0f, 5.0f, 0.0f);

    // shader configuration
    shader1->bind();
    shader1->setUniformValue("texture1", 0);
    shader3->bind();
    shader3->setUniformValue("texture1", 0);
    shader4->bind();
    shader4->setUniformValue("scene", 0);
    shader4->setUniformValue("bloomBlur", 1);

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // per-frame time logic
        perFrameTime();
        // input
        processInput(d_ptr->window);
        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1. render scene into floating point framebuffer
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // create one large cube that acts as the floor
        model.translate(0.0f, -1.0f, 0.0f);
        model.scale(25.0f, 2.0f, 25.0f);
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("viewPos", camera->position());
        shader1->setUniformValue("model", model);
        for (int i = 0; i < lightPositions.size(); i++)
        {
            shader1->setUniformValue(tr("lights[%1].Position").arg(i).toStdString().c_str(), lightPositions[i]);
            shader1->setUniformValue(tr("lights[%1].Color").arg(i).toStdString().c_str(), lightColors[i]);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        d_ptr->engine->renderCube(shader1);
        // then create multiple cubes as the scenery
        glBindTexture(GL_TEXTURE_2D, texture2);
        model.setToIdentity();
        model.translate(0.0f, 1.5f, 0.0);
        model.scale(0.5f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.translate(2.0f, 0.0f, 1.0);
        model.scale(0.5f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.translate(-1.0f, -1.0f, 2.0);
        model.rotate(60.0f, 1.0, 0.0, 1.0);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.translate(0.0f, 2.7f, 4.0);
        model.rotate(23.0f, 1.0, 0.0, 1.0);
        model.scale(1.25);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.translate(-2.0f, 1.0f, -3.0);
        model.rotate(124.0f, 1.0, 0.0, 1.0);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.translate(-3.0f, 0.0f, 0.0);
        model.scale(0.5f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        // finally show all the light sources as bright cubes
        shader2->bind();
        shader2->setUniformValue("projection", projection);
        shader2->setUniformValue("view", view);
        for (int i = 0; i < lightPositions.size(); i++)
        {
            model.setToIdentity();
            model.translate(lightPositions[i]);
            model.scale(0.25f);
            shader2->setUniformValue("model", model);
            shader2->setUniformValue("lightColor", lightColors[i]);
            d_ptr->engine->renderSphere(shader2);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. blur bright fragments with two-pass Gaussian Blur
        bool horizontal = true, first_iteration = true;
        int amount = 10;
        shader3->bind();
        for (int i = 0; i < amount; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            shader3->setUniformValue("horizontal", horizontal);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
            d_ptr->engine->renderScreen(shader3);
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
        shader4->bind();
        shader4->setUniformValue("bloom", d_ptr->bloom);
        shader4->setUniformValue("exposure", d_ptr->exposure);
        d_ptr->engine->renderScreen(shader4);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
