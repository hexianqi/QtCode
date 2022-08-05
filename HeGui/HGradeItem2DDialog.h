/***************************************************************************************************
**      2019-04-23  HGradeItem2DDialog 分级数据编辑对话框(2D)。
***************************************************************************************************/

#pragma once

#include "HAbstractGradeItemDialog.h"

namespace Ui {
class HGradeItem2DDialog;
}

HE_BEGIN_NAMESPACE

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
    void handleCellChanged(int row, int column);

protected:
    bool setAverageMode(bool b) override;
    void averageLevels() override;
    void showData() override;
    void saveData() override;
    QPolygonF getLevel(int row);
    QList<QPolygonF> getLevels();
    void showLevels(QList<QPolygonF> value);
    QString getName(int row);

private:
    void init();

private:
    Ui::HGradeItem2DDialog *ui;
};

HE_END_NAMESPACE
