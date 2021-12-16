/***************************************************************************************************
**      2020-12-09  HGameLevel
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE

