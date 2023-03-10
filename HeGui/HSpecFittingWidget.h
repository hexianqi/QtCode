/***************************************************************************************************
**      2019-07-22  HSpecFittingPolynomWidget 拟合配置窗体（多项式）。
***************************************************************************************************/

#pragma once

#include "HeCore/HActionType.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HSpecFittingWidget;
}

HE_BEGIN_NAMESPACE

class HSpecFitting;
class HSpecFittingWidgetPrivate;

class HSpecFittingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSpecFittingWidget(QWidget *parent = nullptr);
    ~HSpecFittingWidget() override;

signals:
    void stateChanged(bool b);
    void fittingFinished();

public:
    QPolygonF points();
    QPolygonF curve();

public:
    void setData(HSpecFitting *);
    void clearData();
    bool setTestState(bool b);
    void handleAction(HActionType action);

protected:
    void init();
    void cancel(const QString &text);
    void saveData();
    void showData();

protected:
    QScopedPointer<HSpecFittingWidgetPrivate> d_ptr;

private:
    Ui::HSpecFittingWidget *ui;
};

HE_END_NAMESPACE
