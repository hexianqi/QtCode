#ifndef HESQL_GLOBAL_H
#define HESQL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_SQL_LIB)
#  define HE_SQL_EXPORT Q_DECL_EXPORT
#else
#  define HE_SQL_EXPORT Q_DECL_IMPORT
#endif

#define HE_SQL_NAMESPACE HeSql

#ifdef HE_SQL_NAMESPACE
#  define HE_SQL_BEGIN_NAMESPACE namespace HE_SQL_NAMESPACE {
#  define HE_SQL_END_NAMESPACE }
#  define HE_SQL_USE_NAMESPACE using namespace HE_SQL_NAMESPACE;
#else
#  define HE_SQL_BEGIN_NAMESPACE
#  define HE_SQL_END_NAMESPACE
#  define HE_SQL_USE_NAMESPACE
#endif

HE_SQL_BEGIN_NAMESPACE
HE_SQL_END_NAMESPACE

#endif // HESQL_GLOBAL_H
