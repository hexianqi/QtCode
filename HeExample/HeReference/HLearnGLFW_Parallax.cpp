#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testParallaxMapping()
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
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/parallax_mapping3.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/parallax_mapping3.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/bricks2.jpg");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/bricks2_normal.jpg");
    auto texture3 = HOpenGLHelper::loadTexture(":/textures/bricks2_disp.jpg");
    // shader configuration
    shader->bind();
    shader->setUniformValue("diffuseMap", 0);
    shader->setUniformValue("normalMap", 1);
    shader->setUniformValue("depthMap", 2);

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

        QMatrix4x4 projection, view, model;
        auto lightPos = this->lightPos();
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        model.rotate(glfwGetTime() * -10.0f, QVector3D(1.0, 0.0, 1.0).normalized());
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        shader->setUniformValue("model", model);
        shader->setUniformValue("lightPos", lightPos);
        shader->setUniformValue("viewPos", camera->position());
        shader->setUniformValue("heightScale", d_ptr->heightScale);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        renderQuad2();

        // render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
        model.setToIdentity();
        model.translate(lightPos);
        model.scale(0.1);
        shader->setUniformValue("model", model);
        renderQuad2();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
