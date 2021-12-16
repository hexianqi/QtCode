/***************************************************************************************************
**      2021-12-15  名空间定义He
***************************************************************************************************/

#pragma once

#define HE_NAMESPACE He

#ifdef HE_NAMESPACE
#  define HE_BEGIN_NAMESPACE namespace HE_NAMESPACE {
#  define HE_END_NAMESPACE }
#  define HE_USE_NAMESPACE using namespace HE_NAMESPACE;
#else
#  define HE_BEGIN_NAMESPACE
#  define HE_END_NAMESPACE
#  define HE_USE_NAMESPACE
#endif

HE_BEGIN_NAMESPACE
HE_END_NAMESPACE
