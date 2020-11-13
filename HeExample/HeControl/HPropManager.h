/***************************************************************************************************
**      2020-12-21  HPropManager
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

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
    void update(float dt);
    void draw(HSpriteRenderer *);
    void collision(HGameObject *, int height);
    void spawn(QVector2D);
    void reset();

protected:
    HProp *createProp(const QString &, QVector2D);
    void handleActivate(bool);
    bool isOtherActivate(HProp *);

protected:
    QScopedPointer<HPropManagerPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

