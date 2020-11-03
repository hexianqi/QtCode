#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLModel.h"
#include "stb_image.h"
#include <QtGui/QImage>
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

void HLearnGLFW::renderSphere()
{
    // initialize (if necessary)
    if (d_ptr->sphereVAO == 0)
    {
        QVector<QVector3D> positions;
        QVector<QVector2D> uv;
        QVector<QVector3D> normals;
        QVector<unsigned int> indices;

        const int X_SEGMENTS = 64;
        const int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (int x = 0; x <= X_SEGMENTS; ++x)
            {
                auto xSegment = 1.0f * x / X_SEGMENTS;
                auto ySegment = 1.0f * y / Y_SEGMENTS;
                auto xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                auto yPos = std::cos(ySegment * PI);
                auto zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions << QVector3D(xPos, yPos, zPos);
                uv << QVector2D(xSegment, ySegment);
                normals << QVector3D(xPos, yPos, zPos);
            }
        }

        bool oddRow = false;
        for (int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices <<  y      * (X_SEGMENTS + 1) + x
                            << (y + 1) * (X_SEGMENTS + 1) + x;
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices << (y + 1) * (X_SEGMENTS + 1) + x
                            <<  y      * (X_SEGMENTS + 1) + x;
                }
            }
            oddRow = !oddRow;
        }

        auto positionSize = sizeof(QVector3D) * positions.size();
        auto uvSize = sizeof(QVector2D) * uv.size();
        auto normalsSize = sizeof(QVector3D) * normals.size();
        auto indicesSize = sizeof(unsigned int) * indices.size();
        d_ptr->sphereIndexCount = indices.size();

        unsigned int VBO, EBO;
        glGenVertexArrays(1, &d_ptr->sphereVAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(d_ptr->sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, positionSize + uvSize + normalsSize, nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, positionSize, positions.data());
        glBufferSubData(GL_ARRAY_BUFFER, positionSize, uvSize, uv.data());
        glBufferSubData(GL_ARRAY_BUFFER, positionSize + uvSize, normalsSize, normals.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(positionSize));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(positionSize + uvSize));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(d_ptr->sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, d_ptr->sphereIndexCount, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

int HLearnGLFW::testPBR()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr.fs");

    // lighting info
    QVector<QVector3D> lightPos, lightColors;
    lightPos << QVector3D(-10.0f,  10.0f, 10.0f)
             << QVector3D( 10.0f,  10.0f, 10.0f)
             << QVector3D(-10.0f, -10.0f, 10.0f)
             << QVector3D( 10.0f, -10.0f, 10.0f);
    lightColors << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f);

    int nrRows    = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    // initialize static shader uniforms before rendering
    QMatrix4x4 projection, view, model;
    projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);

    shader->bind();
    shader->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    shader->setUniformValue("ao", 1.0f);
    shader->setUniformValue("projection", projection);

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

        QMatrix4x4 view, model;
        view = camera->viewMatrix();
        shader->bind();
        shader->setUniformValue("view", view);
        shader->setUniformValue("camPos", camera->position());
        for (int row = 0; row < nrRows; ++row)
        {
            shader->setUniformValue("metallic", 1.0f * row / nrRows);
            for (int col = 0; col < nrColumns; ++col)
            {

                model.setToIdentity();
                model.translate((col - (nrColumns / 2)) * spacing, (row - (nrRows / 2)) * spacing, 0.0f);
                // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off on direct lighting.
                shader->setUniformValue("roughness", qBound(0.05f, 1.0f * col / nrColumns, 1.0f));
                shader->setUniformValue("model", model);
                renderSphere();
            }
        }

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and
        // keeps the codeprint small.
        for (int i = 0; i < lightPos.size(); ++i)
        {
            auto newPos = lightPos[i] + QVector3D(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            model.setToIdentity();
            model.translate(newPos);
            model.scale(0.5f);
            shader->setUniformValue("model", model);
            shader->setUniformValue(tr("lightPositions[%1]").arg(i).toStdString().c_str(), newPos);
            shader->setUniformValue(tr("lightColors[%1]").arg(i).toStdString().c_str(), lightColors[i]);
            renderSphere();
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testPBR2()
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr2.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr2.fs");

    // load PBR material textures
    auto albedo    = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/albedo.png");
    auto normal    = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/normal.png");
    auto metallic  = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/metallic.png");
    auto roughness = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/roughness.png");
    auto ao        = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/ao.png");

    // lighting info
    QVector3D lightPos(0.0f, 0.0f, 10.0f);
    QVector3D lightColors(150.0f, 150.0f, 150.0f);

    // initialize static shader uniforms before rendering
    QMatrix4x4 projection, view, model;
    projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);

    shader->bind();
    shader->setUniformValue("albedoMap", 0);
    shader->setUniformValue("normalMap", 1);
    shader->setUniformValue("metallicMap", 2);
    shader->setUniformValue("roughnessMap", 3);
    shader->setUniformValue("aoMap", 4);
    shader->setUniformValue("projection", projection);

    int nrRows    = 7;
    int nrColumns = 7;
    float spacing = 2.5;

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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, albedo);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, metallic);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, roughness);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, ao);

        QMatrix4x4 view, model;
        view = camera->viewMatrix();
        shader->bind();
        shader->setUniformValue("view", view);
        shader->setUniformValue("camPos", camera->position());
        for (int row = 0; row < nrRows; ++row)
        {
            shader->setUniformValue("metallic", 1.0f * row / nrRows);
            for (int col = 0; col < nrColumns; ++col)
            {
                model.setToIdentity();
                model.translate((col - (nrColumns / 2)) * spacing, (row - (nrRows / 2)) * spacing, 0.0f);
                shader->setUniformValue("model", model);
                renderSphere();
            }
        }

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and
        // keeps the codeprint small.
        auto newPos = lightPos + QVector3D(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        model.setToIdentity();
        model.translate(newPos);
        model.scale(0.5f);
        shader->setUniformValue("model", model);
        shader->setUniformValue("lightPositions[0]", newPos);
        shader->setUniformValue("lightColors[0]", lightColors);
        renderSphere();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testPBR3()
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
    glDepthFunc(GL_LEQUAL);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr3.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr3.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/equirectangular_to_cubemap.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/background.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/background.fs");

    // lighting info
    QVector<QVector3D> lightPos, lightColors;
    lightPos << QVector3D(-10.0f,  10.0f, 10.0f)
             << QVector3D( 10.0f,  10.0f, 10.0f)
             << QVector3D(-10.0f, -10.0f, 10.0f)
             << QVector3D( 10.0f, -10.0f, 10.0f);
    lightColors << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f);

    // pbr: setup framebuffer
    unsigned int captureFBO, captureRBO;
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);
    // pbr: load the HDR environment map
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float *data = stbi_loadf("hdr\\newport_loft.hdr", &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    if (data)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        qDebug() << "Failed to load HDR image.";
    }

    // pbr: setup cubemap to render to and attach to framebuffer
    unsigned int envCubemap;
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    QMatrix4x4 captureProjection;
    captureProjection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> captureViews(6);
    captureViews[0].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[1].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[2].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    captureViews[3].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    captureViews[4].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[5].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    shader2->bind();
    shader2->setUniformValue("equirectangularMap", 0);
    shader2->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);
    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (int i = 0; i < 6; ++i)
    {
        shader2->setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // initialize static shader uniforms before rendering
    QMatrix4x4 projection, view, model;
    projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);

    shader1->bind();
    shader1->setUniformValue("projection", projection);
    shader1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    shader1->setUniformValue("ao", 1.0f);
    shader3->bind();
    shader3->setUniformValue("projection", projection);
    shader3->setUniformValue("environmentMap", 0);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(d_ptr->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

    int nrRows    = 7;
    int nrColumns = 7;
    float spacing = 2.5;

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

        QMatrix4x4 view, model;
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("camPos", camera->position());
        for (int row = 0; row < nrRows; ++row)
        {
            shader1->setUniformValue("metallic", 1.0f * row / nrRows);
            for (int col = 0; col < nrColumns; ++col)
            {

                model.setToIdentity();
                model.translate((col - (nrColumns / 2)) * spacing, (row - (nrRows / 2)) * spacing, 0.0f);
                // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off on direct lighting.
                shader1->setUniformValue("roughness", qBound(0.05f, 1.0f * col / nrColumns, 1.0f));
                shader1->setUniformValue("model", model);
                renderSphere();
            }
        }

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and
        // keeps the codeprint small.
        for (int i = 0; i < lightPos.size(); ++i)
        {
            auto newPos = lightPos[i] + QVector3D(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            model.setToIdentity();
            model.translate(newPos);
            model.scale(0.5f);
            shader1->setUniformValue("model", model);
            shader1->setUniformValue(tr("lightPositions[%1]").arg(i).toStdString().c_str(), newPos);
            shader1->setUniformValue(tr("lightColors[%1]").arg(i).toStdString().c_str(), lightColors[i]);
            renderSphere();
        }

        // render skybox (render as last to prevent overdraw)
        shader3->bind();
        shader3->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        renderCube();

//        shader2->bind();
//        shader2->setUniformValue("view", view);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, hdrTexture);
//        renderCube();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testPBR4()
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
    glDepthFunc(GL_LEQUAL);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr4.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr4.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/equirectangular_to_cubemap.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/background.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/background.fs");
    auto shader4 = new HOpenGLShaderProgram(this);
    shader4->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader4->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/irradiance_convolution.fs");

    // lighting info
    QVector<QVector3D> lightPos, lightColors;
    lightPos << QVector3D(-10.0f,  10.0f, 10.0f)
             << QVector3D( 10.0f,  10.0f, 10.0f)
             << QVector3D(-10.0f, -10.0f, 10.0f)
             << QVector3D( 10.0f, -10.0f, 10.0f);
    lightColors << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f);

    // pbr: setup framebuffer
    unsigned int captureFBO, captureRBO;
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);
    // pbr: load the HDR environment map
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float *data = stbi_loadf("hdr\\newport_loft.hdr", &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    if (data)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        qDebug() << "Failed to load HDR image.";
    }

    // pbr: setup cubemap to render to and attach to framebuffer
    unsigned int envCubemap;
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    QMatrix4x4 captureProjection;
    captureProjection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> captureViews(6);
    captureViews[0].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[1].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[2].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    captureViews[3].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    captureViews[4].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[5].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    shader2->bind();
    shader2->setUniformValue("equirectangularMap", 0);
    shader2->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);
    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (int i = 0; i < 6; ++i)
    {
        shader2->setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    unsigned int irradianceMap;
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    shader4->bind();
    shader4->setUniformValue("environmentMap", 0);
    shader4->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        shader4->setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // initialize static shader uniforms before rendering
    QMatrix4x4 projection, view, model;
    projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);

    shader1->bind();
    shader1->setUniformValue("projection", projection);
    shader1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    shader1->setUniformValue("ao", 1.0f);
    shader1->setUniformValue("irradianceMap", 0);
    shader3->bind();
    shader3->setUniformValue("projection", projection);
    shader3->setUniformValue("environmentMap", 0);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(d_ptr->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

    int nrRows    = 7;
    int nrColumns = 7;
    float spacing = 2.5;

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

        QMatrix4x4 view, model;
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("camPos", camera->position());
        // bind pre-computed IBL data
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
        for (int row = 0; row < nrRows; ++row)
        {
            shader1->setUniformValue("metallic", 1.0f * row / nrRows);
            for (int col = 0; col < nrColumns; ++col)
            {

                model.setToIdentity();
                model.translate((col - (nrColumns / 2)) * spacing, (row - (nrRows / 2)) * spacing, 0.0f);
                // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off on direct lighting.
                shader1->setUniformValue("roughness", qBound(0.05f, 1.0f * col / nrColumns, 1.0f));
                shader1->setUniformValue("model", model);
                renderSphere();
            }
        }

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and
        // keeps the codeprint small.
        for (int i = 0; i < lightPos.size(); ++i)
        {
            auto newPos = lightPos[i] + QVector3D(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            model.setToIdentity();
            model.translate(newPos);
            model.scale(0.5f);
            shader1->setUniformValue("model", model);
            shader1->setUniformValue(tr("lightPositions[%1]").arg(i).toStdString().c_str(), newPos);
            shader1->setUniformValue(tr("lightColors[%1]").arg(i).toStdString().c_str(), lightColors[i]);
            renderSphere();
        }

        // render skybox (render as last to prevent overdraw)
        shader3->bind();
        shader3->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        renderCube();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testPBR5()
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
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr5.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr5.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/equirectangular_to_cubemap.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/background.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/background.fs");
    auto shader4 = new HOpenGLShaderProgram(this);
    shader4->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader4->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/irradiance_convolution.fs");
    auto shader5 = new HOpenGLShaderProgram(this);
    shader5->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader5->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/prefilter.fs");
    auto shader6 = new HOpenGLShaderProgram(this);
    shader6->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/brdf.vs");
    shader6->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/brdf.fs");

    // lighting info
    QVector<QVector3D> lightPos, lightColors;
    lightPos << QVector3D(-10.0f,  10.0f, 10.0f)
             << QVector3D( 10.0f,  10.0f, 10.0f)
             << QVector3D(-10.0f, -10.0f, 10.0f)
             << QVector3D( 10.0f, -10.0f, 10.0f);
    lightColors << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f);

    // pbr: setup framebuffer
    unsigned int captureFBO, captureRBO;
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);
    // pbr: load the HDR environment map
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float *data = stbi_loadf("hdr\\newport_loft.hdr", &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    if (data)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        qDebug() << "Failed to load HDR image.";
    }

    // pbr: setup cubemap to render to and attach to framebuffer
    unsigned int envCubemap;
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    QMatrix4x4 captureProjection;
    captureProjection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> captureViews(6);
    captureViews[0].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[1].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[2].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    captureViews[3].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    captureViews[4].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[5].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    shader2->bind();
    shader2->setUniformValue("equirectangularMap", 0);
    shader2->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);
    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (int i = 0; i < 6; ++i)
    {
        shader2->setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    unsigned int irradianceMap;
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    shader4->bind();
    shader4->setUniformValue("environmentMap", 0);
    shader4->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        shader4->setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------
    unsigned int prefilterMap;
    glGenTextures(1, &prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minifcation filter to mip_linear
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
    shader5->bind();
    shader5->setUniformValue("environmentMap", 0);
    shader5->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth  = 128 * std::pow(0.5, mip);
        unsigned int mipHeight = 128 * std::pow(0.5, mip);
        glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        shader5->setUniformValue("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            shader5->setUniformValue("view", captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderCube();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: generate a 2D LUT from the BRDF equations used.
    unsigned int brdfLUTTexture;
    glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    glViewport(0, 0, 512, 512);
    shader6->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // initialize static shader uniforms before rendering
    QMatrix4x4 projection, view, model;
    projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);

    shader1->bind();
    shader1->setUniformValue("projection", projection);
    shader1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    shader1->setUniformValue("ao", 1.0f);
    shader1->setUniformValue("irradianceMap", 0);
    shader1->setUniformValue("prefilterMap", 1);
    shader1->setUniformValue("brdfLUT", 2);
    shader3->bind();
    shader3->setUniformValue("projection", projection);
    shader3->setUniformValue("environmentMap", 0);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(d_ptr->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

    int nrRows    = 7;
    int nrColumns = 7;
    float spacing = 2.5;

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

        QMatrix4x4 view, model;
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("camPos", camera->position());
        // bind pre-computed IBL data
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
        for (int row = 0; row < nrRows; ++row)
        {
            shader1->setUniformValue("metallic", 1.0f * row / nrRows);
            for (int col = 0; col < nrColumns; ++col)
            {

                model.setToIdentity();
                model.translate((col - (nrColumns / 2)) * spacing, (row - (nrRows / 2)) * spacing, 0.0f);
                // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off on direct lighting.
                shader1->setUniformValue("roughness", qBound(0.05f, 1.0f * col / nrColumns, 1.0f));
                shader1->setUniformValue("model", model);
                renderSphere();
            }
        }

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and
        // keeps the codeprint small.
        for (int i = 0; i < lightPos.size(); ++i)
        {
            auto newPos = lightPos[i] + QVector3D(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            model.setToIdentity();
            model.translate(newPos);
            model.scale(0.5f);
            shader1->setUniformValue("model", model);
            shader1->setUniformValue(tr("lightPositions[%1]").arg(i).toStdString().c_str(), newPos);
            shader1->setUniformValue(tr("lightColors[%1]").arg(i).toStdString().c_str(), lightColors[i]);
            renderSphere();
        }

        // render skybox (render as last to prevent overdraw)
        shader3->bind();
        shader3->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        renderCube();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

int HLearnGLFW::testPBR6()
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
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr6.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr6.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/equirectangular_to_cubemap.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/background.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/background.fs");
    auto shader4 = new HOpenGLShaderProgram(this);
    shader4->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader4->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/irradiance_convolution.fs");
    auto shader5 = new HOpenGLShaderProgram(this);
    shader5->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader5->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/prefilter.fs");
    auto shader6 = new HOpenGLShaderProgram(this);
    shader6->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/brdf.vs");
    shader6->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/brdf.fs");

    // load PBR material textures
    // --------------------------
    // rusted iron
    unsigned int ironAlbedoMap = HOpenGLHelper::loadTexture("resources/textures/pbr/rusted_iron/albedo.png");
    unsigned int ironNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/normal.png");
    unsigned int ironMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/metallic.png");
    unsigned int ironRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/roughness.png");
    unsigned int ironAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/ao.png");

    // gold
    unsigned int goldAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/albedo.png");
    unsigned int goldNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/normal.png");
    unsigned int goldMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/metallic.png");
    unsigned int goldRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/roughness.png");
    unsigned int goldAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/ao.png");

    // grass
    unsigned int grassAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/albedo.png");
    unsigned int grassNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/normal.png");
    unsigned int grassMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/metallic.png");
    unsigned int grassRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/roughness.png");
    unsigned int grassAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/ao.png");

    // plastic
    unsigned int plasticAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/albedo.png");
    unsigned int plasticNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/normal.png");
    unsigned int plasticMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/metallic.png");
    unsigned int plasticRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/roughness.png");
    unsigned int plasticAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/ao.png");

    // wall
    unsigned int wallAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/albedo.png");
    unsigned int wallNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/normal.png");
    unsigned int wallMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/metallic.png");
    unsigned int wallRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/roughness.png");
    unsigned int wallAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/ao.png");


    // lighting info
    QVector<QVector3D> lightPos, lightColors;
    lightPos << QVector3D(-10.0f,  10.0f, 10.0f)
             << QVector3D( 10.0f,  10.0f, 10.0f)
             << QVector3D(-10.0f, -10.0f, 10.0f)
             << QVector3D( 10.0f, -10.0f, 10.0f);
    lightColors << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f)
                << QVector3D(300.0f, 300.0f, 300.0f);

    // pbr: setup framebuffer
    unsigned int captureFBO, captureRBO;
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);
    // pbr: load the HDR environment map
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float *data = stbi_loadf("hdr\\newport_loft.hdr", &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    if (data)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        qDebug() << "Failed to load HDR image.";
    }

    // pbr: setup cubemap to render to and attach to framebuffer
    unsigned int envCubemap;
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
    QMatrix4x4 captureProjection;
    captureProjection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> captureViews(6);
    captureViews[0].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[1].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[2].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    captureViews[3].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    captureViews[4].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    captureViews[5].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    shader2->bind();
    shader2->setUniformValue("equirectangularMap", 0);
    shader2->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);
    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (int i = 0; i < 6; ++i)
    {
        shader2->setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    unsigned int irradianceMap;
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

    // pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
    shader4->bind();
    shader4->setUniformValue("environmentMap", 0);
    shader4->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        shader4->setUniformValue("view", captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------
    unsigned int prefilterMap;
    glGenTextures(1, &prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minifcation filter to mip_linear
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
    shader5->bind();
    shader5->setUniformValue("environmentMap", 0);
    shader5->setUniformValue("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth  = 128 * std::pow(0.5, mip);
        unsigned int mipHeight = 128 * std::pow(0.5, mip);
        glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        shader5->setUniformValue("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            shader5->setUniformValue("view", captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderCube();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: generate a 2D LUT from the BRDF equations used.
    unsigned int brdfLUTTexture;
    glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    glViewport(0, 0, 512, 512);
    shader6->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // initialize static shader uniforms before rendering
    QMatrix4x4 projection, view, model;
    projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);

    shader1->bind();
    shader1->setUniformValue("projection", projection);
    shader1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    shader1->setUniformValue("ao", 1.0f);
    shader1->setUniformValue("irradianceMap", 0);
    shader1->setUniformValue("prefilterMap", 1);
    shader1->setUniformValue("brdfLUT", 2);
    shader1->setUniformValue("albedoMap", 3);
    shader1->setUniformValue("normalMap", 4);
    shader1->setUniformValue("metallicMap", 5);
    shader1->setUniformValue("roughnessMap", 6);
    shader1->setUniformValue("aoMap", 7);
    shader3->bind();
    shader3->setUniformValue("projection", projection);
    shader3->setUniformValue("environmentMap", 0);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(d_ptr->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

    int nrRows    = 7;
    int nrColumns = 7;
    float spacing = 2.5;

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

        QMatrix4x4 view, model;
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("view", view);
        shader1->setUniformValue("camPos", camera->position());
        // bind pre-computed IBL data
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
        // rusted iron
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, ironAlbedoMap);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, ironNormalMap);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, ironMetallicMap);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, ironRoughnessMap);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, ironAOMap);
        for (int row = 0; row < nrRows; ++row)
        {
            shader1->setUniformValue("metallic", 1.0f * row / nrRows);
            for (int col = 0; col < nrColumns; ++col)
            {

                model.setToIdentity();
                model.translate((col - (nrColumns / 2)) * spacing, (row - (nrRows / 2)) * spacing, 0.0f);
                // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off on direct lighting.
                shader1->setUniformValue("roughness", qBound(0.05f, 1.0f * col / nrColumns, 1.0f));
                shader1->setUniformValue("model", model);
                renderSphere();
            }
        }

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and
        // keeps the codeprint small.
        for (int i = 0; i < lightPos.size(); ++i)
        {
            auto newPos = lightPos[i] + QVector3D(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            model.setToIdentity();
            model.translate(newPos);
            model.scale(0.5f);
            shader1->setUniformValue("model", model);
            shader1->setUniformValue(tr("lightPositions[%1]").arg(i).toStdString().c_str(), newPos);
            shader1->setUniformValue(tr("lightColors[%1]").arg(i).toStdString().c_str(), lightColors[i]);
            renderSphere();
        }

        // render skybox (render as last to prevent overdraw)
        shader3->bind();
        shader3->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        renderCube();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
