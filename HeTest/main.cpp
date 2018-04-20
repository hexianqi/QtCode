#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include "../HeAlgorithm/HRegister.h"
#include <functional>

//using namespace He::Algorithm;

//// 测试注册机
//void TestRegister()
//{
//    HRegister reg;
//    if (reg.checkRegisterCode())
//        return;

//    auto id = reg.getRegisterId();
//    auto code = reg.encrypt(id);
//    qDebug() << id;
//    qDebug() << code;
//    reg.setRegisterCode(code);
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    std::function<int(int,int)> fun;
    TestRegister()*/;
Q_INVOKABLE
    MainWindow w;
    w.show();

    return a.exec();
}



