#ifndef FRMVERIFY_H
#define FRMVERIFY_H
//参数校准
#include <QWidget>
#include "qmenu.h"

namespace Ui {
class Frmverify;
}

class Frmverify : public QWidget
{
    Q_OBJECT

public:
    explicit Frmverify(qint8 iindex,QWidget *parent = nullptr);
    ~Frmverify();

private:
    Ui::Frmverify *ui;
    QMenu* m_menu;      //右键菜单
    QAction* actClear;  //清除按钮

public:
    qint8 itag;             //标签，对应测试工位序号

    int ibincount;
    void tvfinit();         //校准参数列表初始化

private slots:
    void mupdatevfypara(int iindex);       //刷新参数，修改并保存基本参数后，需要重置校准参数
    void on_btndaoru_clicked();
    void on_tvfset_customContextMenuRequested(const QPoint &pos);
    void slot_clear();      //鼠标右键清除所选的单元格数据
    void on_btnjisuan_clicked();
    void msavevfyset(int iindex);
};

#endif // FRMVERIFY_H
