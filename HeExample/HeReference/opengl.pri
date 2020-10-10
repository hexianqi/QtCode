HEADERS += \
    $$PWD/HLearnGLFW.h \
    $$PWD/HLearnGLFW_p.h \
    $$PWD/HOpenGLCamera.h \
    $$PWD/HOpenGLCamera_p.h \
    $$PWD/HOpenGLShaderProgram.h \
    $$PWD/HOpenGLShaderProgram_p.h \
    $$PWD/HOpenGLWidget_1.h \
    $$PWD/HOpenGLWidget_1_p.h

SOURCES += \
    $$PWD/HLearnGLFW.cpp \
    $$PWD/HLearnGLFW_Blending.cpp \
    $$PWD/HLearnGLFW_Camera.cpp \
    $$PWD/HLearnGLFW_Color.cpp \
    $$PWD/HLearnGLFW_Coordinate.cpp \
    $$PWD/HLearnGLFW_Cubemaps.cpp \
    $$PWD/HLearnGLFW_Framebuffers.cpp \
    $$PWD/HLearnGLFW_Geometry.cpp \
    $$PWD/HLearnGLFW_Light.cpp \
    $$PWD/HLearnGLFW_LightCaster.cpp \
    $$PWD/HLearnGLFW_LightMaps.cpp \
    $$PWD/HLearnGLFW_LightMult.cpp \
    $$PWD/HLearnGLFW_Materials.cpp \
    $$PWD/HLearnGLFW_Stencil.cpp \
    $$PWD/HLearnGLFW_Texture.cpp \
    $$PWD/HLearnGLFW_Triangle.cpp \
    $$PWD/HLearnGLFW_Ubo.cpp \
    $$PWD/HOpenGLCamera.cpp \
    $$PWD/HOpenGLShaderProgram.cpp \
    $$PWD/HOpenGLWidget_1.cpp \
    $$PWD/glad.c

GladPath     = $$absolute_path("../../../modules/glad", $$[QT_INSTALL_DATA])
GlfwPath     = $$absolute_path("../../../modules/glfw/win32", $$[QT_INSTALL_DATA])

LIBS        += \
            -L$$GlfwPath/lib-mingw -lglfw3 \
            -lgdi32 \
            -lglu32 \
            -lopengl32

INCLUDEPATH += \
            $$GladPath/include \
            $$GlfwPath/include
