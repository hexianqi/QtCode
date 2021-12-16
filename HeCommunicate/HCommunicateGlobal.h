#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_COMMUNICATE_LIB)
#  define HE_COMMUNICATE_EXPORT Q_DECL_EXPORT
#else
#  define HE_COMMUNICATE_EXPORT Q_DECL_IMPORT
#endif
