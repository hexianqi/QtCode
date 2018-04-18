#ifndef HEFILE_GLOBAL_H
#define HEFILE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HEFILE)
#  define HEFILE_EXPORT Q_DECL_EXPORT
#else
#  define HEFILE_EXPORT Q_DECL_IMPORT
#endif

#endif // HEFILE_GLOBAL_H
