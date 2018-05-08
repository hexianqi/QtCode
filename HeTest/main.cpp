#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include "HeAlgorithm/HRegister.h"
#include "HeAlgorithm/HSpectrumFacade.h"
#include <functional>
#include <QTreeWidgetItem>

//using namespace He::Algorithm;

HE_ALGORITHM_USE_NAMESPACE

// 测试注册机
void TestRegister()
{
    HRegister reg;
    if (reg.checkRegisterCode())
        return;

    auto id = reg.getRegisterId();
    auto code = reg.encrypt(id);
    qDebug() << id;
    qDebug() << code;
    reg.setRegisterCode(code);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    std::function<int(int,int)> fun;
//    TestRegister();

//    HSpectrumFacade sf;
//    sf.getChromaticity();

    MainWindow w;
    qDebug() << w.objectName();
    w.setObjectName("Test123");
    qDebug() << w.objectName();
    w.show();

    return a.exec();
}



