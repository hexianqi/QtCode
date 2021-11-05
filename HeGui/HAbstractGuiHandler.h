/***************************************************************************************************
**      2019-03-01  HAbstractGuiHandler 抽象Gui处理者类。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeCore/IHandler.h"

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAbstractGuiHandlerPrivate;

class HAbstractGuiHandler : public QObject, public IHandler
{
    Q_OBJECT

public:
    explicit HAbstractGuiHandler(QObject *parent = nullptr);
    ~HAbstractGuiHandler() override;

public:
    void initialize(QVariantMap param) override;

protected:
    HAbstractGuiHandler(HAbstractGuiHandlerPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractGuiHandlerPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE
