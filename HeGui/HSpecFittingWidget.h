/***************************************************************************************************
**      2019-03-27  HSpecFittingWidget 拟合配置窗体。
***************************************************************************************************/

#ifndef HSPECFITTINGWIDGET_H
#define HSPECFITTINGWIDGET_H

#include "HGuiGlobal.h"
#include "HeCore/HActionType.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QWidget>

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class HSpecFitting;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecFittingWidgetPrivate;

class HE_GUI_EXPORT HSpecFittingWidget : public QWidget
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

HE_GUI_END_NAMESPACE

#endif // HSPECFITTINGWIDGET_H
