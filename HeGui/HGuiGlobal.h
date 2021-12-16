#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_GUI_LIB)
#  define HE_GUI_EXPORT Q_DECL_EXPORT
#else
#  define HE_GUI_EXPORT Q_DECL_IMPORT
#endif
