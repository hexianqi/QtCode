/***************************************************************************************************
**      2020-12-21  HBrick
***************************************************************************************************/

#pragma once

#include "HGameObject.h"

HE_CONTROL_BEGIN_NAMESPACE

class HBrickPrivate;

class HBrick : public HGameObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBrick)

public:
    explicit HBrick(QObject *parent = nullptr);
    ~HBrick() override;

public:
    bool isSolid();
    bool isDestroyed();

public:
    void setSolid(bool);
    void setDestroyed(bool);

protected:
    HBrick(HBrickPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

