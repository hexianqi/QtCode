/***************************************************************************************************************************
** https://www.2cto.com/kf/201609/549180.html
** 使用了Qt的反射技术。
** 虽然C++本身不像java或者C#那样可以有库自带反射实现的方法来实现通过类名动态的创建类，
** 但是Qt框架的元系统可以使这一过程简化，如果想要动态的在运行时根据字符串的名字创建类，只需要完成以下三步即可：
**
** 第一步：将需要使用的类通过Q_DECLARE_METATYPE注册，如：Q_DECLARE_METATYPE(CExample)。
** 注意：（1）需要构造的类必须提供公用的构造函数、拷贝构造函数和析构函数，
**            当然如果没有复杂的需要深拷贝的数据，使用编译器默认提供的也行。
**       （2）以下类无需使用该宏即可自动的注册到Qt元系统中：
**          a.继承自QObject的类；
**          b.QList, QVector, QQueue, QStack, QSet 和 QLinkedList这些数据结构中T是注册过的类型；
**          c.QHash, QMap 和 QPair这些数据结构中T1和T2是注册过的类型；
**          d.QPointer, QSharedPointer, QWeakPointer, 这些智能指针中T是注册过的类型；
**          e.通过Q_ENUM 或者 Q_FLAG注册的枚举数据；
**          f.具有一个Q_GADGET宏的类。
**
** 第二步：如果需要动态的根据类名创建该类，需要在main函数中通过qRegisterMetaType注册，
** 例如：qRegisterMetaType<CExample>("CExample");
** 注意：如果仅仅要在QVariant中使用该类，就不需要这一步了。
**
** 第三步：通过int id = QMetaType::type(该类名字的字符串转换为QByteArray或者直接const char*)，
**         然后使用QMetaType::create(id)返回一个新的该类的指针。例如：
**          QString className = "CExample";
**          int id = QMetaType::type(className.toLatin1());  //或者int id = QMetaType::type("CExample");
**          CExample* result = static_cast<CExample*>(QMetaType::create(id));
***************************************************************************************************************************/

#include "HTypeHelper.h"
#include "IInitializeable.h"
#include <QMetaType>

HE_CORE_BEGIN_NAMESPACE

template<class T>
T *HTypeHelper::createObject(QString className)
{
    int id = QMetaType::type(className.toLatin1());
    return id == QMetaType::UnknownType ? nullptr : dynamic_cast<T*>(QMetaType::create(id));
}

template<class T>
T *HTypeHelper::createObject(QString className, QVariantMap param)
{
    static_assert(std::is_base_of<IInitializeable, T>::value, "T needs to be IInitializeable based.");
    auto t = createObject<T>(className);
    if (t != nullptr)
        t->initialize(param);
    return t;
}

HE_CORE_END_NAMESPACE
