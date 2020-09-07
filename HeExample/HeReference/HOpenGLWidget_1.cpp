#include "HOpenGLWidget_1_p.h"
#include <QtCore/QTimer>
#include <GL/glu.h>

HE_REFERENCE_BEGIN_NAMESPACE

HOpenGLWidget_1::HOpenGLWidget_1(QWidget *parent) :
    QOpenGLWidget(parent),
    d_ptr(new HOpenGLWidget_1Private)
{
    init();
}

HOpenGLWidget_1::~HOpenGLWidget_1()
{
}

void HOpenGLWidget_1::initializeGL()
{
    // 启用smooth shading(阴影平滑)
    glShadeModel(GL_SMOOTH);
    // 设置清楚屏幕所用的颜色：色彩值范1围从0.0-1.0 (R G B A) 清屏时A不起作用
    glClearColor(0.1, 0.1, 0.4, 1.0);
    // 设置深度缓存
    glClearDepth(1.0);
    // 启用深度测试
    glEnable(GL_DEPTH_TEST);
    // 设置深度测试的类型
    glDepthFunc(GL_LEQUAL);
    // 设置希望得到最好的透视修正
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void HOpenGLWidget_1::resizeGL(int w, int h)
{
    // 防止height为0
    if (h == 0)
        h = 1;
    // 重置当前的视口
    glViewport(0, 0, w, h);
    // 选择投影矩阵
    glMatrixMode(GL_PROJECTION);
    // 重置观察矩阵/投影矩阵 当调用次函数，实际将当前点移到了屏幕中心
    glLoadIdentity();
    // 建立透视投影矩阵,需要<GL/glu.h>头文件
    gluPerspective(45.0, 1.0 * w / h, 0.1, 100.0);
    // 选择模型观察矩阵
    glMatrixMode(GL_MODELVIEW);
    // 重置观察矩阵/投影矩阵
    glLoadIdentity();
}

void HOpenGLWidget_1::paintGL()
{
    // 清除屏幕和深度缓存
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 重置观察矩阵/投影矩阵(X坐标轴从左至右，Y坐标轴从下至上，Z坐标轴从里至外)
    // OpenGL屏幕中心的坐标值是X和Y轴上的0.0点
    // 中心左面的坐标值是负值，右面是正值。
    // 移向屏幕顶端是正值，移向屏幕底端是负值。
    // 移入屏幕深处是负值，移出屏幕则是正值。
    glLoadIdentity();
    // 沿着X、Y、Z轴移动
    // X轴左移1.5个单位，Y轴不动(0.0)，最后移入屏幕6.0个单位
    // 注意在glTranslatef(x, y, z)中当您移动的时候，
    // 您并不是相对屏幕中心移动，而是相对与当前所在的屏幕位置
    glTranslatef(-1.5, 0.0, -6.0);
    // 让对象绕某个轴旋转 绕 Y 轴旋转三角形
    // 注意：X轴旋转，X,Y,Z可调整绕哪个轴
    glRotatef(d_ptr->tri, 0.0, 1.0, 0.0);
    // 以目前所在的点为画图原点(0,0,0) 开始相对原点坐标画三角形
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();
    // 重置模型观察矩阵 重置模型观察矩阵之后，X、Y、Z轴都以复位
    glLoadIdentity();
    glTranslatef(1.5, 0.0,  -6.0);            // 移动到点
    // 绕 X 轴旋转四边形 注意：X轴旋转，X,Y,Z可调整绕哪个轴
    glRotatef(d_ptr->quad, 1.0, 0.0, 0.0);
    // 以目前所在的点为画图原点(0,0,0) 开始相对原点坐标画四边形
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0); // 右上定点
    glVertex3f(1.0, -1.0, 0.0); // 右下定点
    glVertex3f(-1.0, -1.0, 0.0); // 坐下定点
    glEnd();
}

void HOpenGLWidget_1::init()
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(10);
    connect(d_ptr->timer, &QTimer::timeout, this, &HOpenGLWidget_1::rotate);
    d_ptr->timer->start();
}

void HOpenGLWidget_1::rotate()
{
    d_ptr->tri += 1;
    d_ptr->quad += 1;
    update();
}

HE_REFERENCE_END_NAMESPACE
