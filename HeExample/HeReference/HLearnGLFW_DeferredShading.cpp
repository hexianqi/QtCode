#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLModel.h"
#include <QtCore/QRandomGenerator>
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testDeferredShading()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/g_buffer.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/g_buffer.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/deferred_shading.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/deferred_shading.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/deferred_light_box.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/deferred_light_box.fs");
    // load models
    auto backpack = new HOpenGLModel(this);
    backpack->load("objects\\backpack\\backpack.obj");
    QVector<QVector3D> objectPositions;
    objectPositions << QVector3D(-3.0,  -0.5, -3.0);
    objectPositions << QVector3D( 0.0,  -0.5, -3.0);
    objectPositions << QVector3D( 3.0,  -0.5, -3.0);
    objectPositions << QVector3D(-3.0,  -0.5,  0.0);
    objectPositions << QVector3D( 0.0,  -0.5,  0.0);
    objectPositions << QVector3D( 3.0,  -0.5,  0.0);
    objectPositions << QVector3D(-3.0,  -0.5,  3.0);
    objectPositions << QVector3D( 0.0,  -0.5,  3.0);
    objectPositions << QVector3D( 3.0,  -0.5,  3.0);

    // lighting info
    const unsigned int NR_LIGHTS = 32;
    QVector<QVector3D> lightPositions, lightColors;
    QRandomGenerator random(13);
    for (unsigned int i = 0; i < NR_LIGHTS; i++)
    {
        float xPos = random.generateDouble() * 6.0 - 3.0;
        float yPos = random.generateDouble() * 6.0 - 4.0;
        float zPos = random.generateDouble() * 6.0 - 3.0;
        lightPositions << QVector3D(xPos, yPos, zPos);
        float rColor = random.generateDouble() * 0.5 + 0.5;
        float gColor = random.generateDouble() * 0.5 + 0.5;
        float bColor = random.generateDouble() * 0.5 + 0.5;
        lightColors << QVector3D(rColor, gColor, bColor);
    }

    // configure g-buffer framebuffer
    // ------------------------------
    unsigned int gBuffer;
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    unsigned int gPosition, gNormal, gAlbedoSpec;
    // position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, d_ptr->width, d_ptr->height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, d_ptr->width, d_ptr->height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d_ptr->width, d_ptr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);
    // create and attach depth buffer (renderbuffer)
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, d_ptr->width, d_ptr->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "Framebuffer not complete!";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // shader configuration
    shader2->bind();
    shader2->setUniformValue("gPosition", 0);
    shader2->setUniformValue("gNormal", 1);
    shader2->setUniformValue("gAlbedoSpec", 2);

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

        // 1. geometry pass: render scene's geometry/color data into gbuffer
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        for (int i = 0; i < objectPositions.size(); i++)
        {
            model.setToIdentity();
            model.translate(objectPositions[i]);
            model.scale(0.5f);
            shader1->setUniformValue("model", model);
            backpack->draw(shader1);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        shader2->bind();
        shader2->setUniformValue("viewPos", camera->position());
        for (int i = 0; i < lightPositions.size(); i++)
        {
            const float constant = 1.0;
            const float linear = 0.7;
            const float quadratic = 1.8;
            float maxBrightness = qMax(qMax(lightColors[i].x(), lightColors[i].y()), lightColors[i].z());
            float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
            shader2->setUniformValue(tr("lights[%1].Position").arg(i).toStdString().c_str(), lightPositions[i]);
            shader2->setUniformValue(tr("lights[%1].Color").arg(i).toStdString().c_str(), lightColors[i]);
            shader2->setUniformValue(tr("lights[%1].Linear").arg(i).toStdString().c_str(), linear);
            shader2->setUniformValue(tr("lights[%1].Quadratic").arg(i).toStdString().c_str(), quadratic);
            shader2->setUniformValue(tr("lights[%1].Radius").arg(i).toStdString().c_str(), radius);
        }
        renderQuad();

        // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, d_ptr->width, d_ptr->height, 0, 0, d_ptr->width, d_ptr->height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 3. render lights on top of scene
        shader3->bind();
        shader3->setUniformValue("projection", projection);
        shader3->setUniformValue("view", view);
        for (int i = 0; i < lightPositions.size(); i++)
        {
            model.setToIdentity();
            model.translate(lightPositions[i]);
            model.scale(0.125f);
            shader3->setUniformValue("model", model);
            shader3->setUniformValue("lightColor", lightColors[i]);
            renderCube();
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
