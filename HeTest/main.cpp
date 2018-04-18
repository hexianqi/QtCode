#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include "../HeAlgorithm/HRegister.h"
#include <functional>

using namespace He::Algorithm;

// 测试注册机
void TestRegister()
{
    if (HRegister::checkRegisterCode())
        return;
    auto registerId = HRegister::getRegisterId();
    auto registerCode = HRegister::encrypt(registerId);
    qDebug() << registerId;
    qDebug() << registerCode;
    HRegister::setRegisterCode(registerCode);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    std::function<int(int,int)> fun;
    TestRegister()*/;

    MainWindow w;
    w.show();

    return a.exec();
}


