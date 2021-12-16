/***************************************************************************************************
**      2020-01-13  HTipWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QFrame>
#include <QtGui/QIcon>

class QTextBrowser;

HE_BEGIN_NAMESPACE

class HTipWidgetPrivate;

class HTipWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QStringList tips READ tips WRITE setTips)
    Q_PROPERTY(int currentTip READ currentTip WRITE setCurrentTip)
    Q_PROPERTY(QIcon defaultIcon READ defaultIcon WRITE setDefaultIcon)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(Qt::Alignment iconAlignment READ iconAlignment WRITE setIconAlignment)
    Q_PROPERTY(bool checkVisible READ isCheckVisible WRITE setCheckVisible)
    Q_PROPERTY(bool closeVisible READ isCloseVisible WRITE setCloseVisible)
    Q_PROPERTY(bool tipsEnabled READ isTipsEnabled WRITE setTipsEnabled)

public:
    explicit HTipWidget(QWidget *parent = nullptr);
    ~HTipWidget() override;

signals:
    void tipChanged(int);

public:
    QStringList tips() const;
    int currentTip() const;
    QIcon defaultIcon() const;
    QSize iconSize() const;
    Qt::Alignment iconAlignment() const;
    bool isCheckVisible() const;
    bool isCloseVisible() const;
    bool isTipsEnabled() const;
    Shape canvasFrameShape() const;
    QWidget *headerWidget() const;
    QTextBrowser *tipCanvas() const;

public slots:
    void setTips(const QStringList &);
    void setCurrentTip(int value);
    void setDefaultIcon(const QIcon &);
    void setIconSize(QSize value);
    void setIconAlignment(Qt::Alignment value);
    void setCheckVisible(bool b);
    void setCloseVisible(bool b);
    void setTipsEnabled(bool b);
    void setCanvasFrameShape(Shape value);
    void setHeaderWidget(QWidget *);
    void prevTip();
    void nextTip();
    void showTip();

protected:
    HTipWidget(HTipWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HTipWidgetPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
