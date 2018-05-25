/****************************************************************************
 * 调用方法：
 * 首先要注册你的class：必须继承QObject
 * ObjectFactory::registerClass<MyObject>();
 * 反射构建一个新对象：
 * MyObject* object = ObjectFactory::createObject<MyObject>("MyObject");
 ****************************************************************************/

#include "HObjectFactory.h"

HE_CORE_BEGIN_NAMESPACE

QHash<QByteArray, std::function<QObject*(QObject*)>> HObjectFactory::__hashConstructor;

template<typename T>
void HObjectFactory::registerClass()
{
    __hashConstructor.insert(T::staticMetaObject.className(), &constructorHelper<T>);
}

template<typename T>
QObject *HObjectFactory::constructorHelper(QObject *parent)
{
    return new T(parent);
}

HE_CORE_END_NAMESPACE
