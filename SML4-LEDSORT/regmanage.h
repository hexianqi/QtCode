#ifndef WIDGET_H
#define WIDGET_H
//软件注册授权管理

#include <QWidget>
#include <QDebug>
#include <QProcess>
#include <windows.h>

class Regmanage : public QWidget
{
    Q_OBJECT

public:
    Regmanage(QWidget *parent = nullptr);
    ~Regmanage();

    QString getCpuName();
    QString getCpuId();
    QString getBaseboardNum();
    QString getBiosNum();
    QString getDiskNum();
};
#endif // WIDGET_H
