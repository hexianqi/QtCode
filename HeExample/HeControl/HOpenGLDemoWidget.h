/***************************************************************************************************
**      2020-11-05  HOpenGLDemoWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HOpenGLDemoWidget;
}

HE_BEGIN_NAMESPACE

class HOpenGLDemoWidgetPrivate;

class HOpenGLDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HOpenGLDemoWidget(QWidget *parent = nullptr);
    ~HOpenGLDemoWidget();

protected:
    HOpenGLDemoWidget(HOpenGLDemoWidgetPrivate &p, QWidget *parent = nullptr);

protected slots:
    void on_treeWidget_itemSelectionChanged();

protected:
    void init();

protected:
    QScopedPointer<HOpenGLDemoWidgetPrivate> d_ptr;

private:
    Ui::HOpenGLDemoWidget *ui;
};

HE_END_NAMESPACE

