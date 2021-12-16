#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_CONTROL_LIB)
#  define HE_EXPORT Q_DECL_EXPORT
#else
#  define HE_EXPORT Q_DECL_IMPORT
#endif
