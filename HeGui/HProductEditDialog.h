#pragma once

#include "HAbstractTestDataEditDialog.h"

namespace Ui {
class HProductEditDialog;
}

HE_GUI_BEGIN_NAMESPACE

class HProductEditDialogPrivate;

class HE_GUI_EXPORT HProductEditDialog : public HAbstractTestDataEditDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HProductEditDialog)

public:
    explicit HProductEditDialog(QWidget *parent = nullptr);
    ~HProductEditDialog() override;

public:
    QString typeName() override;

protected:
    void showData() override;
    void saveData() override;

private:
    void init();

private:
    Ui::HProductEditDialog *ui;
};

HE_GUI_END_NAMESPACE
