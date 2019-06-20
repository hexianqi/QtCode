/***************************************************************************************************
**      2019-06-19  HTaichiWait 太极。
***************************************************************************************************/

#ifndef HTAICHIWAIT_H
#define HTAICHIWAIT_H

#include "HAbstractWait.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HTaichiWaitPrivate;

class HTaichiWait : public HAbstractWait
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTaichiWait)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HTaichiWait(QObject *parent = nullptr);
    ~HTaichiWait() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, QVariantMap param = QVariantMap()) override;

public:
    QColor background() const;
    QColor foreground() const;

public slots:
    void setBackground(const QColor &value);
    void setForeground(const QColor &value);

protected:
    HTaichiWait(HTaichiWaitPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HTAICHIWAIT_H
