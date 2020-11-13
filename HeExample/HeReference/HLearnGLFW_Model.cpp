#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
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
    auto sourceShader = new HOpenGLShaderProgram(this);
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_source.vs");
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_source.fs");

    auto material = new HOpenGLModel(this);
    material->load("objects\\cyborg\\cyborg.obj");

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
        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // properties
        auto lightPos = this->lightPos();
        auto lightColor = this->lightColor();
        auto lightAmbient = lightColor * 0.1f;
        auto lightDiffuse = lightColor * 0.5f;
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // draw boxes
        model.translate(0.0, -2.0, 0.0);
        materialShader->bind();
        materialShader->setUniformValue("projection", projection);
        materialShader->setUniformValue("view", view);
        materialShader->setUniformValue("model", model);
        materialShader->setUniformValue("viewPos", camera->position());
        materialShader->setUniformValue("light.position", lightPos);
        materialShader->setUniformValue("light.ambient", lightAmbient);
        materialShader->setUniformValue("light.diffuse", lightDiffuse);
        materialShader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        material->draw(materialShader);
        // draw light source
        model.setToIdentity();
        model.translate(lightPos);
        model.scale(0.2);
        sourceShader->bind();
        sourceShader->setUniformValue("projection", projection);
        sourceShader->setUniformValue("view", view);
        sourceShader->setUniformValue("model", model);
        sourceShader->setUniformValue("lightColor", lightColor);
        d_ptr->engine->renderSphere(sourceShader);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
