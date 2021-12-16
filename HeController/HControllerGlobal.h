#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_CONTROLLER_LIB)
#  define HE_CONTROLLER_EXPORT Q_DECL_EXPORT
#else
#  define HE_CONTROLLER_EXPORT Q_DECL_IMPORT
#endif
