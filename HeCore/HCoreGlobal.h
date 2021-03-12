#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_CORE_LIB)
#  define HE_CORE_EXPORT Q_DECL_EXPORT
#else
#  define HE_CORE_EXPORT Q_DECL_IMPORT
#endif

#define HE_CORE_NAMESPACE HeCore

#ifdef HE_CORE_NAMESPACE
#  define HE_CORE_BEGIN_NAMESPACE namespace HE_CORE_NAMESPACE {
#  define HE_CORE_END_NAMESPACE }
#  define HE_CORE_USE_NAMESPACE using namespace HE_CORE_NAMESPACE;
#else
#  define HE_CORE_BEGIN_NAMESPACE
#  define HE_CORE_END_NAMESPACE
#  define HE_CORE_USE_NAMESPACE
#endif

HE_CORE_BEGIN_NAMESPACE
#define ToVariant(Value)            QVariant::fromValue(static_cast<void *>(Value))
#define FromVariant(Class, Value)   static_cast<Class *>(Value.value<void *>())
HE_CORE_END_NAMESPACE
