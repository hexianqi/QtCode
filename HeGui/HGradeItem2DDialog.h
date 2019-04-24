/***************************************************************************************************
**      2019-04-23  HGradeItem2DDialog 分级数据编辑对话框(2D)。
***************************************************************************************************/

#ifndef HGRADEITEM2DDIALOG_H
#define HGRADEITEM2DDIALOG_H

#include "HAbstractGradeItemDialog.h"

namespace Ui {
class HGradeItem2DDialog;
}

HE_GUI_BEGIN_NAMESPACE

class HGradeItem2DDialogPrivate;

class HGradeItem2DDialog : public HAbstractGradeItemDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGradeItem2DDialog)

public:
    explicit HGradeItem2DDialog(QWidget *parent = nullptr);
    ~HGradeItem2DDialog();

protected slots:
    void on_spinBox_02_valueChanged(int value);
    void on_checkBox_01_clicked(bool b);
    void on_pushButton_01_clicked();
    void on_pushButton_13_clicked();
    void setGradeFocus();
    void replacePoint(QPointF point);

protected:
    bool setAverageMode(bool b) override;
    void showData() override;
    void saveData() override;
    void averageLevels() override;
    QList<QPolygonF> getLevels();
    void showLevels(QList<QPolygonF> value);

private:
    void init();

private:
    Ui::HGradeItem2DDialog *ui;
};

HE_GUI_END_NAMESPACE

#endif // HGRADEITEM2DDIALOG_H
