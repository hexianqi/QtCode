/***************************************************************************************************
**      2017-08-11  HIPAddress IP地址输入框控件
**                  https://gitee.com/feiyangqingyun/QWidgetDemo
**                  1:可设置IP地址,自动填入框
**                  2:可清空IP地址
**                  3:支持按下小圆点自动切换
**                  4:支持退格键自动切换
**                  5:支持IP地址过滤
**                  6:可设置背景色/边框颜色/边框圆角角度
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HIPAddressPrivate;

class HIPAddress : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString ip READ ip WRITE setIP)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)

public:
    explicit HIPAddress(QWidget *parent = nullptr);
    ~HIPAddress() override;

signals:
    void valueChanged(const QString &value);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QString ip() const;
    QColor background() const;
    QColor borderColor() const;
    int borderRadius() const;

public slots:
    void setIP(const QString &value);
    void setBackground(const QColor &value);
    void setBorderColor(const QColor &value);
    void setBorderRadius(int value);
    void clear();

protected:
    HIPAddress(HIPAddressPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void handleTextChanged(const QString &text);

protected:
    QScopedPointer<HIPAddressPrivate> d_ptr;

private:
    void init();
    void updateStyle();
};

HE_END_NAMESPACE
