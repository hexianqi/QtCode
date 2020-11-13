/***************************************************************************************************
**      2020-12-09  HBrick
***************************************************************************************************/

#pragma once

#include "HGameObject.h"

HE_REFERENCE_BEGIN_NAMESPACE

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

HE_REFERENCE_END_NAMESPACE

