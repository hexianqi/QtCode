/***************************************************************************************************
**      2019-12-09  HControlDemoWidget 演示窗体。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HControlDemoWidgetPrivate;

class HControlDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HControlDemoWidget(QWidget *parent = nullptr);
    ~HControlDemoWidget() override;

protected:
    HControlDemoWidget(HControlDemoWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HControlDemoWidgetPrivate> d_ptr;

private:
    void init();
    void initWidget();
    void addFYQY();
    void addLiuDianWu();
    void addWw();
    void addDemo();
    void addTool();
    void addMedia();
    void addElse();

    // FYQY
    void addBattery();
    void addDeviceButton();
    void addExplorer();
    void addImageSwitch();
    void addIPAddress();
    void addLightButton();

    // LiuDianWu
    void addCalendar();
    void addNavButton();
    void addLunarCalendar();

    // ww
    void addWwExtend();
    void addWwPicker();
    void addWwNavigator();
    void addWwConfigPanel();
    void addWwNavigationPanel();
    void addWwTaskPanel();
    void addWwTipWidget();
    void addWwElse();

    // media
    void addFFPlayer();
    void addVlcPlayer();

    // Else
    void addMultHeaderTableView();
    void addMultHeaderTableWidget();
    void addLineEditGroup();
    void addButtonGroup();
    void addAnimatedCheckBox();

private:
    void addTab(const QString &key, QWidget *);
    void addTab(const QString &key, const QString &title, QWidget *);
    void addTab(const QString &key, const QString &title, QLayout *);
};

HE_END_NAMESPACE
