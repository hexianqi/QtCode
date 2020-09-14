/***************************************************************************************************
**      2019-03-25  HSpecEnergyWidget 光谱能量窗体。
***************************************************************************************************/

#ifndef HSPECENERGYWIDGET_H
#define HSPECENERGYWIDGET_H

#include "HGuiGlobal.h"
#include <QtWidgets/QWidget>

HE_GUI_BEGIN_NAMESPACE

class HSpecEnergyWidgetPrivate;

class HE_GUI_EXPORT HSpecEnergyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSpecEnergyWidget(QWidget *parent = nullptr);
    ~HSpecEnergyWidget() override;

public:
    void initCoordinate();
    void refreshWidget();
    void addProgressBar(const QString &type);
    void setProgressBarVisible(const QString &type, bool b);

protected:
    HSpecEnergyWidget(HSpecEnergyWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HSpecEnergyWidgetPrivate> d_ptr;

private:
    void init();
};

HE_GUI_END_NAMESPACE

#endif // HSPECENERGYWIDGET_H
