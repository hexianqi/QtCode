#include "HLearnGLFW_p.h"
#include "HOpenGLHelper.h"
#include "HOpenGLShaderProgram.h"
#include "HGeometryEngine.h"
#include <QtGui/QMatrix4x4>

using namespace std;

HE_BEGIN_NAMESPACE

int HLearnGLFW::testFramebuffers()
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
    shader1->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/texture_obj.vs");
    shader1->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/texture_obj.fs");
    auto shader2 = new HOpenGLShaderProgram(this);
    shader2->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/framebuffer.vs");
    shader2->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/framebuffer.fs");

    // load and create a texture
    auto texture1 = HOpenGLHelper::loadTexture(":/textures/marble.jpg");
    auto texture2 = HOpenGLHelper::loadTexture(":/textures/metal.png");

    // shader configuration
    shader1->bind();
    shader1->setUniformValue("texture1", 0);
    shader2->bind();
    shader2->setUniformValue("texture1", 0);

    // framebuffer configuration
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // create a color attachment texture
    auto texture = HOpenGLHelper::createTexture(d_ptr->width, d_ptr->height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, d_ptr->width, d_ptr->height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // per-frame time logic
        perFrameTime();
        // input
        processInput(d_ptr->window);
        // first render pass: mirror texture.
        // bind to framebuffer and draw to color texture as we normally
        // would, but with the view camera reversed.
        // bind to framebuffer and draw scene as we normally would to color texture
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // set uniforms
        QMatrix4x4 projection, view, model;
        projection.perspective(camera->zoom(), 1.0 * d_ptr->width / d_ptr->height, 0.1f, 100.0f);
        view = camera->viewMatrix();
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        model.setToIdentity();
        model.translate(-1.0f, 0.0f, -1.0f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.translate(2.0f, 0.0f, 0.0f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        model.setToIdentity();
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderPlane(shader1);
        // second render pass: draw as normal
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        shader1->bind();
        shader1->setUniformValue("projection", projection);
        shader1->setUniformValue("view", view);
        model.setToIdentity();
        model.translate(-1.0f, 0.0f, -1.0f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        model.setToIdentity();
        model.translate(2.0f, 0.0f, 0.0f);
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderCube(shader1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        model.setToIdentity();
        shader1->setUniformValue("model", model);
        d_ptr->engine->renderPlane(shader1);

        // now draw the mirror quad with screen texture
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        glBindTexture(GL_TEXTURE_2D, texture);
        shader2->bind();
        model.setToIdentity();
        model.translate(0.8, 0.8);
        model.scale(0.2);
        shader2->setUniformValue("model", model);
        shader2->setUniformValue("processing", 1);
        d_ptr->engine->renderScreen(shader2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE
