#include "HTestOpenGL.h"
#include "HeReference/HLearnGLFW.h"
#include "HeReference/HBreakout.h"

HE_USE_NAMESPACE

int HTestOpenGL::testGlfw()
{
//    HLearnGLFW g;
//    g.setLightColorLoop(true);
//    g.setLightPosLoop(true);
//    g.setLineMode(true);
//    g.setEnableCursor(false);
//    return g.testText();
    HBreakout g;
    g.run();
    return 1;
}
