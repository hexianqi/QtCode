/***************************************************************************************************
**      2019-03-27  HSpecFittingWidget 拟合配置窗体。
***************************************************************************************************/

#pragma once

#include "HeCore/HActionType.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HSpecFitting;
class HSpecFittingWidgetPrivate;

class HSpecFittingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSpecFittingWidget(QWidget *parent = nullptr);

signals:
    void stateChanged(bool b);
    void fittingFinished();

public:
    QPolygonF fittingPoints();
    QPolygonF fittingCurve();

public:
    void setData(HSpecFitting *);
    void clearData();
    virtual bool setTestState(bool b);
    virtual void handleAction(HActionType action);

protected:
    HSpecFittingWidget(HSpecFittingWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void cancel(const QString &text);
    virtual bool initParam() = 0;
    virtual void saveData() = 0;
    virtual void showData() = 0;

protected:
    QScopedPointer<HSpecFittingWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
