#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtCore/QtMath>
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

int HLearnGLFW::testLight()
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
    materialShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_phong.vs");
    materialShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_phong.fs");
    auto sourceShader = new HOpenGLShaderProgram(this);
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_source.vs");
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_source.fs");

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
        // draw boxes
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        auto lightPos = this->lightPos();
        auto lightColor = this->lightColor();
        materialShader->bind();
        materialShader->setUniformValue("projection", projection);
        materialShader->setUniformValue("view", view);
        materialShader->setUniformValue("model", model);
        materialShader->setUniformValue("viewPos", camera->position());
        materialShader->setUniformValue("objectColor", 1.0f, 0.5f, 0.31f);
        materialShader->setUniformValue("lightPos", lightPos);
        materialShader->setUniformValue("lightColor", lightColor);
        d_ptr->engine->renderCube(materialShader);
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_caster_directional.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_caster_directional.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/container_specular.png");

    // shader configuration
    shader->bind();
    shader->setUniformValue("material.diffuse", 0);
    shader->setUniformValue("material.specular", 1);
    shader->setUniformValue("material.shininess", 64.0f);

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
        auto lightColor = this->lightColor();
        auto lightAmbient = lightColor * 0.1f;
        auto lightDiffuse = lightColor * 0.5f;
        QMatrix4x4 projection, view;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // draw boxes
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        shader->setUniformValue("viewPos", camera->position());
        shader->setUniformValue("light.direction", -0.2f, -1.0f, -0.3f);
        shader->setUniformValue("light.ambient", lightAmbient);
        shader->setUniformValue("light.diffuse", lightDiffuse);
        shader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        for (int i = 0; i < d_ptr->cubeWorldPosition.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            QMatrix4x4 model;
            model.rotate(glfwGetTime() * 3, 1.0f, 0.0f);
            model.translate(d_ptr->cubeWorldPosition.at(i));
            model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
            shader->setUniformValue("model", model);
            d_ptr->engine->renderCube(shader);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
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
    auto materialShader = new HOpenGLShaderProgram(this);
    materialShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_caster_point.vs");
    materialShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_caster_point.fs");
    auto sourceShader = new HOpenGLShaderProgram(this);
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,   ":/glsl/light_source.vs");
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment, ":/glsl/light_source.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/container_specular.png");

    // shader configuration
    materialShader->bind();
    materialShader->setUniformValue("material.diffuse", 0);
    materialShader->setUniformValue("material.specular", 1);
    materialShader->setUniformValue("material.shininess", 64.0f);

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
        materialShader->bind();
        materialShader->setUniformValue("projection", projection);
        materialShader->setUniformValue("view", view);
        materialShader->setUniformValue("viewPos", camera->position());
        materialShader->setUniformValue("light.position", lightPos);
        materialShader->setUniformValue("light.ambient", lightAmbient);
        materialShader->setUniformValue("light.diffuse", lightDiffuse);
        materialShader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("light.constant", 1.0f);
        materialShader->setUniformValue("light.linear", 0.09f);
        materialShader->setUniformValue("light.quadratic", 0.032f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        for (int i = 0; i < d_ptr->cubeWorldPosition.size(); i++)
        {
            QMatrix4x4 model;
            model.rotate(glfwGetTime() * 3, 1.0f, 0.0f);
            model.translate(d_ptr->cubeWorldPosition.at(i));
            model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
            materialShader->setUniformValue("model", model);
            d_ptr->engine->renderCube(materialShader);
        }
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_caster_spot.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_caster_spot.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/container_specular.png");

    // shader configuration
    shader->bind();
    shader->setUniformValue("material.diffuse", 0);
    shader->setUniformValue("material.specular", 1);
    shader->setUniformValue("material.shininess", 32.0f);

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
        auto lightColor = this->lightColor();
        auto lightAmbient = lightColor * 0.1f;
        auto lightDiffuse = lightColor * 0.5f;
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // draw boxes
        shader->bind();
        shader->setUniformValue("projection", projection);
        shader->setUniformValue("view", view);
        shader->setUniformValue("viewPos", camera->position());
        shader->setUniformValue("light.position", camera->position());
        shader->setUniformValue("light.direction", camera->front());
        shader->setUniformValue("light.innerCutOff", (GLfloat)cos(qDegreesToRadians(12.5)));
        shader->setUniformValue("light.outerCutOff", (GLfloat)cos(qDegreesToRadians(17.5)));
        shader->setUniformValue("light.ambient", lightAmbient);
        shader->setUniformValue("light.diffuse", lightDiffuse);
        shader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        shader->setUniformValue("light.constant", 1.0f);
        shader->setUniformValue("light.linear", 0.09f);
        shader->setUniformValue("light.quadratic", 0.032f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        for (int i = 0; i < d_ptr->cubeWorldPosition.size(); i++)
        {
            model.setToIdentity();
            model.rotate(glfwGetTime() * 3, 1.0f, 0.0f);
            model.translate(d_ptr->cubeWorldPosition.at(i));
            model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
            shader->setUniformValue("model", model);
            d_ptr->engine->renderCube(shader);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testLightMaps()
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
    materialShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_maps.vs");
    materialShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_maps.fs");
    auto sourceShader = new HOpenGLShaderProgram(this);
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,    ":/glsl/light_source.vs");
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment,  ":/glsl/light_source.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/container_specular.png");
    auto texture3 = HOpenGLHelper::loadTexture(":/textures/matrix.jpg");

    // shader configuration
    materialShader->bind();
    materialShader->setUniformValue("material.diffuse", 0);
    materialShader->setUniformValue("material.specular", 1);
    materialShader->setUniformValue("material.emission", 2);
    materialShader->setUniformValue("material.shininess", 64.0f);

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
        materialShader->bind();
        materialShader->setUniformValue("projection", projection);
        materialShader->setUniformValue("view", view);
        materialShader->setUniformValue("model", model);
        materialShader->setUniformValue("viewPos", camera->position());
        materialShader->setUniformValue("light.position", lightPos);
        materialShader->setUniformValue("light.ambient", lightAmbient);
        materialShader->setUniformValue("light.diffuse", lightDiffuse);
        materialShader->setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        d_ptr->engine->renderCube(materialShader);
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

int HLearnGLFW::testLightCasterMult()
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
    materialShader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/light_caster_multi.vs");
    materialShader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/light_caster_multi.fs");
    auto sourceShader = new HOpenGLShaderProgram(this);
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Vertex,   ":/glsl/light_source.vs");
    sourceShader->addShaderFromSourceFile(HOpenGLShader::Fragment, ":/glsl/light_source.fs");

    auto lightPositions = QList<QVector3D>() << QVector3D( 0.7f,  0.2f,  2.0f)
                                             << QVector3D( 2.3f, -3.3f, -4.0f)
                                             << QVector3D(-4.0f,  2.0f, -12.0f)
                                             << QVector3D( 0.0f,  0.0f, -3.0f);

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/container.png");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/container_specular.png");

    // shader configuration
    materialShader->bind();
    materialShader->setUniformValue("material.diffuse", 0);
    materialShader->setUniformValue("material.specular", 1);
    materialShader->setUniformValue("material.shininess", 32.0f);

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
        auto lightColor = this->lightColor();
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        // draw boxes
        materialShader->bind();
        materialShader->setUniformValue("projection", projection);
        materialShader->setUniformValue("view", view);
        materialShader->setUniformValue("viewPos", camera->position());
        materialShader->setUniformValue("dirLight.direction", -0.2f, -1.0f, -0.3f);
        materialShader->setUniformValue("dirLight.ambient", lightColor * 0.05f);
        materialShader->setUniformValue("dirLight.diffuse", lightColor * 0.4f);
        materialShader->setUniformValue("dirLight.specular", 0.5f, 0.5f, 0.5f);
        materialShader->setUniformValue("pointLights[0].position", lightPositions[0]);
        materialShader->setUniformValue("pointLights[0].ambient", lightColor * 0.05f);
        materialShader->setUniformValue("pointLights[0].diffuse", lightColor * 0.8f);
        materialShader->setUniformValue("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("pointLights[0].constant", 1.0f);
        materialShader->setUniformValue("pointLights[0].linear", 0.09f);
        materialShader->setUniformValue("pointLights[0].quadratic", 0.032f);
        materialShader->setUniformValue("pointLights[1].position", lightPositions[1]);
        materialShader->setUniformValue("pointLights[1].ambient", lightColor * 0.05f);
        materialShader->setUniformValue("pointLights[1].diffuse", lightColor * 0.8f);
        materialShader->setUniformValue("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("pointLights[1].constant", 1.0f);
        materialShader->setUniformValue("pointLights[1].linear", 0.09f);
        materialShader->setUniformValue("pointLights[1].quadratic", 0.032f);
        materialShader->setUniformValue("pointLights[2].position", lightPositions[2]);
        materialShader->setUniformValue("pointLights[2].ambient", lightColor * 0.05f);
        materialShader->setUniformValue("pointLights[2].diffuse", lightColor * 0.8f);
        materialShader->setUniformValue("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("pointLights[2].constant", 1.0f);
        materialShader->setUniformValue("pointLights[2].linear", 0.09f);
        materialShader->setUniformValue("pointLights[2].quadratic", 0.032f);
        materialShader->setUniformValue("pointLights[3].position", lightPositions[3]);
        materialShader->setUniformValue("pointLights[3].ambient", lightColor * 0.05f);
        materialShader->setUniformValue("pointLights[3].diffuse", lightColor * 0.8f);
        materialShader->setUniformValue("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("pointLights[3].constant", 1.0f);
        materialShader->setUniformValue("pointLights[3].linear", 0.09f);
        materialShader->setUniformValue("pointLights[3].quadratic", 0.032f);
        materialShader->setUniformValue("spotLight.position", camera->position());
        materialShader->setUniformValue("spotLight.direction", camera->front());
        materialShader->setUniformValue("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        materialShader->setUniformValue("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("spotLight.specular", 1.0f, 1.0f, 1.0f);
        materialShader->setUniformValue("spotLight.constant", 1.0f);
        materialShader->setUniformValue("spotLight.linear", 0.09f);
        materialShader->setUniformValue("spotLight.quadratic", 0.032f);
        materialShader->setUniformValue("spotLight.innerCutOff", (GLfloat)cos(qDegreesToRadians(12.5)));
        materialShader->setUniformValue("spotLight.outerCutOff", (GLfloat)cos(qDegreesToRadians(15.0)));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        for (int i = 0; i < d_ptr->cubeWorldPosition.size(); i++)
        {
            model.setToIdentity();
            model.rotate(glfwGetTime() * 3, 1.0f, 0.0f);
            model.translate(d_ptr->cubeWorldPosition.at(i));
            model.rotate(20.0f * i, 1.0f, 0.3f, 0.5f);
            materialShader->setUniformValue("model", model);
            d_ptr->engine->renderCube(materialShader);
        }
        // draw light source
        sourceShader->bind();
        sourceShader->setUniformValue("projection", projection);
        sourceShader->setUniformValue("view", view);
        sourceShader->setUniformValue("lightColor", lightColor);
        for (int i = 0; i < lightPositions.size(); i++)
        {
            model.setToIdentity();
            model.translate(lightPositions.at(i));
            model.scale(0.2f);
            sourceShader->setUniformValue("model", model);
            d_ptr->engine->renderSphere(sourceShader);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE
