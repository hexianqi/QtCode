#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HSmoothCurveDemoWidget;
}

HE_BEGIN_NAMESPACE

class HSmoothCurveDemoWidgetPrivate;

class HSmoothCurveDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HSmoothCurveDemoWidget(QWidget *parent = nullptr);
    ~HSmoothCurveDemoWidget() override;

protected:
    void paintEvent(QPaintEvent *) override;
    void updateCurve();

private:
    Ui::HSmoothCurveDemoWidget *ui;
    QScopedPointer<HSmoothCurveDemoWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

