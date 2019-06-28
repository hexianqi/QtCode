/***************************************************************************************************
**      2019-06-21  HWheelCircular 轮子
***************************************************************************************************/

#ifndef HWHEELCIRCULAR_H
#define HWHEELCIRCULAR_H

#include "HAbstractCircular.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HWheelCircularPrivate;

class HWheelCircular : public HAbstractCircular
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HWheelCircular)
    Q_PROPERTY(QColor backgroundStart   READ backgroundStart    WRITE setBackgroundStart)
    Q_PROPERTY(QColor backgroundEnd     READ backgroundEnd      WRITE setBackgroundEnd)
    Q_PROPERTY(QColor foreground1Start  READ foreground1Start   WRITE setForeground1Start)
    Q_PROPERTY(QColor foreground1End    READ foreground1End     WRITE setForeground1End)
    Q_PROPERTY(QColor foreground2Start  READ foreground2Start   WRITE setForeground2Start)
    Q_PROPERTY(QColor foreground2End    READ foreground2End     WRITE setForeground2End)

public:
    explicit HWheelCircular(QObject *parent = nullptr);
    ~HWheelCircular() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, QVariantMap param = QVariantMap()) override;

public:
    QColor backgroundStart() const;
    QColor backgroundEnd() const;
    QColor foreground1Start() const;
    QColor foreground1End() const;
    QColor foreground2Start() const;
    QColor foreground2End() const;

public slots:
    void setBackgroundStart(const QColor &value);
    void setBackgroundEnd(const QColor &value);
    void setForeground1Start(const QColor &value);
    void setForeground1End(const QColor &value);
    void setForeground2Start(const QColor &value);
    void setForeground2End(const QColor &value);

protected:
    HWheelCircular(HWheelCircularPrivate &p, QObject *parent = nullptr);

protected:
    void drawBackground(QPainter *);
    void drawCircle(QPainter *);
};

HE_CONTROL_END_NAMESPACE

#endif // HWHEELCIRCULAR_H
