#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

namespace Ui {
class HLogDemoWidget;
}

class QListWidgetItem;

HE_BEGIN_NAMESPACE

class HLogDemoWidgetPrivate;

class HLogDemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HLogDemoWidget(QWidget *parent = nullptr);
    ~HLogDemoWidget() override;

protected slots:
    void on_pushButton_clicked();
    void on_checkBox_1_clicked(bool);
    void on_checkBox_2_clicked(bool);
    void on_checkBox_3_clicked(bool);
    void on_comboBox_2_currentIndexChanged(int);
    void on_comboBox_3_currentIndexChanged(int);
    void on_listWidget_itemPressed(QListWidgetItem *);
    void append(QString text = QString());

private:
    void init();

private:
    Ui::HLogDemoWidget *ui;
    QScopedPointer<HLogDemoWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE

