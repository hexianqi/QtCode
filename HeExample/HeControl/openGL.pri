HEADERS += \
    $$PWD/HAbstractShaderEngine.h \
    $$PWD/HAbstractShaderEngine_p.h \
    $$PWD/HGeometryEngine.h \
    $$PWD/HGeometryEngine_p.h \
    $$PWD/HOpenGLCamera.h \
    $$PWD/HOpenGLCamera_p.h \
    $$PWD/HOpenGLDemoWidget.h \
    $$PWD/HOpenGLDemoWidget_p.h \
    $$PWD/HOpenGLMesh.h \
    $$PWD/HOpenGLMesh_p.h \
    $$PWD/HOpenGLModel.h \
    $$PWD/HOpenGLModel_p.h \
    $$PWD/HOpenGLWidget.h \
    $$PWD/HOpenGLWidget_p.h \
    $$PWD/HShaderEngine.h \
    $$PWD/HShaderEngine_PBR.h \
    $$PWD/HShaderEngine_PBR_p.h \
    $$PWD/HShaderEngine_p.h \
    $$PWD/HTextEngine.h \
    $$PWD/HTextEngine_p.h \
    $$PWD/IShaderEngine.h \
    $$PWD/stb_image.h

SOURCES += \
    $$PWD/HAbstractShaderEngine.cpp \
    $$PWD/HGeometryEngine.cpp \
    $$PWD/HOpenGLCamera.cpp \
    $$PWD/HOpenGLDemoWidget.cpp \
    $$PWD/HOpenGLMesh.cpp \
    $$PWD/HOpenGLModel.cpp \
    $$PWD/HOpenGLWidget.cpp \
    $$PWD/HShaderEngine.cpp \
    $$PWD/HShaderEngine_PBR.cpp \
    $$PWD/HTextEngine.cpp \
    $$PWD/stb_image.cpp

FORMS += \
    $$PWD/HOpenGLDemoWidget.ui

RESOURCES += \
    $$PWD/openGL.qrc

AssimpPath  = $$absolute_path("../../../modules/assimp", $$[QT_INSTALL_DATA])
FreeTypePath  = $$absolute_path("../../../modules/freetype", $$[QT_INSTALL_DATA])

LIBS        += \
            -L$$AssimpPath/lib -lassimp \
            -L$$FreeTypePath/lib -lfreetype \
            -L$$FreeTypePath/lib -lbz2 \
            -L$$FreeTypePath/lib -lz

INCLUDEPATH += \
            $$AssimpPath/include \
            $$FreeTypePath/include

include(breakout.pri)
