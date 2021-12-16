/***************************************************************************************************
**      2020-12-07  HTextEngine
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>
#include <QtGui/QVector2D>

HE_BEGIN_NAMESPACE

class HTextEnginePrivate;

class HTextEngine : public QObject
{
    Q_OBJECT

public:
    explicit HTextEngine(QObject *parent = nullptr);
    ~HTextEngine() override;

public:
    bool setFont(const QString &fontName, int pixelSize);

public:
    void render(const QString &text, QVector2D position = QVector2D(), int pixelSize = -1, int space = 10);

protected:
    HTextEngine(HTextEnginePrivate &p, QObject *parent = nullptr);

protected:
    bool initialize();
    void clear();

protected:
    QScopedPointer<HTextEnginePrivate> d_ptr;
};

HE_END_NAMESPACE

