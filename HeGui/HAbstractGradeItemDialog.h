/***************************************************************************************************
**      2019-04-23  HAbstractGradeItemDialog 抽象分级数据编辑对话框。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QDialog>

HE_BEGIN_NAMESPACE

class IGradeItem;
class HAbstractGradeItemDialogPrivate;

class HAbstractGradeItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HAbstractGradeItemDialog(QWidget *parent = nullptr);

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

HE_END_NAMESPACE
