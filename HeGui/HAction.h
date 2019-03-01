/***************************************************************************************************
**      2019-03-01  HAction 调用者动作类。
***************************************************************************************************/

#ifndef HACTION_H
#define HACTION_H

#include "HGuiGlobal.h"
#include "HeCore/IInvoker.h"
#include <QAction>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HActionPrivate;

class HAction : public QAction, public IInvoker
{
    Q_OBJECT

public:
    explicit HAction(QObject *parent = nullptr);
    ~HAction();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

public:
    virtual void setHandler(IHandler *) override;
    virtual void call() override;

protected:
    HAction(HActionPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HActionPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HACTION_H
