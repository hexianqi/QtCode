/***************************************************************************************************
**      2019-08-09  HTaskPanel
***************************************************************************************************/

#pragma once

#include "HAbstractMultiPanel.h"

HE_CONTROL_BEGIN_NAMESPACE

class HTaskPanelPrivate;

class HTaskPanel : public HAbstractMultiPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTaskPanel)
    Q_PROPERTY(QIcon toggleIcon READ toggleIcon WRITE setToggleIcon)
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)

public:
    explicit HTaskPanel(QWidget *parent = nullptr);

public:
    int count() const override;
    int indexOf(QWidget *) const override;
    QWidget *widget(int index) const override;
    QWidget *currentWidget() const override;
    bool isAnimated() const;
    QIcon toggleIcon() const;

public:
    void insertWidget(int index, QWidget *widget, const QIcon &icon, const QString &label = QString()) override;
    bool removeWidget(int index) override;

public slots:
    bool setCurrentIndex(int value) override;
    bool setWidgetIcon(int index, const QIcon &icon) override;
    bool setWidgetTitle(int index, const QString &title) override;
    void setToggleIcon(const QIcon &value);
    void setAnimated(bool b);

protected:
    HTaskPanel(HTaskPanelPrivate &p, QWidget *parent = nullptr);

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
