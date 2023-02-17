#pragma once

#include "HeGui/HAbstractTestSetWidget.h"

HE_USE_NAMESPACE

namespace Ui {
class HTestSetWidget1000RGB;
}

class HTestSetWidget1000RGBPrivate;

class HTestSetWidget1000RGB : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestSetWidget1000RGB)

public:
    explicit HTestSetWidget1000RGB(QWidget *parent = nullptr);
    ~HTestSetWidget1000RGB();

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;

protected slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_11_clicked();

protected:
    int nextIndex(int);
    bool setCrystalIndex(int);

//protected slots:
//    void on_checkBox_1_clicked(bool b);
//    void on_checkBox_2_clicked(bool b);
//    bool setTestMode(int value) override;
//    void setCurrentGears(int value);
//    void setLuminousGears(int value);

//protected:
//    bool adjustIntegralTime();
//    bool adjustLuminousGears();

private:
    void init();

private:
    Ui::HTestSetWidget1000RGB *ui;
};

