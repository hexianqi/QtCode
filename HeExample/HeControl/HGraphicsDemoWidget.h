#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HGraphicsDemoWidget;
}

HE_BEGIN_NAMESPACE

class HGraphicsDemoWidgetPrivate;

class HGraphicsDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HGraphicsDemoWidget(QWidget *parent = nullptr);
    ~HGraphicsDemoWidget();

protected slots:
    void setItemFix(int);

private:
    void init();
    void initGraphicsView();
    void addTestItem();
    void addPixmapItem();
    void addSliderItem();
    void addColorBoardItem();
    void addNoteItem();
    void addDiscButtonItem();
    void addProxyWidget();

private:
    Ui::HGraphicsDemoWidget *ui;
    QScopedPointer<HGraphicsDemoWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

