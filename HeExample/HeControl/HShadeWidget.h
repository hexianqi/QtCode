/***************************************************************************************************
**      2019-12-20  HShadeWidget 遮罩层。
***************************************************************************************************/

#ifndef HSHADEWIDGET_H
#define HSHADEWIDGET_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HShadeWidgetPrivate;

class HShadeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HShadeWidget(QWidget *parent = nullptr);
    ~HShadeWidget() override;

public:
    void addWatched(QWidget *);
    void setBackground(const QColor &value);
    void setOpacity(double value);

protected:
    HShadeWidget(HShadeWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void showEvent(QShowEvent *) override;

protected:
    QScopedPointer<HShadeWidgetPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HSHADEWIDGET_H
