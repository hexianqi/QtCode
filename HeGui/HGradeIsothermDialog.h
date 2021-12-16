/***************************************************************************************************
**      2019-04-24  HGradeIsothermDialog 等温线分级对话框。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QDialog>

namespace Ui {
class HGradeIsothermDialog;
}

HE_BEGIN_NAMESPACE

class HGradeIsothermDialogPrivate;

class HGradeIsothermDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HGradeIsothermDialog(QWidget *parent = nullptr);
    ~HGradeIsothermDialog() override;

public:
    QList<QPolygonF> levels();

protected:
    void done(int result) override;
    void showData();
    void saveData();

private:
    void init();
    void readSettings();
    void writeSettings();

private:
    QScopedPointer<HGradeIsothermDialogPrivate> d_ptr;
    Ui::HGradeIsothermDialog *ui;
};

HE_END_NAMESPACE
