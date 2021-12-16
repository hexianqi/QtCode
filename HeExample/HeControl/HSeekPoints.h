/***************************************************************************************************
**      2020-09-03  HSeekPoints
**                  参考VLC-3.0.9.2
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>
#include <QtCore/QMutex>

HE_BEGIN_NAMESPACE

struct HSeekPoint
{
public:
    qlonglong time;
    QString name;
};

class HSeekPoints : public QObject
{
    Q_OBJECT

public:
    explicit HSeekPoints(QObject *parent = nullptr);

public:
    QList<HSeekPoint> points();

public:
    void setPoints(QList<HSeekPoint>);

public:
    bool access();
    void release();

private:
    QList<HSeekPoint> _points;
    QMutex _mutex;
};

HE_END_NAMESPACE

