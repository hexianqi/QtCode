/***************************************************************************************************
**      2019-04-30  HGradeEditWidget 分级数据编辑窗体。
***************************************************************************************************/

#pragma once

#include "IDataEditer.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QWidget>

HE_DATA_BEGIN_NAMESPACE
class IGrade;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HGradeEditWidgetPrivate;

class HGradeEditWidget : public QWidget, public IDataEditer<IGrade>
{
    Q_OBJECT

public:
    explicit HGradeEditWidget(QWidget *parent = nullptr);
    ~HGradeEditWidget() override;

public:
    void initialize(QVariantMap param) override;
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

HE_GUI_END_NAMESPACE
