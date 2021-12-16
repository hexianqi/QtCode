/***************************************************************************************************
**      2019-06-25  HDemoWidget 演示窗体。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HDemoWidget;
}

HE_BEGIN_NAMESPACE

class HDemoWidgetPrivate;

class HDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HDemoWidget(QWidget *parent = nullptr);
    ~HDemoWidget() override;

private:
    void init();
//    void addSlideNavigation();
    void addAntLine();
    void addBackground();
    void addButton();
    void addColorPanel();
    void addCpuMemoryLabel();
    void addCustomGraphics();
    void addGauge();
    void addImageCalendar();
    void addLedNumber();
    void addLightPoint();
    void addMagic();
    void addNav();
    void addPanel();
    void addProgressBar();
    void addRuler();
    void addww();

private:
    void addTab(QLayout *, const QString &title);

private:
    Ui::HDemoWidget *ui;
    QScopedPointer<HDemoWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
