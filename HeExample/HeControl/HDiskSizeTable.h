/***************************************************************************************************
**      2016-11-30  HDiskSizeTable 本地存储空间大小控件
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1:可自动加载本地存储设备的总容量/已用容量
**                  2:进度条显示已用容量
**                  3:支持所有操作系统
**                  4:增加U盘或者SD卡到达信号
***************************************************************************************************/

#ifndef HDISKSIZETABLE_H
#define HDISKSIZETABLE_H

#include "HControlGlobal.h"
#include <QtWidgets/QTableWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HDiskSizeTablePrivate;

class HDiskSizeTable : public QTableWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor chunkColor1 READ chunkColor1 WRITE setChunkColor1)
    Q_PROPERTY(QColor chunkColor2 READ chunkColor2 WRITE setChunkColor2)
    Q_PROPERTY(QColor chunkColor3 READ chunkColor3 WRITE setChunkColor3)
    Q_PROPERTY(QColor textColor1 READ textColor1 WRITE setTextColor1)
    Q_PROPERTY(QColor textColor2 READ textColor2 WRITE setTextColor2)
    Q_PROPERTY(QColor textColor3 READ textColor3 WRITE setTextColor3)

public:
    explicit HDiskSizeTable(QWidget *parent = nullptr);
    ~HDiskSizeTable() override;

signals:
    void sdcardReceive(const QString &name);
    void udiskReceive(const QString &name);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QColor background() const;
    QColor chunkColor1() const;
    QColor chunkColor2() const;
    QColor chunkColor3() const;
    QColor textColor1() const;
    QColor textColor2() const;
    QColor textColor3() const;

public slots:
    void load();
    void setBackground(const QColor &value);
    void setChunkColor1(const QColor &value);
    void setChunkColor2(const QColor &value);
    void setChunkColor3(const QColor &value);
    void setTextColor1(const QColor &value);
    void setTextColor2(const QColor &value);
    void setTextColor3(const QColor &value);

protected:
    HDiskSizeTable(HDiskSizeTablePrivate &p, QWidget *parent = nullptr);

protected:
    void insertSize(const QString &name, const QString &use, const QString &free, const QString &all, double percent);
#ifndef Q_OS_WIN
    void readData();
    void checkSize(const QString &result, const QString &name);
#endif

protected:
    QScopedPointer<HDiskSizeTablePrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HDISKSIZETABLE_H
