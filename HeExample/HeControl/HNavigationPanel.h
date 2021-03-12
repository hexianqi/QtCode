/***************************************************************************************************
**      2019-08-07  HNavigationPanel
***************************************************************************************************/

#pragma once

#include "HAbstractMultiPanel.h"
#include <functional>

class QPushButton;
class QToolButton;

HE_CONTROL_BEGIN_NAMESPACE

class HNavigationPanelPrivate;

class HNavigationPanel : public HAbstractMultiPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HNavigationPanel)
    Q_PROPERTY(bool topWidgetVisible READ topWidgetIsVisible WRITE setTopWidgetVisible)

public:
    explicit HNavigationPanel(QWidget *parent = nullptr);

public:
    int count() const override;
    int indexOf(QWidget *) const override;
    QWidget *widget(int index) const override;
    QWidget *currentWidget() const override;
    bool topWidgetIsVisible() const;
    QPushButton *button(int index) const;

public:
    void insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &label = QString()) override;
    bool removeWidget(int index) override;

public slots:
    bool setCurrentIndex(int value) override;
    bool setWidgetIcon(int index, const QIcon &icon) override;
    bool setWidgetTitle(int index, const QString &title) override;
    void setTopWidgetVisible(bool b);

protected:
    HNavigationPanel(HNavigationPanelPrivate &p, QWidget *parent = nullptr);

protected:
    void actionEvent(QActionEvent *) override;
    void addToolButton(int index, QAction *action);
    void findToolButton(QAction *action, const std::function<void (int, QToolButton *)> &func);

private:
    void init();
    void handleButtonClicked();
};

HE_CONTROL_END_NAMESPACE
