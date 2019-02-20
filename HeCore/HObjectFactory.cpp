/****************************************************************************
 * 调用方法：
 * 首先要注册你的class：必须继承QObject
 * HObjectFactory::registerClass<MyObject>();
 * 反射构建一个新对象：
 * MyObject* object = HObjectFactory::createObject<MyObject>("MyObject");
 ****************************************************************************/

#include "HObjectFactory.h"

HE_CORE_BEGIN_NAMESPACE

QHash<QString, std::function<QObject *(QObject *)>> HObjectFactory::__hashConstructor;

HE_CORE_END_NAMESPACE
