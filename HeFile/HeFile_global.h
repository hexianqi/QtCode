#ifndef HEFILE_GLOBAL_H
#define HEFILE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HEFILE_LIBRARY)
#  define HEFILESHARED_EXPORT Q_DECL_EXPORT
#else
#  define HEFILESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HEFILE_GLOBAL_H
