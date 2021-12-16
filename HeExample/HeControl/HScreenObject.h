/***************************************************************************************************
**      2020-01-02  HScreenObject
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

class QPainter;

HE_BEGIN_NAMESPACE

class HScreenObjectPrivate;

class HScreenObject : public QObject
{
    Q_OBJECT

public:
    enum Status
    {
        Select,
        Mov
    };

public:
    explicit HScreenObject(QObject *parent = nullptr);
    ~HScreenObject() override;

public:
    Status status() const;
    bool isInArea(QPoint);

public:
    void setStatus(Status);
    void setStart(QPoint);
    void setEnd(QPoint);
    void move(QPoint);
    void drawScreen(QPainter *);
    void initScreen();
    void saveScreen(const QString &fileName);
    void saveFullScreen(const QString &fileName);

protected:
    HScreenObject(HScreenObjectPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HScreenObjectPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
