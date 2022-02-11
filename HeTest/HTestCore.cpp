#include "HTestCore.h"
#include "HeCore/HDumpTree.h"
#include "HeCore/IConstructionDestruction.h"
#include "HeCore/HDictionary.h"
#include "HeCore/HThreadPool.h"
#include <iostream>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QtDebug>

HE_USE_NAMESPACE

class HBaseClass : public IConstructionDestruction
{
public:
    virtual ~HBaseClass() = default;

public:
    void doSomething()
    {
        qDebug() << "HBase::doSomething";
    }

protected:
    void afterConstruction() override
    {
        qDebug() << "HBase::afterConstruction";
    }
    void beforeDestruction() override
    {
        qDebug() << "HBase::beforeDestruction";
    }
};

class HSubClass : public HBaseClass
{
public:
    ~HSubClass() override = default;

protected:
    void afterConstruction() override
    {
        qDebug() << "HSubClass::afterConstruction";
    };
    void beforeDestruction() override
    {
        qDebug() << "HSubClass::beforeDestruction";
    };
};

class HBaseObject : public QObject
{
    Q_OBJECT

public:
    HBaseObject() { }
    ~HBaseObject() { emit beforeDestroyed(); }

signals:
    void beforeDestroyed();

public:
    virtual void init();
    virtual void close();
    virtual void doSomething();

public:
    virtual void read();
    virtual void write();
};

void HBaseObject::init()
{
    qDebug() << "HBaseObject::init";
    read();
    connect(this, &HBaseObject::beforeDestroyed, this, &HBaseObject::close);
}

void HBaseObject::doSomething()
{
    qDebug() << "HBaseObject::doSomething";
}

void HBaseObject::close()
{
    qDebug() << "HBaseObject::close";
    write();
}

void HBaseObject::read()
{
    qDebug() << "HBaseObject::read";
}

void HBaseObject::write()
{
    qDebug() << "HBaseObject::write";
}

class HSubObject : public HBaseObject
{
    Q_OBJECT

public:
    HSubObject() { }
    ~HSubObject() { emit beforeDestroyed(); }

public:
    void read() override;
    void write() override;
};

void HSubObject::read()
{
    qDebug() << "HSubObject::read";
}

void HSubObject::write()
{
    qDebug() << "HSubObject::write";
}

void HTestCore::testThreadPool()
{
    HThreadPool pool(4);
    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i)
    {
        results.emplace_back(pool.enqueue([i] {
            std::cout << "hello " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "world " << i << std::endl;
            return  i * i;
        }));
    }

    for (auto && result : results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
}

void HTestCore::testConstructionDestruction()
{
    auto obj = new TConstructionDestruction<HSubClass>();
    obj->doSomething();
    delete obj;
}

void HTestCore::testConstructionDestruction2()
{
    HSubObject obj;
    obj.init();
    obj.doSomething();
}

void HTestCore::testDictionary()
{
    QVariantMap map1;
    map1.insert("t0", 10);
    map1.insert("t1", QVariantList() << 7.0 << 8.3 << 0.0 << 90.0);
    map1.insert("t2", false);

    QVariantMap map2;
    map2.insert("f0", 10);
    map2.insert("f1", QVariantList() << -7.0 << 18.3 << 30.0 << 55.0);
    map2.insert("f2", "ssdads");

    HDictionary dict;
    dict.set("a0.b0.c0.d1",     10);
    dict.set("a0.b0.c0.d2",     10);
    dict.set("a0.b0.c1",        true);
    dict.set("a0.b1.c0",        "10ssss");
    dict.set("a0.b1.c1",        QVariantList() << 7.0 << 8.3 << 0.0 << 90.0);
    dict.set("a1",              QVariantList() << 3.0 << 5.3 << 8.0 << 10.0);
    dict.set("a2",              QVariantList() << "abcd" << map1 << map2 << "sss" << true);
//    dict.set("a3",              QVariant::fromValue(QList<double>() << 7.0 << 8.3 << 0.0 << 90.0));
//    qDebug() << dict;

    HDictionary dict2;
    dict2.fromVariantMap(map2);
    dict2.set("a4", 12.0);
    qDebug() << dict2;

    QJsonValue json = dict.toJsonObject();
    HDumpTree::dump(json, "test");
    qDebug() << json;
}

#include "HTestCore.moc"
