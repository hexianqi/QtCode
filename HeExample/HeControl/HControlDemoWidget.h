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

    // FYQY
    void addFYQY();
    void addBattery();
    void addDeviceButton();
    void addExplorer();
    void addImageSwitch();
    void addIPAddress();
    void addLightButton();
    void addNavButton();

    // LiuDianWu
    void addLiuDianWu();
    void addCalendar();
    void addLunarCalendar();

    // ww
    void addWw();
    void addWwExtend();
    void addWwPicker();
    void addWwConfigPanel();
    void addWwNavigationPanel();
    void addWwTaskPanel();
    void addWwTipWidget();
    void addWwNavigator();
    void addWwElse();

    // Demo
    void addDemo();

    // Layout
    void addLayout();
    void addBorderLayout();
    void addCardLayout();
    void addFlowLayout();

    // Style
    void addStyle();

    // Tool
    void addTool();
    void addChineseConvert();

    // media
    void addMedia();
    void addFFPlayer();
    void addVlcPlayer();

    // Else
    void addElse();
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
