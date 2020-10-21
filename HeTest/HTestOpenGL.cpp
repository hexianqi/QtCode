#include "HTestOpenGL.h"
#include "HeReference/HOpenGLWidget_1.h"
#include "HeReference/HLearnGLFW.h"

HE_REFERENCE_USE_NAMESPACE

QWidget *HTestOpenGL::test1()
{
    return new HOpenGLWidget_1;
}

int HTestOpenGL::testGlfw()
{
    HLearnGLFW g;
//    g.setLightColorLoop(true);
    g.setLightPosLoop(true);
//    g.setLineMode(true);
    g.setEnableCursor(false);
    return g.testSSAO();
}
