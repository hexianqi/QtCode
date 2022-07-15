#ifndef FRMSYSTEMSET_H
#define FRMSYSTEMSET_H
//系统设置页面
#include <QWidget>

namespace Ui {
class Frmsystemset;
}

class Frmsystemset : public QWidget
{
    Q_OBJECT

public:
    explicit Frmsystemset(qint8 iindex,QWidget *parent = nullptr);
    ~Frmsystemset();

private:
    Ui::Frmsystemset *ui;

public:
        qint8 itag;             //标签，对应测试工位序号

private slots:
    void msavesysset(int iindex);   //槽函数，接收主页面保存参数的信号
    void on_toolButton_13_clicked();
};

#endif // FRMSYSTEMSET_H
