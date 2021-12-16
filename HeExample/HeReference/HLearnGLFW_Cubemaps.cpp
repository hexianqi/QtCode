#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

int HLearnGLFW::testCubemaps()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/texture_obj.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/texture_obj.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/skybox.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/skybox.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadCubemap(QStringList() << ":/textures/skybox/right.jpg"
                                                             << ":/textures/skybox/left.jpg"
                                                             << ":/textures/skybox/top.jpg"
                                                             << ":/textures/skybox/bottom.jpg"
                                                             << ":/textures/skybox/front.jpg"
                                                             << ":/textures/skybox/back.jpg");

    // shader configuration
    shader1->bind();
    shader1->setUniformValue("texture1", 0);
    shader2->bind();
    shader2->setUniformValue("texture1", 0);

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
        // set uniforms
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        // cubes
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("model", model);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        d_ptr->engine->renderCube(shader1);
        // draw skybox as last
        view = QMatrix4x4(view.toGenericMatrix<3, 3>());    // remove translation from the view matrix
        shader2->bind();
        shader2->setUniformValue("projection", projection);
        shader2->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
        d_ptr->engine->renderSkybox(shader2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testCubemaps2()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/environment_maps.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/environment_maps.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/skybox.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/skybox.fs");

    // load and create a texture
    auto texture = HOpenGLHelper::loadCubemap(QStringList() << ":/textures/skybox/right.jpg"
                                                            << ":/textures/skybox/left.jpg"
                                                            << ":/textures/skybox/top.jpg"
                                                            << ":/textures/skybox/bottom.jpg"
                                                            << ":/textures/skybox/front.jpg"
                                                            << ":/textures/skybox/back.jpg");

    // shader configuration
    shader1->bind();
    shader1->setUniformValue("texture1", 0);
    shader2->bind();
    shader2->setUniformValue("texture1", 0);

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
        // set uniforms
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        // cubes
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("model", model);
        shader1->setUniformValue("viewPos", camera->position());
        d_ptr->engine->renderCube(shader1);
        // draw skybox as last
        view = QMatrix4x4(view.toGenericMatrix<3, 3>());    // remove translation from the view matrix
        shader2->bind();
        shader2->setUniformValue("projection", projection);
        shader2->setUniformValue("view", view);
        d_ptr->engine->renderSkybox(shader2);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE
