/***************************************************************************************************
**      2019-05-13  HSqlFindDialog 数据库查询对话框。
***************************************************************************************************/

#ifndef HSQLFINDDIALOG_H
#define HSQLFINDDIALOG_H

#include "HSqlGlobal.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HSqlFindDialog;
}

HE_SQL_BEGIN_NAMESPACE

class HSqlFindDialogPrivate;

class HSqlFindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HSqlFindDialog(QStringList fields, QString filter = QString(), QWidget *parent = nullptr);
    ~HSqlFindDialog();

public:
    QString filter() const;

protected:
    void done(int result) override;

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    void init();

private:
    QScopedPointer<HSqlFindDialogPrivate> d_ptr;
    Ui::HSqlFindDialog *ui;
};

HE_SQL_END_NAMESPACE

#endif // HSQLFINDDIALOG_H
