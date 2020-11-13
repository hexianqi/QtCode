/***************************************************************************************************
**      2020-12-21  HGameLevel
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HSpriteRenderer;
class HBrick;
class HGameLevelPrivate;

class HGameLevel : public QObject
{
    Q_OBJECT

public:
    explicit HGameLevel(QObject *parent = nullptr);
    ~HGameLevel() override;

public:
    QVector<HBrick *> bricks();
    bool isCompleted();

public:
    bool load(const QString &fileName, int width, int height);
    bool load(QVector<QVector<uint>> data, int width, int height);
    void draw(HSpriteRenderer *);
    void reset();

protected:
    HGameLevel(HGameLevelPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HGameLevelPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

