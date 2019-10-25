/***************************************************************************************************
**      2019-04-23  HAbstractGradeItemDialog 抽象分级数据编辑对话框。
***************************************************************************************************/


#ifndef HABSTRACTGRADEITEMDIALOG_H
#define HABSTRACTGRADEITEMDIALOG_H

#include "HGuiGlobal.h"
#include "HeData/HDataGlobal.h"
#include <QtWidgets/QDialog>

HE_DATA_BEGIN_NAMESPACE
class IGradeItem;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAbstractGradeItemDialogPrivate;

class HAbstractGradeItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HAbstractGradeItemDialog(QWidget *parent = nullptr);
    ~HAbstractGradeItemDialog() override;

public:
    virtual void setData(IGradeItem *);

protected:
    HAbstractGradeItemDialog(HAbstractGradeItemDialogPrivate &p, QWidget *parent = nullptr);

protected:
    void done(int result) override;
    virtual bool setAverageMode(bool b);
    virtual void averageLevels() = 0;
    virtual void showData() = 0;
    virtual void saveData() = 0;

protected:
    QScopedPointer<HAbstractGradeItemDialogPrivate> d_ptr;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTGRADEITEMDIALOG_H
