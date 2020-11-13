#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testBlending()
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
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/blending.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/blending.fs");
    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/marble.jpg");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/metal.png");
    auto texture3 = HOpenGLHelper::loadTexture(":/textures/grass.png");
    // vegetation locations
    auto vegetation = QList<QVector3D>() << QVector3D(-1.5f, 0.0f, -0.48f)
                                         << QVector3D( 1.5f, 0.0f,  0.51f)
                                         << QVector3D( 0.0f, 0.0f,  0.7f)
                                         << QVector3D(-0.3f, 0.0f, -2.3f)
                                         << QVector3D( 0.5f, 0.0f, -0.6f);
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
        // draw cubes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        shader->bind();
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
        // draw vegetation
        glBindTexture(GL_TEXTURE_2D, texture3);
        for (int i = 0; i < vegetation.size(); i++)
        {
            model.setToIdentity();
            model.translate(vegetation.at(i));
            shader->setUniformValue("model", model);
            d_ptr->engine->renderRect(shader);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testBlending2()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/blending2.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/blending2.fs");
    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/marble.jpg");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/metal.png");
    auto texture3 = HOpenGLHelper::loadTexture(":/textures/window.png");
    // windows locations
    auto windows = QList<QVector3D>() << QVector3D(-1.5f, 0.0f, -0.48f)
                                      << QVector3D( 1.5f, 0.0f,  0.51f)
                                      << QVector3D( 0.0f, 0.0f,  0.7f)
                                      << QVector3D(-0.3f, 0.0f, -2.3f)
                                      << QVector3D( 0.5f, 0.0f, -0.6f);
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
        std::map<float, QVector3D> sorted;
        for (int i = 0; i < windows.size(); i++)
        {
            auto distance = camera->position().distanceToPoint(windows.at(i));
            sorted[distance] = windows[i];
        }
        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // properties
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // draw cubes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        shader->bind();
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
        // draw vegetation
        glBindTexture(GL_TEXTURE_2D, texture3);
        for (auto i = sorted.rbegin(); i != sorted.rend(); i++)
        {
            model.setToIdentity();
            model.translate(i->second);
            shader->setUniformValue("model", model);
            d_ptr->engine->renderRect(shader);
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
