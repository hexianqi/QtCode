/***************************************************************************************************
**      2017-04-11  HCustomComboBox 自定义宽高下拉框控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86175-ds-1.html#tpc
**                  1:可设置下拉框元素高度
**                  2:可设置下拉框元素宽度
**                  3:可设置是否自动调整下拉框元素宽度,根据元素宽高自动调整
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QComboBox>

HE_CONTROL_BEGIN_NAMESPACE

class HCustomComboBoxPrivate;

class HCustomComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(int itemWidth READ itemWidth WRITE setItemWidth)
    Q_PROPERTY(int itemHeight READ itemHeight WRITE setItemHeight)
    Q_PROPERTY(bool autoWidth READ isAutoWidth WRITE setAutoWidth)

public:
    explicit HCustomComboBox(QWidget *parent = nullptr);
    ~HCustomComboBox() override;

public:
    int itemWidth() const;
    int itemHeight() const;
    bool isAutoWidth() const;

public slots:
    void setItemWidth(int value);
    void setItemHeight(int value);
    void setAutoWidth(bool b);

protected:
    HCustomComboBox(HCustomComboBoxPrivate &p, QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *) override;

protected:
    QScopedPointer<HCustomComboBoxPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
