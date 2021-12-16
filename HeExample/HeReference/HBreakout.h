/***************************************************************************************************
**      2020-12-08  HBreakout
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

class GLFWwindow;

HE_BEGIN_NAMESPACE

class HBreakoutPrivate;

class HBreakout : public QObject
{
    Q_OBJECT

public:
    explicit HBreakout(QObject *parent = nullptr);
    ~HBreakout() override;

public:
    void run();

protected:
    HBreakout(HBreakoutPrivate &p, QObject *parent = nullptr);

protected:
    void initGlfw();
    bool initFlad();
    bool createWindow();
    void perFrameTime();

protected:
    QScopedPointer<HBreakoutPrivate> d_ptr;
};

HE_END_NAMESPACE

