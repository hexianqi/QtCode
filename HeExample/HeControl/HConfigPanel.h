/***************************************************************************************************
**      2019-08-02  HConfigPanel
***************************************************************************************************/

#pragma once

#include "HAbstractMultiPanel.h"

HE_CONTROL_BEGIN_NAMESPACE

class HConfigPanelPrivate;

class HConfigPanel : public HAbstractMultiPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HConfigPanel)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)

public:
    explicit HConfigPanel(QWidget *parent = nullptr);

signals:
    void saving();
    void applying(int);
    void discarding(int);

public:
    int count() const override;
    int indexOf(QWidget *) const override;
    QWidget *widget(int index) const override;
    QWidget *currentWidget() const override;
    QSize iconSize() const;

public:
    void insertWidget(int index, QWidget *widget, const QIcon &icon = QIcon(), const QString &label = QString()) override;
    bool removeWidget(int index) override;

public slots:
    bool setCurrentIndex(int value) override;
    bool setWidgetIcon(int index, const QIcon &icon) override;
    bool setWidgetTitle(int index, const QString &title) override;
    void setIconSize(const QSize &);
    void save();
    void apply();
    void discard();

protected:
    HConfigPanel(HConfigPanelPrivate &p, QWidget *parent = nullptr);

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
