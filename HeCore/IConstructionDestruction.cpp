#include "IConstructionDestruction.h"
#include <QtCore/QObject>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

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
    HBaseObject();
    ~HBaseObject();

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

HBaseObject::HBaseObject()
{

}

HBaseObject::~HBaseObject()
{
    emit beforeDestroyed();
}

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
    HSubObject();
    ~HSubObject();

public:
    void read() override;
    void write() override;
};

HSubObject::HSubObject()
{

}

HSubObject::~HSubObject()
{
    emit beforeDestroyed();
}

void HSubObject::read()
{
    qDebug() << "HSubObject::read";
}

void HSubObject::write()
{
    qDebug() << "HSubObject::write";
}

void testConstructionDestruction()
{
    auto obj = new TConstructionDestruction<HSubClass>();
    obj->doSomething();
    delete obj;
}

void testObject()
{
    HSubObject obj;
    obj.init();
    obj.doSomething();
}

HE_END_NAMESPACE

#include "IConstructionDestruction.moc"


