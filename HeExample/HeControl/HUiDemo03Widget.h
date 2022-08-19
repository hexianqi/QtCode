#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HUiDemo03Widget;
}

HE_BEGIN_NAMESPACE

class HUiDemo03Widget : public QWidget
{
    Q_OBJECT

public:
    explicit HUiDemo03Widget(QWidget *parent = nullptr);
    ~HUiDemo03Widget() override;

private:
    void init();

private:
    Ui::HUiDemo03Widget *ui;
};

HE_END_NAMESPACE
