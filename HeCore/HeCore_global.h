#ifndef HECORE_GLOBAL_H
#define HECORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HECORE)
#  define HECORE_EXPORT Q_DECL_EXPORT
#else
#  define HECORE_EXPORT Q_DECL_IMPORT
#endif

#endif // HECORE_GLOBAL_H
