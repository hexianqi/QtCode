#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

int HLearnGLFW::testDepth()
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
//    glDepthFunc(GL_ALWAYS);

    // build and compile our shader program
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/test_depth_view.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/test_depth_view.fs");
    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/marble.jpg");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/metal.png");
    // shader configuration
    shader->bind();
    shader->setUniformValue("texture1", 0);
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
        // properties
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // draw boxes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        shader->bind();
        shader->setUniformValue("linearize", d_ptr->linearize);
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        model.setToIdentity();
        model.translate(-1.0f, 0.0f, -1.0f);
        shader->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader);
        model.setToIdentity();
        model.translate(2.0f, 0.0f, 0.0f);
        shader->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader);
        // draw floor
        glBindTexture(GL_TEXTURE_2D, texture2);
        model.setToIdentity();
        shader->setUniformValue("model", model);
        d_ptr->engine->renderPlane(shader);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testStencil()
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
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/texture_obj.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/texture_obj.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,   ":/glsl/test_stencil_single_color.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment, ":/glsl/test_stencil_single_color.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/marble.jpg");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/metal.png");
    // shader configuration
    shader1->bind();
    shader1->setUniformValue("texture1", 0);
    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // per-frame time logic
        perFrameTime();
        // input
        processInput(d_ptr->window);
        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        // properties
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // draw floor as normal, but don't write the floor to the stencil buffer, we only care about the containers. We set its mask to 0x00 to not write to the stencil buffer.
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        glStencilMask(0x00);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        model.setToIdentity();
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderPlane(shader1);
        // 1st. render pass, draw objects as normal, writing to the stencil buffer
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        model.setToIdentity();
        model.translate(-1.0f, 0.0f, -1.0f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.translate(2.0f, 0.0f, 0.0f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
        // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing
        // the objects' size differences, making it look like borders.
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        shader2->bind();
        shader2->setUniformValue("projection", projection);
        shader2->setUniformValue("view", view);
        model.setToIdentity();
        model.translate(-1.0f, 0.0f, -1.0f);
        model.scale(1.1);
        shader2->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader2);
        model.setToIdentity();
        model.translate(2.0f, 0.0f, 0.0f);
        model.scale(1.1);
        shader2->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader2);
        // restore
        glBindVertexArray(0);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE
