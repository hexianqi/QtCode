#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

int HLearnGLFW::testShadowMappingDepth()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_mapping_depth.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_mapping_depth.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/debug_quad_depth.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/debug_quad_depth.fs");

    // configure depth map FBO
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    auto texturebuffer = HOpenGLHelper::createTextureDepth(SHADOW_WIDTH, SHADOW_HEIGHT);
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texturebuffer, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");
    // shader configuration
    shader2->bind();
    shader2->setUniformValue("texture1", 0);

    QVector3D lightPos(-2.0f, 4.0f, -1.0f);

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
        // 1. render depth of scene to texture (from light's perspective)
        QMatrix4x4 lightProjection, lightView, lightSpaceMatrix;
        auto nearPlane = 1.0f;
        auto farPlane = 7.5f;
        lightProjection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
        lightView.lookAt(lightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        shader1->bind();
        shader1->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        d_ptr->engine->renderScene(shader1);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // reset viewport
        glViewport(0, 0, d_ptr->width, d_ptr->height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // render Depth map to quad for visual debugging
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texturebuffer);
        shader2->bind();
        shader2->setUniformValue("nearPlane", nearPlane);
        shader2->setUniformValue("farPlane", farPlane);
        d_ptr->engine->renderScreen(shader2);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testShadowMappingBase()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_mapping.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_mapping.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_mapping_depth.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_mapping_depth.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/debug_quad_depth.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/debug_quad_depth.fs");

    // configure depth map FBO
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    auto texturebuffer = HOpenGLHelper::createTextureDepth(SHADOW_WIDTH, SHADOW_HEIGHT);
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texturebuffer, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");

    // shader configuration
    shader1->bind();
    shader1->setUniformValue("diffuseTexture", 0);
    shader1->setUniformValue("shadowTexture", 1);
    shader3->bind();
    shader3->setUniformValue("texture1", 0);

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
        // 1. render depth of scene to texture (from light's perspective)
        QMatrix4x4 lightProjection, lightView, lightSpaceMatrix;
        auto nearPlane = 1.0f;
        auto farPlane = 7.5f;
        auto lightPos = this->lightPos();
        lightProjection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
        lightView.lookAt(lightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        shader2->bind();
        shader2->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        d_ptr->engine->renderScene(shader2);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // reset viewport
        glViewport(0, 0, d_ptr->width, d_ptr->height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2. render scene as normal using the generated depth/shadow map
        QMatrix4x4 projection, view;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("viewPos", camera->position());
        shader1->setUniformValue("lightPos", lightPos);
        shader1->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texturebuffer);
        d_ptr->engine->renderScene(shader1);

//        // render Depth map to quad for visual debugging
//        shader3->bind();
//        shader3->setUniformValue("nearPlane", nearPlane);
//        shader3->setUniformValue("farPlane", farPlane);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texturebuffer);
//        d_ptr->engine->renderScreen(shader3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testShadowMapping()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_mapping2.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_mapping2.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_mapping_depth.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_mapping_depth.fs");

    // configure depth map FBO
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    auto texturebuffer = HOpenGLHelper::createTextureDepth(SHADOW_WIDTH, SHADOW_HEIGHT);
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texturebuffer, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");

    // shader configuration
    shader1->bind();
    shader1->setUniformValue("diffuseTexture", 0);
    shader1->setUniformValue("shadowTexture", 1);

    QVector3D lightPos(-2.0f, 4.0f, -1.0f);

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
        // 1. render depth of scene to texture (from light's perspective)
        QMatrix4x4 lightProjection, lightView, lightSpaceMatrix;
        auto nearPlane = 1.0f;
        auto farPlane = 7.5f;

        lightProjection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
        lightView.lookAt(lightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        shader2->bind();
        shader2->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        d_ptr->engine->renderScene(shader2);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // reset viewport
        glViewport(0, 0, d_ptr->width, d_ptr->height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2. render scene as normal using the generated depth/shadow map
        QMatrix4x4 projection, view;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("viewPos", camera->position());
        shader1->setUniformValue("lightPos", lightPos);
        shader1->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texturebuffer);
        d_ptr->engine->renderScene(shader1);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testShadowPoint()
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
    glEnable(GL_CULL_FACE);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_point2.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_point2.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_point_depth.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_point_depth.fs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Geometry,   ":/glsl/shadow_point_depth.gs");

    // configure depth map FBO
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    auto texturebuffer = HOpenGLHelper::createCubemapDepth(SHADOW_WIDTH, SHADOW_HEIGHT);
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texturebuffer, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");

    // shader configuration
    shader1->bind();
    shader1->setUniformValue("diffuseTexture", 0);
    shader1->setUniformValue("shadowTexture", 1);

    QVector3D lightPos;

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // per-frame time logic
        perFrameTime();
        // input
        processInput(d_ptr->window);
        // move light position over time
        lightPos.setZ(sin(glfwGetTime() * 0.5) * 3.0);
        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 0. create depth cubemap transformation matrices
        QMatrix4x4 shadowProjection;
        QVector<QMatrix4x4> shadowView(6), shadowTransforms(6);
        auto nearPlane = 1.0f;
        auto farPlane = 25.0f;
        shadowProjection.perspective(90.0f, 1.0 * SHADOW_WIDTH / SHADOW_HEIGHT, nearPlane, farPlane);
        shadowView[0].lookAt(lightPos, lightPos + QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
        shadowView[1].lookAt(lightPos, lightPos + QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
        shadowView[2].lookAt(lightPos, lightPos + QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
        shadowView[3].lookAt(lightPos, lightPos + QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
        shadowView[4].lookAt(lightPos, lightPos + QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
        shadowView[5].lookAt(lightPos, lightPos + QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));
        for (int i = 0; i < 6; i++)
            shadowTransforms[i] = shadowProjection * shadowView[i];
        // 1. render scene to depth cubemap
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClear(GL_DEPTH_BUFFER_BIT);
        shader2->bind();
        for (int i = 0; i < 6; ++i)
            shader2->setUniformValue(QString("shadowMatrices[%1]").arg(i).toStdString().c_str(), shadowTransforms[i]);
        shader2->setUniformValue("farPlane", farPlane);
        shader2->setUniformValue("lightPos", lightPos);
        d_ptr->engine->renderRoom(shader2);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. render scene as normal using the generated depth/shadow map
        glViewport(0, 0, d_ptr->width, d_ptr->height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        QMatrix4x4 projection, view;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("lightPos", lightPos);
        shader1->setUniformValue("viewPos", camera->position());
        shader1->setUniformValue("shadows", d_ptr->shadows);
        shader1->setUniformValue("farPlane", farPlane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texturebuffer);
        d_ptr->engine->renderRoom(shader1);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE
