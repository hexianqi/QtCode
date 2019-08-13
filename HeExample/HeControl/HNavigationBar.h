/***************************************************************************************************
**      2019-08-07  HNavigationBar
***************************************************************************************************/

#ifndef HNAVIGATIONBAR_H
#define HNAVIGATIONBAR_H

#include "HAbstractMultiWidget.h"
#include <functional>

class QPushButton;
class QToolButton;

HE_CONTROL_BEGIN_NAMESPACE

class HNavigationBarPrivate;

class HNavigationBar : public HAbstractMultiWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HNavigationBar)
    Q_PROPERTY(bool topWidgetVisible READ topWidgetIsVisible WRITE setTopWidgetVisible)

public:
    explicit HNavigationBar(QWidget *parent = nullptr);
    ~HNavigationBar() override;

public:
    int count() const override;
    int indexOf(QWidget *) const override;
    QWidget *widget(int index) const override;
    QWidget *currentWidget() const override;
    QPushButton *button(int index) const;
    bool topWidgetIsVisible() const;

public:
    void insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &label = QString()) override;
    void removeWidget(int index) override;

public slots:
    bool setCurrentIndex(int value) override;
    bool setWidgetIcon(int index, const QIcon &icon) override;
    bool setWidgetTitle(int index, const QString &title) override;
    void setTopWidgetVisible(bool b);

protected:
    HNavigationBar(HNavigationBarPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void actionEvent(QActionEvent *) override;
    void addToolButton(int index, QAction *action);
    void findToolButton(QAction *action, std::function<void (int, QToolButton *)> func);

private:
    void init();
    void handleButtonClicked();
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVIGATIONBAR_H
