#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLModel.h"
#include "HGeometryEngine.h"
#include <QtCore/QRandomGenerator>
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

int HLearnGLFW::testSSAO()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/ssao_geometry.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/ssao_geometry.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/ssao.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/ssao_lighting.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/ssao.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/ssao.fs");
    auto shader4 = new HOpenGLShaderProgram(this);
    shader4->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/ssao.vs");
    shader4->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/ssao_blur.fs");

    // load models
    auto cyborg = new HOpenGLModel(this);
    cyborg->load("objects\\cyborg\\cyborg.obj");

    // configure g-buffer framebuffer
    unsigned int gbuffer, rboDepth, gPosition, gNormal, gAlbedo;
    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    gPosition = HOpenGLHelper::createTextureF(d_ptr->width, d_ptr->height);
    gNormal = HOpenGLHelper::createTextureF(d_ptr->width, d_ptr->height);
    gAlbedo = HOpenGLHelper::createTexture(d_ptr->width, d_ptr->height);
    rboDepth = HOpenGLHelper::createRenderDepth(d_ptr->width, d_ptr->height);
    glGenFramebuffers(1, &gbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    glDrawBuffers(3, attachments);
    // attach depth buffer (renderbuffer)
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "Framebuffer not complete!";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // create framebuffer to hold SSAO processing stage
    unsigned int ssaoFbo, ssaoBlurFbo;
    unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
    glGenFramebuffers(1, &ssaoFbo);
    glGenFramebuffers(1, &ssaoBlurFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoFbo);
    // SSAO color buffer
    glGenTextures(1, &ssaoColorBuffer);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, d_ptr->width, d_ptr->height, 0, GL_RED, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "Framebuffer not complete!";
    // and blur stage
    glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFbo);
    glGenTextures(1, &ssaoColorBufferBlur);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, d_ptr->width, d_ptr->height, 0, GL_RED, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "Framebuffer not complete!";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // generate sample kernel
    QRandomGenerator random;
    QVector<QVector3D> ssaoKernel, ssaoNoise;
    for (int i = 0; i < 64; ++i)
    {
        QVector3D sample(random.generateDouble() * 2.0 - 1.0, random.generateDouble() * 2.0 - 1.0, random.generateDouble());
        sample.normalize();
        sample *= random.generateDouble();
        float scale = i / 64.0;

        // scale samples s.t. they're more aligned to center of kernel
        scale = 0.1 + scale * scale * 0.9;
        sample *= scale;
        ssaoKernel << sample;
    }
    // generate noise texture
    for (int i = 0; i < 16; i++)
        ssaoNoise << QVector3D(random.generateDouble() * 2.0 - 1.0, random.generateDouble() * 2.0 - 1.0, 0.0f);// rotate around z-axis (in tangent space)

    unsigned int noiseTexture;
    glGenTextures(1, &noiseTexture);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // lighting info
    QVector3D lightPos(2.0, 4.0, -2.0);
    QVector3D lightColor(0.2, 0.2, 0.7);

    // shader configuration
    shader2->bind();
    shader2->setUniformValue("gPosition", 0);
    shader2->setUniformValue("gNormal", 1);
    shader2->setUniformValue("gAlbedo", 2);
    shader2->setUniformValue("ssao", 3);
    shader3->bind();
    shader3->setUniformValue("gPosition", 0);
    shader3->setUniformValue("gNormal", 1);
    shader3->setUniformValue("texNoise", 2);
    shader4->bind();
    shader4->setUniformValue("ssaoInput", 0);

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
        model.translate(0.0, 7.0f, 0.0f);
        model.scale(7.5f, 7.5f, 7.5f);
        glBindFramebuffer(GL_FRAMEBUFFER, gbuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("model", model);
        shader1->setUniformValue("invertedNormals", 1);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.rotate(-90.0f, 1.0, 0.0, 0.0);
        model.scale(1.0f);
        shader1->setUniformValue("model", model);
        shader1->setUniformValue("invertedNormals", 0);
        cyborg->draw(shader1);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. generate SSAO texture
        glBindFramebuffer(GL_FRAMEBUFFER, ssaoFbo);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, noiseTexture);
        shader3->bind();
        shader3->setUniformValue("projection", projection);
        for (int i = 0; i < 64; ++i)
            shader3->setUniformValue(tr("samples[%1]").arg(i).toStdString().c_str(), ssaoKernel[i]);
        d_ptr->engine->renderScreen(shader3);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 3. blur SSAO texture to remove noise
        glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFbo);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
        shader4->bind();
        d_ptr->engine->renderScreen(shader4);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 4. lighting pass: traditional deferred Blinn-Phong lighting with added screen-space ambient occlusion
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedo);
        glActiveTexture(GL_TEXTURE3); // add extra SSAO texture to lighting pass
        glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
        const float linear    = 0.09;
        const float quadratic = 0.032;
        auto lightPosView = QVector3D(camera->viewMatrix() * QVector4D(lightPos, 1.0));
        shader2->bind();
        shader2->setUniformValue("light.Position", lightPosView);
        shader2->setUniformValue("light.Color", lightColor);
        shader2->setUniformValue("light.Linear", linear);
        shader2->setUniformValue("light.Quadratic", quadratic);
        d_ptr->engine->renderScreen(shader2);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            glfwSwapBuffers(d_ptr->window);
            glfwPollEvents();
        }

//    // configure g-buffer framebuffer
//    unsigned int gBuffer;
//    glGenFramebuffers(1, &gBuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//    unsigned int gPosition, gNormal, gAlbedo;
//    // position color buffer
//    glGenTextures(1, &gPosition);
//    glBindTexture(GL_TEXTURE_2D, gPosition);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, d_ptr->width, d_ptr->height, 0, GL_RGBA, GL_FLOAT, nullptr);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
//    // normal color buffer
//    glGenTextures(1, &gNormal);
//    glBindTexture(GL_TEXTURE_2D, gNormal);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, d_ptr->width, d_ptr->height, 0, GL_RGBA, GL_FLOAT, nullptr);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
//    // color + specular color buffer
//    glGenTextures(1, &gAlbedo);
//    glBindTexture(GL_TEXTURE_2D, gAlbedo);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d_ptr->width, d_ptr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
//    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
//    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
//    glDrawBuffers(3, attachments);
//    // create and attach depth buffer (renderbuffer)
//    unsigned int rboDepth;
//    glGenRenderbuffers(1, &rboDepth);
//    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, d_ptr->width, d_ptr->height);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
//    // finally check if framebuffer is complete
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        qDebug() << "Framebuffer not complete!";
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);

//    // also create framebuffer to hold SSAO processing stage
//    unsigned int ssaoFBO, ssaoBlurFBO;
//    glGenFramebuffers(1, &ssaoFBO);
//    glGenFramebuffers(1, &ssaoBlurFBO);
//    glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
//    unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
//    // SSAO color buffer
//    glGenTextures(1, &ssaoColorBuffer);
//    glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, d_ptr->width, d_ptr->height, 0, GL_RED, GL_FLOAT, nullptr);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        qDebug() << "Framebuffer not complete!";
//    // and blur stage
//    glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
//    glGenTextures(1, &ssaoColorBufferBlur);
//    glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, d_ptr->width, d_ptr->height, 0, GL_RED, GL_FLOAT, nullptr);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        qDebug() << "Framebuffer not complete!";
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);


//    // generate sample kernel
//    QRandomGenerator random;
//    QVector<QVector3D> ssaoKernel, ssaoNoise;
//    for (int i = 0; i < 64; ++i)
//    {
//        QVector3D sample(random.generateDouble() * 2.0 - 1.0, random.generateDouble() * 2.0 - 1.0, random.generateDouble());
//        sample.normalize();
//        sample *= random.generateDouble();
//        float scale = i / 64.0;

