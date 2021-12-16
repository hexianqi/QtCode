#include "HLearnGLFW_p.h"
#include "HOpenGLShaderProgram.h"
#include "HFreeType.h"
#include <QtGui/QMatrix4x4>

HE_BEGIN_NAMESPACE

int HLearnGLFW::testText()
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

    HFreeType ft;
    ft.setFont(":/fonts/Antonio-Bold.ttf", 64); // 显示中文需要中文字体

    // build and compile our shader program
    auto shader = new HOpenGLShaderProgram(this);
    shader->addShaderFromSourceFile(HOpenGLShader::Vertex,     ":/glsl/text.vs");
    shader->addShaderFromSourceFile(HOpenGLShader::Fragment,   ":/glsl/text.fs");

    QMatrix4x4 projection;
    projection.ortho(QRectF(0.0f, d_ptr->width, 0.0f,  d_ptr->height));
    shader->bind();
    shader->setUniformValue("projection", projection);
    shader->setUniformValue("texture1", 0);

    // render loop
    while (!glfwWindowShouldClose(d_ptr->window))
    {
        // input
        processInput(d_ptr->window);
        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->bind();
        shader->setUniformValue("color", QVector3D(0.5, 0.8f, 0.2f));
        ft.renderText("This is sample text", QVector2D(25.0, 25.0));
        shader->setUniformValue("color", QVector3D(0.3, 0.7f, 0.9f));
        ft.renderText("测试汉字\n测试行", QVector2D(400, 400.0));

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(d_ptr->window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

HE_END_NAMESPACE
