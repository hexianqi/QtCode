/***************************************************************************************************
**      2019-7-28  HCustomRing 环形图控件 （源码不全）
**                  http://www.qtcn.org/bbs/read-htm-tid-86031-ds-1.html#tpc
**                  1:可设置是否显示标题+标题文字+标题高度+标题字号
**                  2:可设置是否显示图例+图例高度+图例字号
**                  3:可设置背景颜色+文字颜色+高亮颜色+标识颜色
**                  4:可设置外圆颜色+中间圆颜色+内圆颜色
**                  5:可设置外圆数据集合+内圆数据集合
**                  6:鼠标悬停突出显示区域并高亮显示文字
**                  7:每个区域都可设置对应的颜色+文字描述+百分比
**                  8:支持直接字符串设置文字集合和百分比集合
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HCustomRingPrivate;

class HCustomRing : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool showTitle READ isShowTitle WRITE setShowTitle)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(int titleHeight READ titleHeight WRITE setTitleHeight)
    Q_PROPERTY(int titleFontSize READ titleFontSize WRITE setTitleFontSize)

    Q_PROPERTY(bool showLegend READ isShowLegend WRITE setShowLegend)
    Q_PROPERTY(int legendHeight READ legendHeight WRITE setLegendHeight)
    Q_PROPERTY(int legendFontSize READ legendFontSize WRITE setLegendFontSize)

    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor highColor READ highColor WRITE setHighColor)
    Q_PROPERTY(QColor flagColor READ flagColor WRITE setFlagColor)

    Q_PROPERTY(QColor outerCircleColor READ outerCircleColor WRITE setOuterCircleColor)
    Q_PROPERTY(QColor innerCircleColor READ innerCircleColor WRITE setInnerCircleColor)
    Q_PROPERTY(QColor centerCircleColor READ centerCircleColor WRITE setCenterCircleColor)

    Q_PROPERTY(QString outerPieInfos READ outerPieInfos WRITE setOuterPieInfos)
    Q_PROPERTY(QString innerPieInfos READ innerPieInfos WRITE setInnerPieInfos)

public:
    explicit HCustomRing(QWidget *parent = nullptr);
    ~HCustomRing() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    bool isShowTitle() const;
    QString title() const;
    int titleHeight() const;
    int titleFontSize() const;
    bool isShowLegend() const;
    int legendHeight() const;
    int legendFontSize() const;
    QColor background() const;
    QColor textColor() const;
    QColor highColor() const;
    QColor flagColor() const;
    QColor outerCircleColor() const;
    QColor innerCircleColor() const;
    QColor centerCircleColor() const;
    QString outerPieInfos() const;
    QString innerPieInfos() const;

public slots:
    void setShowTitle(bool b);
    void setTitle(const QString &value);
    void setTitleHeight(int value);
    void setTitleFontSize(int value);
    void setShowLegend(bool b);
    void setLegendHeight(int value);
    void setLegendFontSize(int value);
    void setBackground(const QColor &value);
    void setTextColor(const QColor &value);
    void setHighColor(const QColor &value);
    void setFlagColor(const QColor &value);
    void setOuterCircleColor(const QColor &value);
    void setInnerCircleColor(const QColor &value);
    void setCenterCircleColor(const QColor &value);
    void setOuterPieInfos(const QString &value);
    void setInnerPieInfos(const QString &value);

protected:
    HCustomRing(HCustomRingPrivate &p, QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawOuterCircle(QPainter *);
    void drawOuterPie(QPainter *painter, double scale, QPoint center);
    void drawCenterCircle(QPainter *);
    void drawInnerCircle(QPainter *);
    void drawInnerPie(QPainter *painter, double scale, QPoint center);
    void drawTitle(QPainter *);
    void drawLegend(QPainter *painter, double scale);

protected:
    QScopedPointer<HCustomRingPrivate> d_ptr;

private:

};

HE_CONTROL_END_NAMESPACE
