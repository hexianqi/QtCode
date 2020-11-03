#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testMaterials()
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
    auto materialShader = new HOpenGLShaderProgram(this);
    materialShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/materials.vs");
    materialShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/materials.fs");
    auto lightSourceShader = new HOpenGLShaderProgram(this);
    lightSourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_source.vs");
    lightSourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_source.fs");

    unsigned int VBO, VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize + d_ptr->cubeNormalSize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, d_ptr->cubePositionSize, d_ptr->cubePosition.data());
    glBufferSubData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubeNormalSize, d_ptr->cubeNormal.data());
    glBindVertexArray(VAOs[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(d_ptr->cubePositionSize));
    glEnableVertexAttribArray(1);
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
        // light properties
        auto lightPos = this->lightPos();
        auto lightColor = this->lightColor();
        auto diffuseColor = lightColor * 0.5f;      // decrease the influence
        auto ambientColor = diffuseColor * 0.2f;    // low influence
        // draw boxes
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        materialShader->bind();
        materialShader->setUniformValue("light.position", lightPos);
        materialShader->setUniformValue("light.ambient", ambientColor);
        materialShader->setUniformValue("light.diffuse", diffuseColor);
        materialShader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("material.ambient", 1.0f, 0.5f, 0.31f);
        materialShader->setUniformValue("material.diffuse", 1.0f, 0.5f, 0.31f);
        materialShader->setUniformValue("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        materialShader->setUniformValue("material.shininess", 32.0f);
        materialShader->setUniformValue("viewPos", camera->position());
        materialShader->setUniformValue("projection", projection);
        materialShader->setUniformValue("view", view);
        materialShader->setUniformValue("model", model);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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

HE_REFERENCE_END_NAMESPACE
