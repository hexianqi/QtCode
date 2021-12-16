#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_SQL_LIB)
#  define HE_SQL_EXPORT Q_DECL_EXPORT
#else
#  define HE_SQL_EXPORT Q_DECL_IMPORT
#endif

