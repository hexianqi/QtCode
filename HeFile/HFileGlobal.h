#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_FILE_LIB)
#  define HE_FILE_EXPORT Q_DECL_EXPORT
#else
#  define HE_FILE_EXPORT Q_DECL_IMPORT
#endif
