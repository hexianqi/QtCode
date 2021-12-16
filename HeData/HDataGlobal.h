#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_DATA_LIB)
#  define HE_DATA_EXPORT Q_DECL_EXPORT
#else
#  define HE_DATA_EXPORT Q_DECL_IMPORT
#endif
