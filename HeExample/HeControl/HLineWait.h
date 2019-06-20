/***************************************************************************************************
**      2019-06-20  HLineWait 线状
***************************************************************************************************/

#ifndef HLINEWAIT_H
#define HLINEWAIT_H

#include "HAbstractWait.h"
#include <QtGui/QColor>

HE_CONTROL_BEGIN_NAMESPACE

class HLineWaitPrivate;

class HLineWait : public HAbstractWait
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLineWait)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

public:
    explicit HLineWait(QObject *parent = nullptr);
    ~HLineWait() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void draw(QPainter *, QVariantMap param = QVariantMap()) override;

public:
    QColor foreground() const;

public slots:
    void setForeground(const QColor &value);

protected:
    HLineWait(HLineWaitPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HLINEWAIT_H
