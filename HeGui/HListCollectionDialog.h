/***************************************************************************************************
**      2019-04-19  HListCollectionDialog 集合配置对话框（列表模式）。
***************************************************************************************************/

#ifndef HLISTCOLLECTIONDIALOG_H
#define HLISTCOLLECTIONDIALOG_H

#include "HGuiGlobal.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HListCollectionDialog;
}

HE_GUI_BEGIN_NAMESPACE

class IDataDetail;
class HListCollectionDialogPrivate;

class HE_GUI_EXPORT HListCollectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HListCollectionDialog(QWidget *parent = nullptr);
    ~HListCollectionDialog();

public:
    void setDataDetail(IDataDetail *);

protected:
    void done(int result) override;

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

protected:
    void setCurrentIndex(QModelIndex index);
    void handleSourceChanged(QStringList names, QString name);

protected:
    QScopedPointer<HListCollectionDialogPrivate> d_ptr;

private:
    void init();

private:
    Ui::HListCollectionDialog *ui;
};

HE_GUI_END_NAMESPACE

#endif // HLISTCOLLECTIONDIALOG_H
