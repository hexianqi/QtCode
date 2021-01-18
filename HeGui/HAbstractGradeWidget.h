/***************************************************************************************************
**      2020-10-22  HAbstractGradeWidget
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QWidget>

HE_DATA_BEGIN_NAMESPACE
class IGrade;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAbstractGradeWidgetPrivate;

class HAbstractGradeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HAbstractGradeWidget(QWidget *parent = nullptr);
    ~HAbstractGradeWidget() override;

public:
    virtual void setData(IGrade *);
    virtual void clearData();
    virtual bool saveData();
    virtual bool showData();

protected:
    HAbstractGradeWidget(HAbstractGradeWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void insertGradeItem();
    void removeGradeItem();
    void editGradeItem();
    bool editGradeItem(const QString &type);

protected:
    QScopedPointer<HAbstractGradeWidgetPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

