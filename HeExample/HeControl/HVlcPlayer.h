#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QMainWindow>

namespace Ui {
class HVlcPlayer;
}

HE_CONTROL_BEGIN_NAMESPACE

class HVlcPlayerPrivate;

class HVlcPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit HVlcPlayer(QWidget *parent = nullptr);
    ~HVlcPlayer();

protected slots:
    void on_action_101_triggered(bool checked = false);

protected:
    void init();
    void handleStateChanged(int value);

protected:
    QScopedPointer<HVlcPlayerPrivate> d_ptr;

private:
    Ui::HVlcPlayer *ui;
};

HE_CONTROL_END_NAMESPACE
