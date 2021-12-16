/***************************************************************************************************
**      2019-04-30  HGradeEditWidget 分级数据编辑窗体。
***************************************************************************************************/

#pragma once

#include "IDataEditer.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class IGrade;

class HGradeEditWidgetPrivate;

class HGradeEditWidget : public QWidget, public IDataEditer<IGrade>
{
    Q_OBJECT

public:
    explicit HGradeEditWidget(QWidget *parent = nullptr);
    ~HGradeEditWidget() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QWidget *widget() override;
    IGrade *createData() override;
    void setData(IGrade *) override;
    void clearData() override;
    void saveData() override;
    void showData() override;

private:
    void init();

private:
    QScopedPointer<HGradeEditWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
