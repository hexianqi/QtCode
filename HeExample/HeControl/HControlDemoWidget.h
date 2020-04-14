/***************************************************************************************************
**      2019-12-09  HControlDemoWidget 演示窗体。
***************************************************************************************************/

#ifndef HCONTROLDEMOWIDGET_H
#define HCONTROLDEMOWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HControlDemoWidgetPrivate;

class HE_CONTROL_EXPORT HControlDemoWidget : public QWidget
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
    void addLiuDianWu();
    void addWw();
    void addDemo();
    void addTool();
    void addElse();

    // LiuDianWu
    void addBattery();
    void addCalendar();
    void addExplorer();
    void addIPAddress();
    void addDefenceButton();
    void addLightButton();
    void addNavButton();
    void addLunarCalendar();
    void addImageSwitch();

    // ww
    void addWwExtend();
    void addWwPicker();
    void addWwNavigator();
    void addWwConfigPanel();
    void addWwNavigationPanel();
    void addWwTaskPanel();
    void addWwTipWidget();
    void addWwElse();

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

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLDEMOWIDGET_H
