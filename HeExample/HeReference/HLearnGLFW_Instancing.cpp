#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLModel.h"
#include <QtCore/QRandomGenerator>
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

int HLearnGLFW::testInstancing()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/instancing.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/instancing.fs");

    QVector<QVector2D> translations(100);
    int index = 0;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            translations[index++] = QVector2D(x / 10.0 + 0.1, y / 10.0 + 0.1);
        }
    }

    float quadVertices[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    // store instance data in an array buffer
    unsigned int VAO, VBOs[2];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBOs);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // this attribute comes from a different vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * 100, &translations[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw points
        shader->bind();
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
        glBindVertexArray(0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBOs);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testInstancing2()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/model_instance.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/model_show.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/model_show.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/model_show.fs");

    // generate a large list of semi-random model transformation matrices
    int amount = 10000;
    float radius = 50.0;
    float offset = 2.5f;
    QRandomGenerator random(glfwGetTime());
    QVector<QMatrix4x4> models(amount);
    for (int i = 0; i < amount; i++)
    {
        QMatrix4x4 model;
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = 360.0 * i / amount;
        float x = sin(angle) * radius + random.bounded(2 * offset) - offset;
        float y = (random.bounded(2 * offset) - offset) * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        float z = cos(angle) * radius + random.bounded(2 * offset) - offset;
        model.translate(x, y, z);
        // 2. scale: Scale between 0.05 and 0.25f
        model.scale(random.bounded(0.2) + 0.05);
        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        model.rotate(random.bounded(360.0), 0.4f, 0.6f, 0.8f);
        // 4. now add to list of matrices
        models[i] = model;
    }

    auto rock = new HOpenGLModel(this);
    rock->load("objects\\rock\\rock.obj");
    rock->setInstancedMatrix(3, models);
    auto planet = new HOpenGLModel(this);
    planet->load("objects\\planet\\planet.obj");

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

        // draw model
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 1000.0f);
        view = camera->viewMatrix();
        model.scale(4.0);
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        rock->draw(shader1, amount);
        shader2->bind();
        shader2->setUniformValue("projection", projection);
        shader2->setUniformValue("view", view);
        shader2->setUniformValue("model", model);
        planet->draw(shader2);
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE

