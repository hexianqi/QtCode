#pragma once

#include "HMainWindow.h"
#include <QtCore/QMap>

class QextSerialPort;

class HMainWindowPrivate
{
public:
    HMainWindowPrivate();

public:
    void readSendData(const QString &fileName = QString());
    void readDeviceData(const QString &fileName = QString());

public:
    QString configFileName;             // 配置文件
    QString sendFileName;               // 发送数据文件名
    QString deviceFileName;             // 模拟设备数据文件名

    QStringList sendDatas;              // 发送数据
    QMap<QString, QString> deviceDatas; // 模拟设备数据

    QString portName;                   // 串口号
    int baudRate;                       // 波特率
    int dataBit;                        // 数据位
    QString parity;                     // 校验位
    double stopBit;                     // 停止位

    bool hexSend;                       // 16进制发送
    bool hexReceive;                    // 16进制接收
    bool debug;                         // 模拟设备
    bool autoClear;                     // 自动清空

    bool autoSend;                      // 自动发送
    int sendInterval;                   // 自动发送间隔
    bool autoSave;                      // 自动保存
    int saveInterval;                   // 自动保存间隔

    int sleepTime = 10;                 // 接收延时时间
    int sendCount = 0;                  // 发送数据计数
    int receiveCount = 0;               // 接收数据计数
    bool show = true;                 // 是否显示数据

    QextSerialPort *com = nullptr;      // 串口通信对象
    QTimer *timerRead = nullptr;        // 定时读取串口数据
    QTimer *timerSend = nullptr;        // 定时发送串口数据
    QTimer *timerSave = nullptr;        // 定时保存串口数据

    bool opened = false;
    int currentCount = 0;
    int maxCount = 100;
};
