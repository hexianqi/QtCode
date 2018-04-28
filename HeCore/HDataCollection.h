//#ifndef HDATACOLLECTION_H
//#define HDATACOLLECTION_H

//#include "HDataObject.h"
//#include <QVariantMap>

//using namespace  He::Core;

//template <class T>
//class HDataCollection : public HDataObject
//{
//public:
//    void initialize(QVariantMap param);

//protected:
//    T createObject(QVariant param);

//protected:
//    QMap<QString, T> map;
//};

//template <typename T>
//void HDataCollection<T>::initialize(QVariantMap param)
//{
//    HDataObject::initialize(param);
//    if (!param.contains("childs"))
//        return;
//    auto list = param["childs"].toList();
//    for (auto i : list)
//    {
//        auto t = createObject(i);
//        map.insert(t.type(), t);
//    }
//}

//template <typename T>
//T HDataCollection<T>::createObject(QVariant param)
//{
//    T t;
//    t.initialize(param.toMap());
//    return t;
//}


////#include "HDataObject.h"
////#include <QVariantMap>

////template <class T = HDataObject>
////class HDataCollection : QMap<QString, T>
////{
////public:
////    void initialize(QVariantMap param);
////};

////template <typename T>
////void HDataCollection<T>::initialize(QVariantMap param)
////{
////    if (!param.contains("typs"))
////        return;
////    auto list = param["types"].toList();
////    for (auto i : list)
////    {
////        T t;
////        t.initialize(i);
////        insert(t.type, t);
////    }
////}

//#endif // HDATACOLLECTION_H
