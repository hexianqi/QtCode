#include "frmmain.h"
//zhb,2020307创建，SML四通道LED分光机软件
#include "frmlogin.h"

#include <QApplication>
#include "single_application.h"     //判断程序实例是否已经运行
#include <qmessagebox.h>
#include "unitpublic.h"
#include "qsplashscreen.h"  //欢迎页面

int main(int argc, char *argv[])
{
 //   QApplication a(argc, argv);
 //   frmmain w;
 //   w.show();
 //   return a.exec();
    SingleApplication app(argc,argv,"some unique key string : SML4-LEDSORT");
    if(app.isRunning())
    {
        app.sendMessage("message from other instance.");
        QMessageBox::information(NULL,"提示","程序已经运行！");
        return 0;
    }
    unitpublic::dbmysql = QSqlDatabase::addDatabase("QODBC","mysql");       //利用ODBC连接mysql，注意odbc驱动版本要跟gcc版本一样，都是32位
          //注意：addDatabase这里一定要指定一个连接名，比如“mysql”，否则qt也会使用默认连接名qt_sql_default_connection，
          //这样跟后面的sqlite数据库的链接冲突了，因为后面我们采用也是默认qt_sql_default_connection连接名，导致mysql数据库连接和sqlite都出现异常
          //这样指定mysql连接名后，就没有问题，同时dbmysql是全局变量，可以在其他地方直接访问这个链接，类似长连接，但mysql默认是超过8小时连接无通信，就会断开连接，可以后续再处理
    unitpublic::dbmysql.setHostName("127.0.0.1");
    unitpublic::dbmysql.setPort(3306);
    unitpublic::dbmysql.setDatabaseName("ledsort-mysql");
    unitpublic::dbmysql.setUserName("root");
    unitpublic::dbmysql.setPassword("123456");
    if(!unitpublic::dbmysql.open())
    {
        QMessageBox::information(NULL,"提示","MySQL数据库连接失败，程序无法启动！");
        return 0;
    }
    unitpublic::dbmysql.setConnectOptions("CLIENT_INTERACTIVE=31536000");   //设置mysql长连接时长，31536000=365*24*60*60秒，即1年
    for(int i=0;i<ST_COUNT;i++){        //初始化线程内的连接池
        unitpublic::dblstmysql[i] = QSqlDatabase::addDatabase("QODBC","mysql"+QString::number(i));       //利用ODBC连接mysql，注意odbc驱动版本要跟gcc版本一样，都是32位
        unitpublic::dblstmysql[i].setHostName("127.0.0.1");
        unitpublic::dblstmysql[i].setPort(3306);
        unitpublic::dblstmysql[i].setDatabaseName("ledsort-mysql");
        unitpublic::dblstmysql[i].setUserName("root");
        unitpublic::dblstmysql[i].setPassword("123456");
        if(!unitpublic::dblstmysql[i].open())
        {
            QMessageBox::information(NULL,"提示","MySQL数据库连接失败，程序无法启动！");
            return 0;
        }
        unitpublic::dblstmysql[i].setConnectOptions("CLIENT_INTERACTIVE=31536000");
    }

    frmlogin login;     //登录页面
    if(login.exec()==QDialog::Accepted){        //登录成功
        //进入欢迎界面
        QPixmap pixmap(":/new/prefix1/res/pic/welcome.png");     //读取图片
        QSplashScreen splash(pixmap); //
        splash.setWindowOpacity(0.98); // 设置窗口透明度
        splash.show();
        splash.showMessage("程序正在加载......", Qt::AlignCenter, Qt::red); //显示文字
        QDateTime time = QDateTime::currentDateTime();
        QDateTime currentTime = QDateTime::currentDateTime(); //记录当前时间
        while (time.secsTo(currentTime) <= 3) // 3为需要延时的秒数
        {
          currentTime = QDateTime::currentDateTime();
          app.processEvents();
        };

        frmmain w;  //这个时候比较耗时，弄个欢迎界面，避免程序傻等
        w.show();        
        splash.finish(&w); //在主体对象初始化完成后结束启动动画

        return app.exec();
    }else
        return 0;
}
