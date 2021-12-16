/***************************************************************************************************
**      2019-06-10  HImageEffectWidget 图片特效。【注：现在只做了一张图片的特效】
**                  http://www.qtcn.org/bbs/read-htm-tid-85995-ds-1.html#tpc
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class IShaderEffect;
class HImageEffectWidgetPrivate;

class HImageEffectWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double factor READ factor WRITE setFactor)
    Q_PROPERTY(QString imageName1 READ imageName1 WRITE setImageName1)
    Q_PROPERTY(QString imageName2 READ imageName2 WRITE setImageName2)
    Q_PROPERTY(QPixmap pixmap1 READ pixmap1 WRITE setPixmap1)
    Q_PROPERTY(QPixmap pixmap2 READ pixmap2 WRITE setPixmap2)

public:
    explicit HImageEffectWidget(QWidget *parent = nullptr);
    ~HImageEffectWidget() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void setEffect(IShaderEffect *);
    double factor() const;
    QString imageName1() const;
    QString imageName2() const;
    QPixmap pixmap1() const;
    QPixmap pixmap2() const;

public slots:
    void setFactor(double value);
    void setImageName1(const QString &value);
    void setImageName2(const QString &value);
    void setPixmap1(const QPixmap &value);
    void setPixmap2(const QPixmap &value);
    void startAnimation();
    void stopAnimation();

protected:
    HImageEffectWidget(HImageEffectWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void changeEffect(QAction *);

protected:
    QScopedPointer<HImageEffectWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE


//public:
//    enum AnimationType {
//        FadeEffect = 0,             //图像1渐渐变淡,图像2渐渐显现
//        BlindsEffect = 1,           //百叶窗效果
//        FlipRightToLeft = 2,        //图像从右向左翻转
//        OutsideToInside = 3,        //从外到内水平分割
//        MoveLeftToRightEffect = 4,  //图像1从左至右退出可视区域,同时图像2从左至右进入可视区域
//        MoveRightToLeftEffect = 5,  //图像1从左至右退出可视区域,同时图像2从左至右进入可视区域
//        MoveBottomToUpEffect = 6,   //图像1从下至上退出可视区域,同时图像2从下至上进入可视区域
//        MoveUpToBottomEffect = 7,   //图像1从上至下退出可视区域,同时图像2从上至下进入可视区域
//        MoveBottomToLeftUpEffect = 8//图像1不动,同时图像2从右下到左上
//    };

//    explicit ImageAnimation(QWidget *parent = 0);
//    ~ImageAnimation();

//protected:
//    void paintEvent(QPaintEvent *);
//    void fadeEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);
//    void blindsEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);
//    void flipRightToLeft(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);
//    void outsideToInside(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);
//    void moveLeftToRightEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);
//    void moveRightToLeftEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);
//    void moveBottomToUpEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);
//    void moveUpToBottomEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);
//    void moveBottomToLeftUpEffect(QPainter *painter, const QRect &rect, float factor, const QPixmap &pixmap1, const QPixmap &pixmap2);


//    AnimationType animationType;    //动画效果类型

//    QPropertyAnimation *animation;  //动画属性

//public:

//    AnimationType getAnimationType()const;

//    QSize sizeHint()                const;
//    QSize minimumSizeHint()         const;

//public Q_SLOTS:


//    //设置动画类型
//    void setAnimationType(const AnimationType &animationType);


//};


