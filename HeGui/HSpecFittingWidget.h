/***************************************************************************************************
**      2019-03-27  HSpecFittingWidget 拟合配置窗体。
***************************************************************************************************/

#ifndef HSPECFITTINGWIDGET_H
#define HSPECFITTINGWIDGET_H

#include "HGuiGlobal.h"
#include "HeCore/HActionType.h"
#include "HeData/HDataGlobal.h"
#include <QWidget>

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
    explicit HSpecFittingWidget(HSpecFitting *data, QWidget *parent = nullptr);
    ~HSpecFittingWidget() override;

signals:
    void testStateChanged(bool b);
    void fittingFinished();

public:
    virtual void restoreDefault();
    virtual QPolygonF fittingPoints();
    virtual void handleAction(HActionType action);
    virtual bool setTest(bool b);

protected:
    HSpecFittingWidget(HSpecFittingWidgetPrivate &p, QWidget *parent = nullptr);

protected:
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
