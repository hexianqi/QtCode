/***************************************************************************************************
**      2022-05-17  HDecoratorDialog 装饰对话框。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QDialog>

HE_BEGIN_NAMESPACE

class ITestWidget;
class IMainWindow;

class HDecoratorDialogPrivate;

class HDecoratorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HDecoratorDialog(IMainWindow *parent);
    ~HDecoratorDialog() override;

public:
    int run(ITestWidget *);

protected:
    HDecoratorDialog(HDecoratorDialogPrivate &p, QWidget *parent = nullptr);

protected:
    void done(int result) override;

protected:
    QScopedPointer<HDecoratorDialogPrivate> d_ptr;
};

HE_END_NAMESPACE

