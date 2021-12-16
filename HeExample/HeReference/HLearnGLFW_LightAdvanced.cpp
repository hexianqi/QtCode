#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

int HLearnGLFW::testLightBlinn()
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader program
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_blinn.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_blinn.fs");

    // load and create a texture
    auto texture = HOpenGLHelper::loadTexture(":/textures/wood.png");
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
        QMatrix4x4 projection, view;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        shader->setUniformValue("viewPos", camera->position());
        shader->setUniformValue("lightPos", QVector3D(0.0,0.0,0.0));
        shader->setUniformValue("blinn", d_ptr->blinn);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        d_ptr->engine->renderPlane(shader);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testLightGamma()
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader program
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_gamma.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_gamma.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/wood.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/wood.png", true);
    // shader configuration
    shader->bind();
    shader->setUniformValue("texture1", 0);

    // lighting info
    QVector3D lightPositions[] = {
        QVector3D(-3.0f, 0.0f, 0.0f),
        QVector3D(-1.0f, 0.0f, 0.0f),
        QVector3D( 1.0f, 0.0f, 0.0f),
        QVector3D( 3.0f, 0.0f, 0.0f)
    };
    QVector3D lightColors[] = {
        QVector3D(0.25, 0.25, 0.25),
        QVector3D(0.50, 0.50, 0.50),
        QVector3D(0.75, 0.75, 0.75),
        QVector3D(1.00, 1.00, 1.00)
    };

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
        QMatrix4x4 projection, view;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        shader->setUniformValueArray("lightPositions", lightPositions, 4);
        shader->setUniformValueArray("lightColors", lightColors, 4);
        shader->setUniformValue("viewPos", camera->position());
        shader->setUniformValue("gamma", d_ptr->gamma);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, d_ptr->gamma ? texture2 : texture1);
        d_ptr->engine->renderPlane(shader);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE
