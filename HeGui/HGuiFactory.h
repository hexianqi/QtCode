#ifndef HGUIFACTORY_H
#define HGUIFACTORY_H

#include "IGuiFactory.h"

HE_GUI_BEGIN_NAMESPACE

class HGuiFactoryPrivate;

class HGuiFactory : public QObject, public IGuiFactory
{
public:
    explicit HGuiFactory(QObject *parent = nullptr);
    ~HGuiFactory();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

public:
    virtual IHandler *createHandler(QString type, QVariantMap param) override;

protected:
    HGuiFactory(HGuiFactoryPrivate &p);

private:
    void registerClass();

protected:
    QScopedPointer<HGuiFactoryPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HGUIFACTORY_H
