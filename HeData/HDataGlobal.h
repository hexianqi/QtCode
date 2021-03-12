#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_DATA_LIB)
#  define HE_DATA_EXPORT Q_DECL_EXPORT
#else
#  define HE_DATA_EXPORT Q_DECL_IMPORT
#endif

#define HE_DATA_NAMESPACE HeData

#ifdef HE_DATA_NAMESPACE
#  define HE_DATA_BEGIN_NAMESPACE namespace HE_DATA_NAMESPACE {
#  define HE_DATA_END_NAMESPACE }
#  define HE_DATA_USE_NAMESPACE using namespace HE_DATA_NAMESPACE;
#else
#  define HE_DATA_BEGIN_NAMESPACE
#  define HE_DATA_END_NAMESPACE
#  define HE_DATA_USE_NAMESPACE
#endif

HE_DATA_BEGIN_NAMESPACE
HE_DATA_END_NAMESPACE

#define H_DECLARE_PRIVATE(Class, T) \
    inline Class##Private<T> *d_func() { return reinterpret_cast<Class##Private<T> *>(qGetPtrHelper(this->d_ptr)); } \
    inline const Class##Private<T> *d_func() const { return reinterpret_cast<const Class##Private<T> *>(qGetPtrHelper(this->d_ptr)); } \
    friend class Class##Private<T>;

#define H_D(Class, T) Class##Private<T> * const d = d_func()
