#pragma once

#include <QtWidgets/QWidget>

namespace Ui {
class HTestResultWidget;
}

class HTestResultWidgetPrivate;

class HTestResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HTestResultWidget(QWidget *parent = nullptr);
    ~HTestResultWidget();

public:
    void setLedType();
    void clearResult();

protected:
    void initialize();

private:
    QScopedPointer<HTestResultWidgetPrivate> d_ptr;
    Ui::HTestResultWidget *ui;
};

