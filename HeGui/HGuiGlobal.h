#pragma once

#include <QtCore/qglobal.h>

#if defined(HE_BUILD_GUI_LIB)
#  define HE_GUI_EXPORT Q_DECL_EXPORT
#else
#  define HE_GUI_EXPORT Q_DECL_IMPORT
#endif

#define HE_GUI_NAMESPACE HeGui

#ifdef HE_GUI_NAMESPACE
#  define HE_GUI_BEGIN_NAMESPACE namespace HE_GUI_NAMESPACE {
#  define HE_GUI_END_NAMESPACE }
#  define HE_GUI_USE_NAMESPACE using namespace HE_GUI_NAMESPACE;
#else
#  define HE_GUI_BEGIN_NAMESPACE
#  define HE_GUI_END_NAMESPACE
#  define HE_GUI_USE_NAMESPACE
#endif

HE_GUI_BEGIN_NAMESPACE
HE_GUI_END_NAMESPACE
