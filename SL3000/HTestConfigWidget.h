#pragma once

#include <QtWidgets/QWidget>

namespace Ui {
class HTestConfigWidget;
}

class HTestConfigWidgetPrivate;

class HTestConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HTestConfigWidget(QWidget *parent = nullptr);
    ~HTestConfigWidget();

protected:
    void initialize();

private:
    QScopedPointer<HTestConfigWidgetPrivate> d_ptr;
    Ui::HTestConfigWidget *ui;
};

