#pragma once

#include "HAbstractTestDataEditDialog.h"

namespace Ui {
class HProductEditDialog;
}

HE_BEGIN_NAMESPACE

class HProductEditDialogPrivate;

class HProductEditDialog : public HAbstractTestDataEditDialog
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

HE_END_NAMESPACE
