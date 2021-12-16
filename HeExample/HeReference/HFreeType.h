/***************************************************************************************************
**      2020-12-04  HFreeType
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>
#include <QtGui/QVector2D>

HE_BEGIN_NAMESPACE

struct HCharacter;
class HFreeTypePrivate;

class HFreeType : public QObject
{
    Q_OBJECT

public:
    explicit HFreeType(QObject *parent = nullptr);
    ~HFreeType() override;

public:
    bool setFont(const QString &, int pixelSize);

public:
    void renderText(const QString &text, QVector2D position = QVector2D(), int pixelSize = -1, int space = 10);

protected:
    HFreeType(HFreeTypePrivate &p, QObject *parent = nullptr);

protected:
    bool initialize();
    HCharacter *findCharacter(QChar key);

protected:
    QScopedPointer<HFreeTypePrivate> d_ptr;
};

HE_END_NAMESPACE

