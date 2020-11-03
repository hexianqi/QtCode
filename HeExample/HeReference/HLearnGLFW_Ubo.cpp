#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testUbo()
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
    auto shaderR = new HOpenGLShaderProgram(this);
    shaderR->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/advanced_glsl.vs");
    shaderR->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/colors_red.fs");
    auto shaderG = new HOpenGLShaderProgram(this);
    shaderG->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/advanced_glsl.vs");
    shaderG->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/colors_green.fs");
    auto shaderB = new HOpenGLShaderProgram(this);
    shaderB->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/advanced_glsl.vs");
    shaderB->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/colors_blue.fs");
    auto shaderY = new HOpenGLShaderProgram(this);
    shaderY->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/advanced_glsl.vs");
    shaderY->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/colors_yellow.fs");

    unsigned int VBO, VAO, UBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, d_ptr->cubePositionSize, d_ptr->cubePosition.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // shader configuration
    shaderR->bind();
    shaderR->bindUniformBlock("Matrices", 0);
    shaderG->bind();
    shaderG->bindUniformBlock("Matrices", 0);
    shaderB->bind();
    shaderB->bindUniformBlock("Matrices", 0);
    shaderY->bind();
    shaderY->bindUniformBlock("Matrices", 0);

    // Now actually create the buffer
    QMatrix4x4 projection;
    projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    // glBufferData(GL_UNIFORM_BUFFER, sizeof(QMatrix4x4) * 2, nullptr, GL_STATIC_DRAW);
    // QMatrix4x4 带flagBits无法转换成GLSL中的mat4
    glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * 16 * 2, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, sizeof(float) * 16 * 2);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * 16, projection.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

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
        // set uniforms
        auto view = camera->viewMatrix();
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float) * 16, sizeof(float) * 16, view.data());
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        // draw cubes
        glBindVertexArray(VAO);
        QMatrix4x4 model;
        model.translate(-0.75f, 0.75f, 0.0f);
        shaderR->bind();
        shaderR->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model.setToIdentity();
        model.translate(0.75f, 0.75f, 0.0f);
        shaderG->bind();
        shaderG->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model.setToIdentity();
        model.translate(0.75f, -0.75f, 0.0f);
        shaderB->bind();
        shaderB->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model.setToIdentity();
        model.translate(-0.75f, -0.75f, 0.0f);
        shaderY->bind();
        shaderY->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &UBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
