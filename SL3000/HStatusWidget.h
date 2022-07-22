/***************************************************************************************************
**      2022-07-15  HStatusWidget
***************************************************************************************************/

#pragma once

#include <QtWidgets/QWidget>

class HStatusWidgetPrivate;

class HStatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HStatusWidget(const QString &text, QVector<int> indexs, QWidget *parent = nullptr);
    ~HStatusWidget() override;

public:
    void setStatus(int index, bool b);

protected:
    QScopedPointer<HStatusWidgetPrivate> d_ptr;
};



