/***************************************************************************************************
**      2020-12-21  HProp
***************************************************************************************************/

#pragma once

#include "HGameObject.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPropPrivate;

class HProp : public HGameObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HProp)

public:
    explicit HProp(QObject *parent = nullptr);
    ~HProp() override;

signals:
    void activateChanged(bool);

public:
    QString type();
    bool isActivated();
    bool isDestroyed();
    bool isPermanent();

public:
    void setType(const QString &);
    void setDuration(float);
    void setActivated(bool);
    void setDestroyed(bool);
    void update(float dt);

protected:
    HProp(HPropPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

