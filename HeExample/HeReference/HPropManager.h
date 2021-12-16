/***************************************************************************************************
**      2020-12-11  HPropManager
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HSpriteRenderer;
class HGameObject;
class HProp;
class HPropManagerPrivate;

class HPropManager : public QObject
{
    Q_OBJECT

public:
    explicit HPropManager(QObject *parent = nullptr);
    ~HPropManager() override;

signals:
    void propStateChanged(const QString &, bool b);

public:
    void spawn(QVector2D);
    void update(float dt);
    void draw(HSpriteRenderer *);
    void collision(HGameObject *, int height);
    void reset();

protected:
    HProp *createProp(const QString &, QVector2D);
    void handleActivate(bool);
    bool isOtherActivate(HProp *);

protected:
    QScopedPointer<HPropManagerPrivate> d_ptr;
};

HE_END_NAMESPACE

