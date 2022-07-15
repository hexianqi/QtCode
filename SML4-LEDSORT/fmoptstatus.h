#ifndef FMOPTSTATUS_H
#define FMOPTSTATUS_H

#include <QWidget>

//光谱仪、测试机连接状态窗口显示类，在主界面frmmain中添加到下方状态栏

namespace Ui {
class FmOptStatus;
}

class FmOptStatus : public QWidget
{
    Q_OBJECT

public:
    explicit FmOptStatus(QString ltext, QWidget *parent = nullptr);
    ~FmOptStatus();

     //设置连接状态指示灯颜色，联机-绿色，掉线-红色
    //传入参数：iindex，光谱仪或测试机设备编号
    //         bcon，连接状态，true-联机，false-掉线
    void setConStatus(qint8 iindex,bool bcon);

private:
    Ui::FmOptStatus *ui;
};

#endif // FMOPTSTATUS_H
