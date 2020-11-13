#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

int HLearnGLFW::testNormalMapping()
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
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/normal_mapping.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/normal_mapping.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_source.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_source.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/brickwall.jpg");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/brickwall_normal.jpg");

    // shader configuration
    shader1->bind();
    shader1->setUniformValue("texture_diffuse1", 0);
    shader1->setUniformValue("texture_normal1", 1);

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

        auto lightPos = this->lightPos();
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        model.rotate(glfwGetTime() * -10.0f, QVector3D(1.0, 0.0, 1.0).normalized());
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("model", model);
        shader1->setUniformValue("lightPos", lightPos);
        shader1->setUniformValue("viewPos", camera->position());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        d_ptr->engine->renderQuad(shader1);

        // render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
        model.setToIdentity();
        model.translate(lightPos);
        model.scale(0.2);
        shader2->bind();
        shader2->setUniformValue("projection", projection);
        shader2->setUniformValue("view", view);
        shader2->setUniformValue("model", model);
        shader2->setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));
        d_ptr->engine->renderSphere(shader2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
