#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HOpenGLModel.h"
#include "HGeometryEngine.h"
#include "stb_image.h"
#include <QtGui/QImage>
#include <QtGui/QMatrix4x4>
#include <QtCore/QDebug>

HE_REFERENCE_BEGIN_NAMESPACE

unsigned int HLearnGLFW::loadCubemapFromHdr(const QString &fileName, int width, int height, int magFilter)
{
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/cubemap_from_equirectangular.fs");
    auto texture = HOpenGLHelper::loadTextureFromHdr(fileName);
    return createCubemap(shader, GL_TEXTURE_2D, texture, width, height, magFilter);
}

unsigned int HLearnGLFW::createCubemapIrradiance(unsigned int texture, int width, int height)
{
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/cubemap_irradiance_convolution.fs");
    return createCubemap(shader, GL_TEXTURE_CUBE_MAP, texture, width, height);
}

unsigned int HLearnGLFW::createCubemapPrefilter(unsigned int texture, int width, int height)
{
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/cubemap.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/cubemap_prefilter.fs");

    unsigned int fbo;
    auto cubemap = HOpenGLHelper::createCubemap(width, height, GL_LINEAR_MIPMAP_LINEAR);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    auto rbo = HOpenGLHelper::createRenderDepth(width, height);
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
    // set up projection and view matrices for capturing data onto the 6 cubemap face directions
    QMatrix4x4 projection;
    projection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> views(6);
    views[0].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[1].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[2].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    views[3].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    views[4].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[5].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    // render to cubemap
    shader->bind();
    shader->setUniformValue("texture1", 0);
    shader->setUniformValue("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        unsigned int mipWidth  = width * std::pow(0.5, mip);
        unsigned int mipHeight = height * std::pow(0.5, mip);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = 1.0  * mip / (maxMipLevels - 1);
        shader->setUniformValue("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            shader->setUniformValue("view", views[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap, mip);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            d_ptr->engine->renderCube(shader);
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &fbo);
    return cubemap;
}

unsigned int HLearnGLFW::createCubemap(HOpenGLShaderProgram *shader, unsigned int target, unsigned int texture, int width, int height, int magFilter)
{
    unsigned int fbo;
    auto cubemap = HOpenGLHelper::createCubemap(width, height, magFilter);
    auto rbo = HOpenGLHelper::createRenderDepth(width, height);
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
    // set up projection and view matrices for capturing data onto the 6 cubemap face directions
    QMatrix4x4 projection;
    projection.perspective(90.0f, 1.0f, 0.1f, 10.0f);
    QVector<QMatrix4x4> views(6);
    views[0].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[1].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(-1.0f,  0.0f,  0.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[2].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  1.0f,  0.0f), QVector3D(0.0f,  0.0f,  1.0f));
    views[3].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f, -1.0f,  0.0f), QVector3D(0.0f,  0.0f, -1.0f));
    views[4].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    views[5].lookAt(QVector3D(0.0f, 0.0f, 0.0f), QVector3D( 0.0f,  0.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f));
    // render cubemap
    shader->bind();
    shader->setUniformValue("texture1", 0);
    shader->setUniformValue("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(target, texture);
    glViewport(0, 0, width, height); // don't forget to configure the viewport to the capture dimensions.
    for (int i = 0; i < 6; i++)
    {
        shader->setUniformValue("view", views[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_ptr->engine->renderCube(shader);
    }
    if (magFilter >= GL_NEAREST_MIPMAP_NEAREST)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &fbo);
    return cubemap;
}

unsigned int HLearnGLFW::createTextureBrdf(int width, int height)
{
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/brdf.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/brdf.fs");

    unsigned int fbo;
    auto texture = HOpenGLHelper::createTextureF(width, height);
    auto rbo = HOpenGLHelper::createRenderDepth(width, height);
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->bind();
    d_ptr->engine->renderScreen(shader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &fbo);
    return texture;
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
        shader->setUniformValue("viewPos", camera->position());
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
                d_ptr->engine->renderSphere(shader);
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
            d_ptr->engine->renderSphere(shader);
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
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr.vs");
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
    int nrRows    = 7;
    int nrColumns = 7;
    float spacing = 2.5;

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
        shader->setUniformValue("viewPos", camera->position());
        for (int row = 0; row < nrRows; ++row)
        {
            shader->setUniformValue("metallic", 1.0f * row / nrRows);
            for (int col = 0; col < nrColumns; ++col)
            {
                model.setToIdentity();
                model.translate((col - (nrColumns / 2)) * spacing, (row - (nrRows / 2)) * spacing, 0.0f);
                shader->setUniformValue("model", model);
                d_ptr->engine->renderSphere(shader);
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
        d_ptr->engine->renderSphere(shader);

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

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/skybox2.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/skybox2.fs");

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

    // pbr: load the HDR environment map
    auto envCubemap = loadCubemapFromHdr(":/textures/hdr/newport_loft.hdr", 512, 512);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(d_ptr->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

    // initialize static shader uniforms before rendering
    QMatrix4x4 projection, view, model;
    projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);

    shader1->bind();
    shader1->setUniformValue("projection", projection);
    shader1->setUniformValue("albedo", 0.5f, 0.0f, 0.0f);
    shader1->setUniformValue("ao", 1.0f);
    shader3->bind();
    shader3->setUniformValue("projection", projection);
    shader3->setUniformValue("texture1", 0);

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
        shader1->setUniformValue("viewPos", camera->position());
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
                d_ptr->engine->renderSphere(shader1);
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
            d_ptr->engine->renderSphere(shader1);
        }

        // render skybox (render as last to prevent overdraw)
        shader3->bind();
        shader3->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        d_ptr->engine->renderSkybox(shader3);

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

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr4.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/skybox2.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/skybox2.fs");

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

    // load the HDR environment map
    auto envCubemap = loadCubemapFromHdr(":/textures/hdr/newport_loft.hdr", 512, 512);
    // create an irradiance cubemap
    auto irradianceCubemap = createCubemapIrradiance(envCubemap, 32, 32);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(d_ptr->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

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
    shader3->setUniformValue("texture1", 0);

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
        shader1->setUniformValue("viewPos", camera->position());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceCubemap);
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
                d_ptr->engine->renderSphere(shader1);
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
            d_ptr->engine->renderSphere(shader1);
        }

        // render skybox (render as last to prevent overdraw)
        shader3->bind();
        shader3->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        d_ptr->engine->renderSkybox(shader3);

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
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr5.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/skybox2.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/skybox2.fs");

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

    // load the HDR environment map
    auto envCubemap = loadCubemapFromHdr(":/textures/hdr/newport_loft.hdr", 512, 512, GL_LINEAR_MIPMAP_LINEAR);
    // create an irradiance cubemap
    auto irradianceCubemap = createCubemapIrradiance(envCubemap, 32, 32);
    // create a pre-filter cubemap
    auto prefilterCubemap = createCubemapPrefilter(envCubemap, 128, 128);
    // generate a 2D LUT from the BRDF equations used
    auto brdfLUTTexture = createTextureBrdf(512, 512);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(d_ptr->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

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
    shader3->setUniformValue("texture1", 0);

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
        shader1->setUniformValue("viewPos", camera->position());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceCubemap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterCubemap);
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
                d_ptr->engine->renderSphere(shader1);
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
            d_ptr->engine->renderSphere(shader1);
        }

        // render skybox (render as last to prevent overdraw)
        shader3->bind();
        shader3->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        d_ptr->engine->renderSkybox(shader3);

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
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // build and compile our shader program
    auto shader1 = new HOpenGLShaderProgram(this);
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/pbr.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/pbr6.fs");
    auto shader3 = new HOpenGLShaderProgram(this);
    shader3->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/skybox2.vs");
    shader3->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/skybox2.fs");

    // load PBR material textures
    // rusted iron
    auto ironAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/albedo.png");
    auto ironNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/normal.png");
    auto ironMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/metallic.png");
    auto ironRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/roughness.png");
    auto ironAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/rusted_iron/ao.png");
    // gold
    auto goldAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/albedo.png");
    auto goldNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/normal.png");
    auto goldMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/metallic.png");
    auto goldRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/roughness.png");
    auto goldAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/gold/ao.png");
    // grass
    auto grassAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/albedo.png");
    auto grassNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/normal.png");
    auto grassMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/metallic.png");
    auto grassRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/roughness.png");
    auto grassAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/grass/ao.png");
    // plastic
    auto plasticAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/albedo.png");
    auto plasticNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/normal.png");
    auto plasticMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/metallic.png");
    auto plasticRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/roughness.png");
    auto plasticAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/plastic/ao.png");
    // wall
    auto wallAlbedoMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/albedo.png");
    auto wallNormalMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/normal.png");
    auto wallMetallicMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/metallic.png");
    auto wallRoughnessMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/roughness.png");
    auto wallAOMap = HOpenGLHelper::loadTexture(":/textures/pbr/wall/ao.png");

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

    // load the HDR environment map
    auto envCubemap = loadCubemapFromHdr(":/textures/hdr/newport_loft.hdr", 512, 512, GL_LINEAR_MIPMAP_LINEAR);
    // create an irradiance cubemap
    auto irradianceCubemap = createCubemapIrradiance(envCubemap, 32, 32);
    // create a pre-filter cubemap
    auto prefilterCubemap = createCubemapPrefilter(envCubemap, 128, 128);
    // generate a 2D LUT from the BRDF equations used
    auto brdfLUTTexture = createTextureBrdf(512, 512);

    // then before rendering, configure the viewport to the original framebuffer's screen dimensions
    int scrWidth, scrHeight;
    glfwGetFramebufferSize(d_ptr->window, &scrWidth, &scrHeight);
    glViewport(0, 0, scrWidth, scrHeight);

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
    shader3->setUniformValue("texture1", 0);

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
        shader1->setUniformValue("viewPos", camera->position());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceCubemap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterCubemap);
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
        model.setToIdentity();
        model.translate(-5.0, 0.0, 2.0);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderSphere(shader1);
        // gold
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, goldAlbedoMap);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, goldNormalMap);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, goldMetallicMap);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, goldRoughnessMap);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, goldAOMap);
        model.setToIdentity();
        model.translate(-3.0, 0.0, 2.0);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderSphere(shader1);
        // grass
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, grassAlbedoMap);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, grassNormalMap);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, grassMetallicMap);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, grassRoughnessMap);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, grassAOMap);
        model.setToIdentity();
        model.translate(-1.0, 0.0, 2.0);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderSphere(shader1);
        // plastic
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, plasticAlbedoMap);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, plasticNormalMap);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, plasticMetallicMap);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, plasticRoughnessMap);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, plasticAOMap);
        model.setToIdentity();
        model.translate(1.0, 0.0, 2.0);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderSphere(shader1);
        // wall
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, wallAlbedoMap);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, wallNormalMap);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, wallMetallicMap);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, wallRoughnessMap);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, wallAOMap);
        model.setToIdentity();
        model.translate(3.0, 0.0, 2.0);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderSphere(shader1);

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
            d_ptr->engine->renderSphere(shader1);
        }

        // render skybox (render as last to prevent overdraw)
        shader3->bind();
        shader3->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        d_ptr->engine->renderSkybox(shader3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_REFERENCE_END_NAMESPACE
