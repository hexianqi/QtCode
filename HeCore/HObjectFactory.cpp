/****************************************************************************
调用方法：
首先要注册你的class：必须继承QObject
ObjectFactory::registerClass<MyObject>();

反射构建一个新对象：
MyObject* object = ObjectFactory::createObject<MyObject>( "MyObject" );
****************************************************************************/

#include "HObjectFactory.h"

HE_CORE_USE_NAMESPACE

QHash<QByteArray, std::function<QObject*(QObject*)>> HObjectFactory::hashConstructor;

template<typename T>
void HObjectFactory::registerClass()
{
    hashConstructor.insert(T::staticMetaObject.className(), &constructorHelper<T>);
}

template<typename T>
T *HeCore::HObjectFactory::createObject(const QByteArray &className, QObject *parent)
{
    if (!hashConstructor.contains(className))
        return nullptr;
    return dynamic_cast<T*>(hashConstructor[className](parent));
}

template<typename T>
QObject *HObjectFactory::constructorHelper(QObject *parent)
{
    return new T(parent);
}