//        // scale samples s.t. they're more aligned to center of kernel
//        scale = 0.1 + scale * scale * 0.9;
//        sample *= scale;
//        ssaoKernel << sample;
//    }
//    // generate noise texture
//    for (int i = 0; i < 16; i++)
//        ssaoNoise << QVector3D(random.generateDouble() * 2.0 - 1.0, random.generateDouble() * 2.0 - 1.0, 0.0f);// rotate around z-axis (in tangent space)

//    unsigned int noiseTexture;
//    glGenTextures(1, &noiseTexture);
//    glBindTexture(GL_TEXTURE_2D, noiseTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//    // lighting info
//    QVector3D lightPos(2.0, 4.0, -2.0);
//    QVector3D lightColor(0.2, 0.2, 0.7);

//    // shader configuration
//    shader2->bind();
//    shader2->setUniformValue("gPosition", 0);
//    shader2->setUniformValue("gNormal", 1);
//    shader2->setUniformValue("gAlbedo", 2);
//    shader2->setUniformValue("ssao", 3);
//    shader3->bind();
//    shader3->setUniformValue("gPosition", 0);
//    shader3->setUniformValue("gNormal", 1);
//    shader3->setUniformValue("texNoise", 2);
//    shader4->bind();
//    shader4->setUniformValue("ssaoInput", 0);

//    // render loop
//    while (!glfwWindowShouldClose(d_ptr->window))
//    {
//        // per-frame time logic
//        perFrameTime();
//        // input
//        processInput(d_ptr->window);
//        // render
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        // 1. geometry pass: render scene's geometry/color data into gbuffer
//        QMatrix4x4 projection, view, model;
//        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
//        view = camera->viewMatrix();
//        model.translate(0.0, 7.0f, 0.0f);
//        model.scale(7.5f);
//        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        shader1->bind();
//        shader1->setUniformValue("projection", projection);
//        shader1->setUniformValue("view", view);
//        shader1->setUniformValue("model", model);
//        shader1->setUniformValue("invertedNormals", 1);
//        renderCube();
//        model.setToIdentity();
//        model.translate(0.0f, 0.5f, 0.0);
//        model.rotate(-90.0f, 1.0, 0.0, 0.0);
//        model.scale(1.0f);
//        shader1->setUniformValue("model", model);
//        shader1->setUniformValue("invertedNormals", 0);
//        backpack->draw(shader1);
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);

//        // 2. generate SSAO texture
//        glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
//        glClear(GL_COLOR_BUFFER_BIT);
//        shader3->bind();
//        shader3->setUniformValue("projection", projection);
//        for (int i = 0; i < 64; ++i)
//            shader3->setUniformValue(tr("samples[%1]").arg(i).toStdString().c_str(), ssaoKernel[i]);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, gPosition);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, gNormal);
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, noiseTexture);
//        renderQuad();
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);

//        // 3. blur SSAO texture to remove noise
//        glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
//        glClear(GL_COLOR_BUFFER_BIT);
//        shader4->bind();
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
//        renderQuad();
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);

//        // 4. lighting pass: traditional deferred Blinn-Phong lighting with added screen-space ambient occlusion
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        const float linear    = 0.09;
//        const float quadratic = 0.032;
//        auto lightPosView = QVector3D(camera->viewMatrix() * QVector4D(lightPos, 1.0));
//        shader2->bind();
//        shader2->setUniformValue("light.Position", lightPosView);
//        shader2->setUniformValue("light.Color", lightColor);
//        shader2->setUniformValue("light.Linear", linear);
//        shader2->setUniformValue("light.Quadratic", quadratic);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, gPosition);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, gNormal);
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, gAlbedo);
//        glActiveTexture(GL_TEXTURE3); // add extra SSAO texture to lighting pass
//        glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
//        renderQuad();

//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        glfwSwapBuffers(d_ptr->window);
//        glfwPollEvents();
//    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE
