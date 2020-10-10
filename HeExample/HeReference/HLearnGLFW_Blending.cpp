#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
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

    unsigned int VBOs[3], VAOs[3];
    glGenVertexArrays(3, VAOs);
    glGenBuffers(3, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->cubePositionSize, d_ptr->cubePosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubeTextureSize, d_ptr->cubeTexture.data());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->cubePositionSize));
    glEnableVertexAttribArray(1);
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->planePositionSize + d_ptr->planeTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->planePositionSize, d_ptr->planePosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->planePositionSize, d_ptr->planeTextureSize, d_ptr->planeTexture.data());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->planePositionSize));
    glEnableVertexAttribArray(1);
    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->transparentPositionSize + d_ptr->transparentTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->transparentPositionSize, d_ptr->transparentPosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->transparentPositionSize, d_ptr->transparentTextureSize, d_ptr->transparentTexture.data());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->transparentPositionSize));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    auto vegetation = QList<QVector3D>() << QVector3D(-1.5f, 0.0f, -0.48f)
                                         << QVector3D( 1.5f, 0.0f,  0.51f)
                                         << QVector3D( 0.0f, 0.0f,  0.7f)
                                         << QVector3D(-0.3f, 0.0f, -2.3f)
                                         << QVector3D( 0.5f, 0.0f, -0.6f);

    // load and create a texture
    auto texture1 = loadTexture(":/image/marble.jpg");
    auto texture2 = loadTexture(":/image/metal.png");
    auto texture3 = loadTexture(":/image/grass.png");

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
        // clear
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // set uniforms
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        // cubes
        glBindVertexArray(VAOs[0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        model.setToIdentity();
        model.translate(-1.0f, 0.0f, -1.0f);
        shader->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model.setToIdentity();
        model.translate(2.0f, 0.0f, 0.0f);
        shader->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // floor
        glBindVertexArray(VAOs[1]);
        glBindTexture(GL_TEXTURE_2D, texture2);
        model.setToIdentity();
        shader->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // vegetation
        glBindVertexArray(VAOs[2]);
        glBindTexture(GL_TEXTURE_2D, texture3);
        for (int i = 0; i < vegetation.size(); i++)
        {
            model.setToIdentity();
            model.translate(vegetation.at(i));
            shader->setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);
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

    unsigned int VBOs[3], VAOs[3];
    glGenVertexArrays(3, VAOs);
    glGenBuffers(3, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->cubePositionSize, d_ptr->cubePosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubeTextureSize, d_ptr->cubeTexture.data());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->cubePositionSize));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->planePositionSize + d_ptr->planeTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->planePositionSize, d_ptr->planePosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->planePositionSize, d_ptr->planeTextureSize, d_ptr->planeTexture.data());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->planePositionSize));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->transparentPositionSize + d_ptr->transparentTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->transparentPositionSize, d_ptr->transparentPosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->transparentPositionSize, d_ptr->transparentTextureSize, d_ptr->transparentTexture.data());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->transparentPositionSize));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    auto windows = QList<QVector3D>() << QVector3D(-1.5f, 0.0f, -0.48f)
                                      << QVector3D( 1.5f, 0.0f,  0.51f)
                                      << QVector3D( 0.0f, 0.0f,  0.7f)
                                      << QVector3D(-0.3f, 0.0f, -2.3f)
                                      << QVector3D( 0.5f, 0.0f, -0.6f);

    // load and create a texture
    auto texture1 = loadTexture(":/image/marble.jpg");
    auto texture2 = loadTexture(":/image/metal.png");
    auto texture3 = loadTexture(":/image/window.png");

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
        // sort the transparent windows before rendering
        std::map<float, QVector3D> sorted;
        for (int i = 0; i < windows.size(); i++)
        {
            auto distance = camera->position().distanceToPoint(windows.at(i));
            sorted[distance] = windows[i];
        }
        // clear
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // set uniforms
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        // cubes
        glBindVertexArray(VAOs[0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        model.setToIdentity();
        model.translate(-1.0f, 0.0f, -1.0f);
        shader->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model.setToIdentity();
        model.translate(2.0f, 0.0f, 0.0f);
        shader->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // floor
        glBindVertexArray(VAOs[1]);
        glBindTexture(GL_TEXTURE_2D, texture2);
        model.setToIdentity();
        shader->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // windows
        glBindVertexArray(VAOs[2]);
        glBindTexture(GL_TEXTURE_2D, texture3);
        for (auto i = sorted.rbegin(); i != sorted.rend(); i++)
        {
            model.setToIdentity();
            model.translate(i->second);
            shader->setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
