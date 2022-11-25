/***************************************************************************************************
**      2022-11-23  HIrregularPopupWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HIrregularPopupWidgetPrivate;

class HIrregularPopupWidget : public QWidget
{
    Q_OBJECT

public:
    enum SharpPosition
    {
        Left = 0,
        Right,
        Top,
        Bottom
    };

public:
    explicit HIrregularPopupWidget(QWidget *parent = nullptr);
    ~HIrregularPopupWidget() override;

public:
    QSize sizeHint() const override;
    void setText(const QString &);
    void setSharpPosition(SharpPosition);

protected:
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HIrregularPopupWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

