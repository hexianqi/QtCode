#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include <QtCore/QtMath>
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testLightMult()
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
    lightingShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_multiple.vs");
    lightingShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_multiple.fs");
    auto lightSourceShader = new HOpenGLShaderProgram(this);
    lightSourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,   ":/glsl/light_source.vs");
    lightSourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment, ":/glsl/light_source.fs");

    auto lightPositions = QList<QVector3D>() << QVector3D( 0.7f,  0.2f,  2.0f)
                                             << QVector3D( 2.3f, -3.3f, -4.0f)
                                             << QVector3D(-4.0f,  2.0f, -12.0f)
                                             << QVector3D( 0.0f,  0.0f, -3.0f);

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
        // draw boxes
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        auto lightColor = this->lightColor();
        lightingShader->bind();
        lightingShader->setUniformValue("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader->setUniformValue("dirLight.ambient", lightColor * 0.05f);
        lightingShader->setUniformValue("dirLight.diffuse", lightColor * 0.4f);
        lightingShader->setUniformValue("dirLight.specular", 0.5f, 0.5f, 0.5f);
        lightingShader->setUniformValue("pointLights[0].position", lightPositions[0]);
        lightingShader->setUniformValue("pointLights[0].ambient", lightColor * 0.05f);
        lightingShader->setUniformValue("pointLights[0].diffuse", lightColor * 0.8f);
        lightingShader->setUniformValue("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setUniformValue("pointLights[0].constant", 1.0f);
        lightingShader->setUniformValue("pointLights[0].linear", 0.09f);
        lightingShader->setUniformValue("pointLights[0].quadratic", 0.032f);
        lightingShader->setUniformValue("pointLights[1].position", lightPositions[1]);
        lightingShader->setUniformValue("pointLights[1].ambient", lightColor * 0.05f);
        lightingShader->setUniformValue("pointLights[1].diffuse", lightColor * 0.8f);
        lightingShader->setUniformValue("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setUniformValue("pointLights[1].constant", 1.0f);
        lightingShader->setUniformValue("pointLights[1].linear", 0.09f);
        lightingShader->setUniformValue("pointLights[1].quadratic", 0.032f);
        lightingShader->setUniformValue("pointLights[2].position", lightPositions[2]);
        lightingShader->setUniformValue("pointLights[2].ambient", lightColor * 0.05f);
        lightingShader->setUniformValue("pointLights[2].diffuse", lightColor * 0.8f);
        lightingShader->setUniformValue("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setUniformValue("pointLights[2].constant", 1.0f);
        lightingShader->setUniformValue("pointLights[2].linear", 0.09f);
        lightingShader->setUniformValue("pointLights[2].quadratic", 0.032f);
        lightingShader->setUniformValue("pointLights[3].position", lightPositions[3]);
        lightingShader->setUniformValue("pointLights[3].ambient", lightColor * 0.05f);
        lightingShader->setUniformValue("pointLights[3].diffuse", lightColor * 0.8f);
        lightingShader->setUniformValue("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setUniformValue("pointLights[3].constant", 1.0f);
        lightingShader->setUniformValue("pointLights[3].linear", 0.09f);
        lightingShader->setUniformValue("pointLights[3].quadratic", 0.032f);
        lightingShader->setUniformValue("spotLight.position", camera->position());
        lightingShader->setUniformValue("spotLight.direction", camera->front());
        lightingShader->setUniformValue("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader->setUniformValue("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader->setUniformValue("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setUniformValue("spotLight.constant", 1.0f);
        lightingShader->setUniformValue("spotLight.linear", 0.09f);
        lightingShader->setUniformValue("spotLight.quadratic", 0.032f);
        lightingShader->setUniformValue("spotLight.cutOff", (GLfloat)cos(qDegreesToRadians(12.5)));
        lightingShader->setUniformValue("spotLight.outerCutOff", (GLfloat)cos(qDegreesToRadians(15.0)));
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
        glBindVertexArray(VAOs[1]);
        lightSourceShader->bind();
        lightSourceShader->setUniformValue("projection", projection);
        lightSourceShader->setUniformValue("view", view);
        lightSourceShader->setUniformValue("lightColor", lightColor);
        for (int i = 0; i < lightPositions.size(); i++)
        {
            model.setToIdentity();
            model.translate(lightPositions.at(i));
            model.scale(0.2f);
            lightSourceShader->setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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

HE_REFERENCE_END_NAMESPACE
