#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLModel.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testModel()
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
    materialShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/model_light.vs");
    materialShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/model_light.fs");
    auto lightSourceShader = new HOpenGLShaderProgram(this);
    lightSourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_source.vs");
    lightSourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_source.fs");

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubePosition.data(), GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    auto material = new HOpenGLModel(this);
    material->load("objects\\backpack\\backpack.obj");

    // draw in wireframe
    if (d_ptr->lineMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
        auto lightColor =  this->lightColor();
        auto diffuseColor = lightColor * 0.5f;  // decrease the influence
        auto ambientColor = lightColor * 0.2f;  // low influence
        // draw model
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        model.translate(0.0f, 0.0f, 0.0f);
        model.scale(0.2f);
        materialShader->bind();
        materialShader->setUniformValue("light.position", lightPos);
        materialShader->setUniformValue("light.ambient", ambientColor);
        materialShader->setUniformValue("light.diffuse", diffuseColor);
        materialShader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("viewPos", camera->position());
        materialShader->setUniformValue("projection", projection);
        materialShader->setUniformValue("view", view);
        materialShader->setUniformValue("model", model);
        material->draw(materialShader);

        // draw light source
        model.setToIdentity();
        model.translate(lightPos);
        model.scale(0.2f);
        lightSourceShader->bind();
        lightSourceShader->setUniformValue("projection", projection);
        lightSourceShader->setUniformValue("view", view);
        lightSourceShader->setUniformValue("model", model);
        lightSourceShader->setUniformValue("lightColor", lightColor);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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
