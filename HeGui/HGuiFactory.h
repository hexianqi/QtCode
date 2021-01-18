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
    ~HGuiFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    ITestSetWidget *createTestSetWidget(QString type, QWidget *parent = nullptr, QVariantMap param = QVariantMap()) override;
    ITestDataEditDialog *createTestDataEditDialog(QString type, QWidget *parent = nullptr, QVariantMap param = QVariantMap()) override;
    IGuiHandler *createHandler(QString type, QVariantMap param = QVariantMap()) override;
    HAction *createAction(QString text, QString type, QVariantMap param = QVariantMap()) override;

protected:
    HGuiFactory(HGuiFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HGuiFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_GUI_END_NAMESPACE

#endif // HGUIFACTORY_H
