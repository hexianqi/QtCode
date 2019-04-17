/***************************************************************************************************
**      2019-03-01  HAction 调用者动作类。
***************************************************************************************************/

#ifndef HACTION_H
#define HACTION_H

#include "HGuiGlobal.h"
#include "HeCore/IInvoker.h"
#include <QtWidgets/QAction>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HActionPrivate;

class HAction : public QAction, public IInvoker
{
    Q_OBJECT

public:
    explicit HAction(QObject *parent = nullptr);
    ~HAction() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setHandler(IHandler *) override;
    void call() override;

protected:
    HAction(HActionPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HActionPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HACTION_H
