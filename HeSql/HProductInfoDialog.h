/***************************************************************************************************
**      2019-05-14  HProductInfoDialog 产品信息配置对话框。
***************************************************************************************************/

#ifndef HPRODUCTINFODIALOG_H
#define HPRODUCTINFODIALOG_H

#include "HSqlGlobal.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HProductInfoDialog;
}

HE_SQL_BEGIN_NAMESPACE

class IProductInfo;
class HProductInfoDialogPrivate;

class HProductInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HProductInfoDialog(QWidget *parent = nullptr);
    ~HProductInfoDialog();

public:
    void setData(IProductInfo *);

protected:
    void done(int result);
    void showData();
    void saveData();

protected:
    QScopedPointer<HProductInfoDialogPrivate> d_ptr;

private:
    void init();

private:
    Ui::HProductInfoDialog *ui;
};

HE_SQL_END_NAMESPACE

#endif // HPRODUCTINFODIALOG_H
