#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testCoordinate()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/coordinate_systems.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/coordinate_systems.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/awesomeface.png");
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shader->bind();
    shader->setUniformValue("texture1", 0);
    shader->setUniformValue("texture2", 1);

    // create transformations
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    QMatrix4x4 projection, view, model;
    projection.perspective(45.0f, 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
    view.translate(0.0f, 0.0f, -3.0f);
    model.rotate(-45.0f, 1.0f, 0.0f);

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // input
        processInput(d_ptr->window);
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader->bind();
        shader->setUniformValue("model", model);
        shader->setUniformValue("view", view);
        shader->setUniformValue("projection", projection);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // render container
        d_ptr->engine->renderRect(shader);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testCoordinate2()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/coordinate_systems.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/coordinate_systems.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/awesomeface.png");
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shader->bind();
    shader->setUniformValue("texture1", 0);
    shader->setUniformValue("texture2", 1);

    // create transformations
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    QMatrix4x4 projection, view;
    projection.perspective(45.0f, 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
    view.translate(0.0f, 0.0f, -3.0f);

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // input
        processInput(d_ptr->window);
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // render container
        for (int i = 0; i < d_ptr->cubeWorldPosition.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            QMatrix4x4 model;
            model.setToIdentity();
            model.rotate(glfwGetTime() * 3, 1.0f, 0.0f);
            model.translate(d_ptr->cubeWorldPosition.at(i));
            model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
            shader->setUniformValue("model", model);
            d_ptr->engine->renderCube(shader);
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
