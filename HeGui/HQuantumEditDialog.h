#pragma once

#include "HAbstractTestDataEditDialog.h"

namespace Ui {
class HQuantumEditDialog;
}

HE_GUI_BEGIN_NAMESPACE

class HQuantumEditDialogPrivate;

class HE_GUI_EXPORT HQuantumEditDialog : public HAbstractTestDataEditDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HQuantumEditDialog)

public:
    explicit HQuantumEditDialog(QWidget *parent = nullptr);
    ~HQuantumEditDialog();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setData(ITestData *) override;

protected:
    void showData() override;
    void saveData() override;

private:
    void init();

private:
    Ui::HQuantumEditDialog *ui;
};

HE_GUI_END_NAMESPACE
