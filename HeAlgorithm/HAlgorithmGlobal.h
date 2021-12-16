#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_ALGORITHM_LIB)
#  define HE_ALGORITHM_EXPORT Q_DECL_EXPORT
#else
#  define HE_ALGORITHM_EXPORT Q_DECL_IMPORT
#endif
