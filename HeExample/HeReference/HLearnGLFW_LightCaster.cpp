#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include <QtCore/QtMath>
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testLightCasterDirectional()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_casters_directional.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_casters_directional.fs");

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize + d_ptr->cubeTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->cubePositionSize, d_ptr->cubePosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubeNormalSize, d_ptr->cubeNormal.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize, d_ptr->cubeTextureSize, d_ptr->cubeTexture.data());
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(d_ptr->cubePositionSize));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->cubePositionSize + d_ptr->cubeNormalSize));
    glEnableVertexAttribArray(2);

    // load and create a texture
    auto texture1 = loadTexture(":/image/container.png");
    auto texture2 = loadTexture(":/image/container_specular.png");

    // shader configuration
    shader->bind();
    shader->setUniformValue("material.diffuse", 0);
    shader->setUniformValue("material.specular", 1);

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
        // light properties
        auto lightColor = this->lightColor();
        auto diffuseColor = lightColor * 0.5f;  // decrease the influence
        auto ambientColor = lightColor * 0.8f;  // low influence
        // draw boxes
        QMatrix4x4 projection, view;
        projection.perspective(camera->zoom(), d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // be sure to activate shader when setting uniforms/drawing objects
        shader->bind();
        shader->setUniformValue("light.direction", -0.2f, -1.0f, -0.3f);
        shader->setUniformValue("light.ambient", ambientColor);
        shader->setUniformValue("light.diffuse", diffuseColor);
        shader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        shader->setUniformValue("material.shininess", 32.0f);
        shader->setUniformValue("viewPos", camera->position());
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);
        for (int i = 0; i < d_ptr->cubeWorldPosition.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            QMatrix4x4 model;
            model.rotate(glfwGetTime(), 1.0f, 0.0f);
            model.translate(d_ptr->cubeWorldPosition.at(i));
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

int HLearnGLFW::testLightCasterPoint()
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
    auto lightingShader = new HOpenGLShaderProgram(this);
    lightingShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_casters_point.vs");
    lightingShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_casters_point.fs");
    auto lightSourceShader = new HOpenGLShaderProgram(this);
    lightSourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,   ":/glsl/light_source.vs");
    lightSourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment, ":/glsl/light_source.fs");

    unsigned int VBO, VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize + d_ptr->cubeTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->cubePositionSize, d_ptr->cubePosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubeNormalSize, d_ptr->cubeNormal.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize, d_ptr->cubeTextureSize, d_ptr->cubeTexture.data());
    glBindVertexArray(VAOs[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(d_ptr->cubePositionSize));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->cubePositionSize + d_ptr->cubeNormalSize));
    glEnableVertexAttribArray(2);
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load and create a texture
    auto texture1 = loadTexture(":/image/container.png");
    auto texture2 = loadTexture(":/image/container_specular.png");

    // shader configuration
    lightingShader->bind();
    lightingShader->setUniformValue("material.diffuse", 0);
    lightingShader->setUniformValue("material.specular", 1);

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
        // light properties
        auto lightPos = this->lightPos();
        auto lightColor = this->lightColor();
        auto ambientColor = lightColor * 0.8f;
        auto diffuseColor = lightColor * 0.5f;
        // draw boxes
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader->bind();
        lightingShader->setUniformValue("light.position", lightPos);
        lightingShader->setUniformValue("light.ambient", ambientColor);
        lightingShader->setUniformValue("light.diffuse", diffuseColor);
        lightingShader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setUniformValue("light.constant", 1.0f);
        lightingShader->setUniformValue("light.linear", 0.09f);
        lightingShader->setUniformValue("light.quadratic", 0.032f);
        lightingShader->setUniformValue("material.shininess", 32.0f);
        lightingShader->setUniformValue("viewPos", camera->position());
        lightingShader->setUniformValue("projection", projection);
        lightingShader->setUniformValue("view", view);
        lightingShader->setUniformValue("model", model);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAOs[0]);
        for (int i = 0; i < d_ptr->cubeWorldPosition.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            model.setToIdentity();
            model.rotate(glfwGetTime(), 1.0f, 0.0f);
            model.translate(d_ptr->cubeWorldPosition.at(i));
            model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
            lightingShader->setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // draw light source
        model.setToIdentity();
        model.translate(lightPos);
        model.scale(0.2f);
        lightSourceShader->bind();
        lightSourceShader->setUniformValue("projection", projection);
        lightSourceShader->setUniformValue("view", view);
        lightSourceShader->setUniformValue("model", model);
        lightSourceShader->setUniformValue("lightColor", lightColor);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(1, &VBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testLightCasterSpot()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_casters_spot.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_casters_spot.fs");

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize + d_ptr->cubeTextureSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->cubePositionSize, d_ptr->cubePosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubeNormalSize, d_ptr->cubeNormal.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize, d_ptr->cubeTextureSize, d_ptr->cubeTexture.data());
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(d_ptr->cubePositionSize));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(d_ptr->cubePositionSize + d_ptr->cubeNormalSize));
    glEnableVertexAttribArray(2);

    // load and create a texture
    auto texture1 = loadTexture(":/image/container.png");
    auto texture2 = loadTexture(":/image/container_specular.png");

    // shader configuration
    shader->bind();
    shader->setUniformValue("material.diffuse", 0);
    shader->setUniformValue("material.specular", 1);

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
        // light properties
        auto lightColor = this->lightColor();
        auto diffuseColor = lightColor * 0.8f;
        auto ambientColor = lightColor * 0.1f;
        // draw boxes
        QMatrix4x4 projection, view;
        projection.perspective(camera->zoom(), d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // be sure to activate shader when setting uniforms/drawing objects
        shader->bind();
        shader->setUniformValue("light.position", camera->position());
        shader->setUniformValue("light.direction", camera->front());
        shader->setUniformValue("light.cutOff", (GLfloat)cos(qDegreesToRadians(12.5)));
        shader->setUniformValue("light.outerCutOff", (GLfloat)cos(qDegreesToRadians(17.5)));
        shader->setUniformValue("light.ambient", ambientColor);
        shader->setUniformValue("light.diffuse", diffuseColor);
        shader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        shader->setUniformValue("light.constant", 1.0f);
        shader->setUniformValue("light.linear", 0.09f);
        shader->setUniformValue("light.quadratic", 0.032f);
        shader->setUniformValue("material.shininess", 32.0f);
        shader->setUniformValue("viewPos", camera->position());
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);
        for (int i = 0; i < d_ptr->cubeWorldPosition.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            QMatrix4x4 model;
            model.rotate(glfwGetTime(), 1.0f, 0.0f);
            model.translate(d_ptr->cubeWorldPosition.at(i));
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
