#ifndef HECORE_GLOBAL_H
#define HECORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HECORE_LIBRARY)
#  define HECORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define HECORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HECORE_GLOBAL_H
