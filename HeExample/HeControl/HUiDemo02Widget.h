#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HUiDemo02Widget;
}

HE_BEGIN_NAMESPACE

class HUiDemo02Widget : public QWidget
{
    Q_OBJECT

public:
    explicit HUiDemo02Widget(QWidget *parent = nullptr);
    ~HUiDemo02Widget();

protected slots:
    void on_toolButton_01_clicked();
    void updateBackground();

private:
    Ui::HUiDemo02Widget *ui;
    QStringList _imageFile;
    int _index = 0;
};

HE_END_NAMESPACE

