/***************************************************************************************************
**      2019-06-25  HDemoWidget 演示窗体。
***************************************************************************************************/

#ifndef HDEMOWIDGET_H
#define HDEMOWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HDemoWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HDemoWidgetPrivate;

class HE_CONTROL_EXPORT HDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HDemoWidget(QWidget *parent = nullptr);
    ~HDemoWidget();

private:
    void init();
//    void addSlideNavigation();
    void addAntLine();
    void addBackground();
    void addBattery();
    void addButton();
    void addColorPanel();
    void addCpuMemoryLabel();
    void addCustomGraphics();
    void addGauge();
    void addImageCalendar();
    void addLedNumber();
    void addLightPoint();
    void addMagic();
    void addMultHeaderTableView();
    void addMultHeaderTableWidget();
    void addNav();
    void addProgressBar();
    void addRuler();
    void addww();

private:
    void addTab(QLayout *, QString title);

private:
    Ui::HDemoWidget *ui;
    QScopedPointer<HDemoWidgetPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HDEMOWIDGET_H
