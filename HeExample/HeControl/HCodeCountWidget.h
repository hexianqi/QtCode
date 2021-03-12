/***************************************************************************************************
**      2019-12-09  HCodeCountWidget 代码统计窗体。
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HCodeCountWidget;
}

HE_CONTROL_BEGIN_NAMESPACE

class HCodeCountWidgetPrivate;

class HCodeCountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HCodeCountWidget(QWidget *parent = nullptr);
    ~HCodeCountWidget() override;

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    void init();
    void clear();
    bool checkFile(const QString &file);
    QStringList countCode(const QString &path);
    void countCode(const QStringList &files);
    void countCode(const QString &file, quint32 &lineCode, quint32 &lineBlank, quint32 &lineNotes);

private:
    Ui::HCodeCountWidget *ui;
    QScopedPointer<HCodeCountWidgetPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
