/***************************************************************************************************
**      2019-08-20  HIconFontWidget 图标字体窗体演示。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HIconFontWidget;
}

HE_BEGIN_NAMESPACE

class HIconFontWidgetPrivate;

class HIconFontWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HIconFontWidget(QWidget *parent = nullptr);
    ~HIconFontWidget();

public slots:
    void setFontFamily(const QString &);

protected:
    bool checkIcon(int);

private:
    void init();

private:
    Ui::HIconFontWidget *ui;
    QScopedPointer<HIconFontWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
