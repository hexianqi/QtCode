HEADERS += \
    $$PWD/HLearnGLFW.h \
    $$PWD/HLearnGLFW_p.h \
    $$PWD/HOpenGLCamera.h \
    $$PWD/HOpenGLCamera_p.h \
    $$PWD/HOpenGLHelper.h \
    $$PWD/HOpenGLMesh.h \
    $$PWD/HOpenGLMesh_p.h \
    $$PWD/HOpenGLModel.h \
    $$PWD/HOpenGLModel_p.h \
    $$PWD/HOpenGLShaderProgram.h \
    $$PWD/HOpenGLShaderProgram_p.h \
    $$PWD/HOpenGLWidget_1.h \
    $$PWD/HOpenGLWidget_1_p.h \
    $$PWD/stb_image.h

SOURCES += \
    $$PWD/HLearnGLFW.cpp \
    $$PWD/HLearnGLFW_AntiAliasing.cpp \
    $$PWD/HLearnGLFW_Blending.cpp \
    $$PWD/HLearnGLFW_Bloom.cpp \
    $$PWD/HLearnGLFW_Camera.cpp \
    $$PWD/HLearnGLFW_Color.cpp \
    $$PWD/HLearnGLFW_Coordinate.cpp \
    $$PWD/HLearnGLFW_Cubemaps.cpp \
    $$PWD/HLearnGLFW_DeferredShading.cpp \
    $$PWD/HLearnGLFW_Framebuffers.cpp \
    $$PWD/HLearnGLFW_Geometry.cpp \
    $$PWD/HLearnGLFW_HDR.cpp \
    $$PWD/HLearnGLFW_Instancing.cpp \
    $$PWD/HLearnGLFW_Light.cpp \
    $$PWD/HLearnGLFW_LightAdvanced.cpp \
    $$PWD/HLearnGLFW_Materials.cpp \
    $$PWD/HLearnGLFW_Model.cpp \
    $$PWD/HLearnGLFW_Normal.cpp \
    $$PWD/HLearnGLFW_PBR.cpp \
    $$PWD/HLearnGLFW_Parallax.cpp \
    $$PWD/HLearnGLFW_SSAO.cpp \
    $$PWD/HLearnGLFW_Shadow.cpp \
    $$PWD/HLearnGLFW_Stencil.cpp \
    $$PWD/HLearnGLFW_Texture.cpp \
    $$PWD/HLearnGLFW_Triangle.cpp \
    $$PWD/HLearnGLFW_Ubo.cpp \
    $$PWD/HOpenGLCamera.cpp \
    $$PWD/HOpenGLHelper.cpp \
    $$PWD/HOpenGLMesh.cpp \
    $$PWD/HOpenGLModel.cpp \
    $$PWD/HOpenGLShaderProgram.cpp \
    $$PWD/HOpenGLWidget_1.cpp \
    $$PWD/glad.c \
    $$PWD/stb_image.cpp

GladPath    = $$absolute_path("../../../modules/glad", $$[QT_INSTALL_DATA])
GlfwPath    = $$absolute_path("../../../modules/glfw/win32", $$[QT_INSTALL_DATA])
AssimpPath  = $$absolute_path("../../../modules/assimp", $$[QT_INSTALL_DATA])

LIBS        += \
            -L$$GlfwPath/lib-mingw -lglfw3 \
            -L$$AssimpPath/lib -lassimp \
            -lgdi32 \
            -lglu32 \
            -lopengl32

INCLUDEPATH += \
            $$GladPath/include \
            $$GlfwPath/include \
            $$AssimpPath/include
