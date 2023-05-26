/***************************************************************************************************
**      2019-03-25  HSpecEnergyWidget 光谱能量窗体。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HSpecEnergyWidgetPrivate;

class HSpecEnergyWidget : public QWidget
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
    void setToolTipTypes(const QStringList &value = QStringList());

protected:
    HSpecEnergyWidget(HSpecEnergyWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HSpecEnergyWidgetPrivate> d_ptr;

private:
    void init();
    void readSettings();
    void writeSettings();
};

HE_END_NAMESPACE
