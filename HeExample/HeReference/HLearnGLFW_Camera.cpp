#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testCamera()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/coordinate_systems.vert");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/coordinate_systems.frag");

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_ptr->cubeVertices2.size(), d_ptr->cubeVertices2.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture
    auto texture1 = loadTexture(":/image/huesatradialpicker.png");
    auto texture2 = loadTexture(":/image/awesomeface.png");
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shader->bind();
    shader->setUniformValue("texture1", 0);
    shader->setUniformValue("texture2", 1);

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // per-frame time logic
        perFrameTime();
        // input
        processInput(d_ptr->window);
        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // render boxes
        glBindVertexArray(VAO);
        QMatrix4x4 projection, view;
        projection.perspective(fov, d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        for (int i = 0; i < d_ptr->cubePositions.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            QMatrix4x4 model;
            model.rotate(glfwGetTime(), 1.0f, 0.0f);
            model.translate(d_ptr->cubePositions.at(i));
            model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
            shader->setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testCamera2()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/coordinate_systems.vert");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/coordinate_systems.frag");

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_ptr->cubeVertices2.size(), d_ptr->cubeVertices2.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture
    auto texture1 = loadTexture(":/image/huesatradialpicker.png");
    auto texture2 = loadTexture(":/image/awesomeface.png");
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shader->bind();
    shader->setUniformValue("texture1", 0);
    shader->setUniformValue("texture2", 1);

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // per-frame time logic
        perFrameTime();
        // input
        processInput(d_ptr->window);
        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // render boxes
        glBindVertexArray(VAO);
        QMatrix4x4 projection;
        projection.perspective(camera->zoom(), d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", camera->viewMatrix());
        for (int i = 0; i < d_ptr->cubePositions.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            QMatrix4x4 model;
            model.rotate(glfwGetTime(), 1.0f, 0.0f);
            model.translate(d_ptr->cubePositions.at(i));
            model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
            shader->setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
