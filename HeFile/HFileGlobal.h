#ifndef HFILEGLOBAL_H
#define HFILEGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_FILE_LIB)
#  define HE_FILE_EXPORT Q_DECL_EXPORT
#else
#  define HE_FILE_EXPORT Q_DECL_IMPORT
#endif

#define HE_FILE_NAMESPACE HeFile

#ifdef HE_FILE_NAMESPACE
#  define HE_FILE_BEGIN_NAMESPACE namespace HE_FILE_NAMESPACE {
#  define HE_FILE_END_NAMESPACE }
#  define HE_FILE_USE_NAMESPACE using namespace HE_FILE_NAMESPACE;
#else
#  define HE_FILE_BEGIN_NAMESPACE
#  define HE_FILE_END_NAMESPACE
#  define HE_FILE_USE_NAMESPACE
#endif

#endif // HFILEGLOBAL_H
