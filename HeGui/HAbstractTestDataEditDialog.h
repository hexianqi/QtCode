/***************************************************************************************************
**      2020-10-27  HAbstractTestDataEditDialog
***************************************************************************************************/

#pragma once

#include "ITestDataEditDialog.h"

HE_BEGIN_NAMESPACE

class HAbstractTestDataEditDialogPrivate;

class HAbstractTestDataEditDialog : public ITestDataEditDialog
{
    Q_OBJECT

public:
    explicit HAbstractTestDataEditDialog(QWidget *parent = nullptr);
    ~HAbstractTestDataEditDialog() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void setData(ITestData *) override;

protected:
    HAbstractTestDataEditDialog(HAbstractTestDataEditDialogPrivate &p, QWidget *parent = nullptr);

protected:
    void done(int result) override;
    virtual void showData() = 0;
    virtual void saveData() = 0;

protected:
    QScopedPointer<HAbstractTestDataEditDialogPrivate> d_ptr;
};

HE_END_NAMESPACE

