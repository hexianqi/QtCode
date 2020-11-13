/***************************************************************************************************
**      2020-12-08  HBreakout
***************************************************************************************************/

#pragma once

#include "HReferenceGlobal.h"
#include <QtCore/QObject>

class GLFWwindow;

HE_REFERENCE_BEGIN_NAMESPACE

class HBreakoutPrivate;

class HE_REFERENCE_EXPORT HBreakout : public QObject
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

HE_REFERENCE_END_NAMESPACE

