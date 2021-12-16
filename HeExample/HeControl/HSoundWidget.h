/***************************************************************************************************
**      2020-09-01  HSoundWidget 语音控制窗体。
**                  参考VLC-3.0.9.2
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HSoundWidgetPrivate;

class HSoundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSoundWidget(bool shiny, bool special = false, QWidget *parent = nullptr);
    ~HSoundWidget() override;

signals:
    void mutedChanged(bool);
    void volumeChanged(int);

public:
    void setMuted(bool);
    void setVolume(int);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void refreshLabels();
    void showVolumeMenu(QPoint);
    void handleValueChanged(int);



protected:
    QScopedPointer<HSoundWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

