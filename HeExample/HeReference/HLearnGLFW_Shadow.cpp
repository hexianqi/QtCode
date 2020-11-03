#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

// renders the 3D scene
void HLearnGLFW::renderScene(HOpenGLShaderProgram *shader, int type)
{
    if (d_ptr->planeVAO == 0)
    {
        unsigned int VBO;
        glGenVertexArrays(1, &d_ptr->planeVAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(d_ptr->planeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, d_ptr->planePositionSize + d_ptr->planeNormalSize + d_ptr->planeTextureSize, nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->planePositionSize, d_ptr->planePosition.data());
        glBufferSubData(GL_ARRAY_BUFFER, d_ptr->planePositionSize, d_ptr->planeNormalSize, d_ptr->planeNormal.data());
        glBufferSubData(GL_ARRAY_BUFFER, d_ptr->planePositionSize + d_ptr->planeNormalSize, d_ptr->planeTextureSize, d_ptr->planeTexture.data());
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(d_ptr->planePositionSize));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->planePositionSize + d_ptr->planeNormalSize));
        glBindVertexArray(0);
    }

    QMatrix4x4 model;
    if (type == 0) // floor
    {
        shader->setUniformValue("model", model);
        glBindVertexArray(d_ptr->planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    if (type == 1) // room cube
    {
        model.scale(5.0f);
        shader->setUniformValue("model", model);
        glDisable(GL_CULL_FACE); // note that we disable culling here since we render 'inside' the cube instead of the usual 'outside' which throws off the normal culling methods.
        shader->setUniformValue("reverse_normals", 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
        renderCube();
        shader->setUniformValue("reverse_normals", 0); // and of course disable it
        glEnable(GL_CULL_FACE);
    }

    // cubes
    model.setToIdentity();
    model.translate(0.0f, 1.5f, 0.0f);
    model.scale(0.5f);
    shader->setUniformValue("model", model);
    renderCube();
    model.setToIdentity();
    model.translate(2.0f, 0.0f, 1.0f);
    model.scale(1.0f);
    shader->setUniformValue("model", model);
    renderCube();
    model.setToIdentity();
    model.translate(-1.0f, 0.0f, 2.0f);
    model.rotate(60.0f, QVector3D(1.0, 0.0, 1.0).normalized());
    model.scale(0.25f);
    shader->setUniformValue("model", model);
    renderCube();
}

void HLearnGLFW::renderCube()
{
    // initialize (if necessary)
    if (d_ptr->cubeVAO == 0)
    {
        unsigned int VBO;
        glGenVertexArrays(1, &d_ptr->cubeVAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize + d_ptr->cubeTextureSize, nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->cubePositionSize, d_ptr->cubePosition.data());
        glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubeNormalSize, d_ptr->cubeNormal.data());
        glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize, d_ptr->cubeTextureSize, d_ptr->cubeTexture.data());
        glBindVertexArray(d_ptr->cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(d_ptr->cubePositionSize));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->cubePositionSize + d_ptr->cubeNormalSize));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(d_ptr->cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void HLearnGLFW::renderQuad()
{
    if (d_ptr->quadVAO == 0)
    {
        unsigned int VBO;
        glGenVertexArrays(1, &d_ptr->quadVAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(d_ptr->quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, d_ptr->quadPositionSize + d_ptr->quadTextureSize, nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->quadPositionSize, d_ptr->quadPosition.data());
        glBufferSubData(GL_ARRAY_BUFFER, d_ptr->quadPositionSize, d_ptr->quadTextureSize, d_ptr->quadTexture.data());
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->quadPositionSize));
    }
    glBindVertexArray(d_ptr->quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

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
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/debug_quad.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/debug_quad_depth.fs");

    // configure depth map FBO
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int FBO, depthTexture;
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");
    // shader configuration
    shader2->bind();
    shader2->setUniformValue("depthMap", 0);

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
        auto near_plane = 1.0f;
        auto far_plane = 7.5f;
        lightProjection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView.lookAt(lightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        shader1->bind();
        shader1->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        renderScene(shader1);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // reset viewport
        glViewport(0, 0, d_ptr->width, d_ptr->height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // render Depth map to quad for visual debugging
        shader2->bind();
        shader2->setUniformValue("near_plane", near_plane);
        shader2->setUniformValue("far_plane", far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        renderQuad();

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
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/debug_quad.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/debug_quad_depth.fs");

    // configure depth map FBO
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int FBO, depthTexture;
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");
    // shader configuration
    shader1->bind();
    shader1->setUniformValue("diffuseTexture", 0);
    shader1->setUniformValue("shadowMap", 1);
    shader3->bind();
    shader3->setUniformValue("depthMap", 0);

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
        auto near_plane = 1.0f;
        auto far_plane = 7.5f;
        lightProjection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView.lookAt(lightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        shader2->bind();
        shader2->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        renderScene(shader2);
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
        shader1->setUniformValue("lightPos", lightPos);
        shader1->setUniformValue("viewPos", camera->position());
        shader1->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        renderScene(shader1);

//        // render Depth map to quad for visual debugging
//        shader3->bind();
//        shader3->setUniformValue("near_plane", near_plane);
//        shader3->setUniformValue("far_plane", far_plane);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, depthTexture);
//        renderQuad();

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
    const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
    unsigned int FBO, depthTexture;
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");
    // shader configuration
    shader1->bind();
    shader1->setUniformValue("diffuseTexture", 0);
    shader1->setUniformValue("shadowMap", 1);

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
        auto near_plane = 1.0f;
        auto far_plane = 7.5f;
        auto lightPos = this->lightPos();
        lightProjection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView.lookAt(lightPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        shader2->bind();
        shader2->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glCullFace(GL_FRONT);
        renderScene(shader2);
        glCullFace(GL_BACK);
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
        shader1->setUniformValue("lightPos", lightPos);
        shader1->setUniformValue("viewPos", camera->position());
        shader1->setUniformValue("lightSpaceMatrix", lightSpaceMatrix);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        renderScene(shader1);

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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_point.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_point.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/shadow_point_depth.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/shadow_point_depth.fs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Geometry,   ":/glsl/shadow_point_depth.gs");

    // configure depth map FBO
    const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
    unsigned int FBO, depthCubemap;
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");
    // shader configuration
    shader1->bind();
    shader1->setUniformValue("diffuseTexture", 0);
    shader1->setUniformValue("depthMap", 1);

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
        // 0. create depth cubemap transformation matrices
        auto near_plane = 1.0f;
        auto far_plane = 25.0f;
        auto lightPos = QVector3D();
        lightPos.setZ(sin(glfwGetTime() * 0.5) * 3.0);
        QMatrix4x4 shadowProjection;
        QVector<QMatrix4x4> shadowView(6), shadowTransforms(6);
        shadowProjection.perspective(90.0f, 1.0 * SHADOW_WIDTH / SHADOW_HEIGHT, near_plane, far_plane);
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
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        shader2->bind();
        for (int i = 0; i < 6; ++i)
            shader2->setUniformValue(QString("shadowMatrices[%1]").arg(i).toStdString().c_str(), shadowTransforms[i]);
        shader2->setUniformValue("far_plane", far_plane);
        shader2->setUniformValue("lightPos", lightPos);
        renderScene(shader2, 1);
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
        shader1->setUniformValue("far_plane", far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthCubemap);
        renderScene(shader1, 1);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
