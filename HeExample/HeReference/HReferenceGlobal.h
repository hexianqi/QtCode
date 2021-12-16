#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_REFERENCE_LIB)
#  define HE_REFERENCE_EXPORT Q_DECL_EXPORT
#else
#  define HE_REFERENCE_EXPORT Q_DECL_IMPORT
#endif
