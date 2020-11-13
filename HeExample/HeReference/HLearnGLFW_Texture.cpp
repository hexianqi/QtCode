#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testTexture()
{
    initGlfw();
    if (!createWindow())
    {
        glfwTerminate();
        return -1;
    }
    if (!initFlad())
        return -1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader program
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/texture_color.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/texture_color.fs");
    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/awesomeface.png");
    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // input
        processInput(d_ptr->window);
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, texture);
        // render container
        shader->bind();
        d_ptr->engine->renderRect(shader);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testTexture2()
{
    initGlfw();
    if (!createWindow())
    {
        glfwTerminate();
        return -1;
    }
    if (!initFlad())
        return -1;

    // build and compile our shader program
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/texture_color.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/texture_blend.fs");
    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/awesomeface.png");
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shader->bind();
    shader->setUniformValue("texture1", 0);
    shader->setUniformValue("texture2", 1);
    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // input
        processInput(d_ptr->window);
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // render container
        shader->bind();
        d_ptr->engine->renderRect(shader);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
