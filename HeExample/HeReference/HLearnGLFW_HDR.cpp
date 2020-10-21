#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testHDR()
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
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/lighting.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/lighting.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/hdr.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/hdr.fs");

    // configure floating point framebuffer
    unsigned int FBO, RBO, colorBuffer;
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, d_ptr->width, d_ptr->height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, d_ptr->width, d_ptr->height);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "Framebuffer not complete!";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // lighting info
    QVector<QVector3D> lightPositions, lightColors;
    lightPositions << QVector3D( 0.0f,  0.0f, 49.5f); // back light
    lightPositions << QVector3D(-1.4f, -1.9f, 9.0f);
    lightPositions << QVector3D( 0.0f, -1.8f, 4.0f);
    lightPositions << QVector3D( 0.8f, -1.7f, 6.0f);
    lightColors << QVector3D(200.0f, 200.0f, 200.0f);
    lightColors << QVector3D(0.1f, 0.0f, 0.0f);
    lightColors << QVector3D(0.0f, 0.0f, 0.2f);
    lightColors << QVector3D(0.0f, 0.1f, 0.0f);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png", true);
    // shader configuration
    shader1->bind();
    shader1->setUniformValue("diffuseTexture", 0);
    shader2->bind();
    shader2->setUniformValue("hdrBuffer", 0);

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

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("viewPos", camera->position());
        shader1->setUniformValue("model", model);
        shader1->setUniformValue("inverse_normals", true);
        for (int i = 0; i < lightPositions.size(); i++)
        {
            shader1->setUniformValue(tr("lights[%1].Position").arg(i).toStdString().c_str(), lightPositions[i]);
            shader1->setUniformValue(tr("lights[%1].Color").arg(i).toStdString().c_str(), lightColors[i]);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        renderCube();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader2->bind();
        shader2->setUniformValue("hdr", d_ptr->hdr);
        shader2->setUniformValue("exposure", d_ptr->exposure);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorBuffer);
        renderQuad();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
