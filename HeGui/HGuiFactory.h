/***************************************************************************************************
**      2019-03-01  HGuiFactory Gui工厂类。
***************************************************************************************************/

#ifndef HGUIFACTORY_H
#define HGUIFACTORY_H

#include "IGuiFactory.h"

HE_GUI_BEGIN_NAMESPACE

class HGuiFactoryPrivate;

class HE_GUI_EXPORT HGuiFactory : public QObject, public IGuiFactory
{
    Q_OBJECT

public:
    explicit HGuiFactory(QObject *parent = nullptr);
    ~HGuiFactory();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

public:
    virtual IGuiHandler *createHandler(QString type, QVariantMap param = QVariantMap()) override;
    virtual HAction *createAction(QString text, QString type, QVariantMap param = QVariantMap()) override;

protected:
    HGuiFactory(HGuiFactoryPrivate &p, QObject *parent = nullptr);

private:
    void registerClass();

protected:
    QScopedPointer<HGuiFactoryPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HGUIFACTORY_H
