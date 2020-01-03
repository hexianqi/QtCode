/***************************************************************************************************
**      2020-01-02  HScreenObject
***************************************************************************************************/

#ifndef HSCREENOBJECT_H
#define HSCREENOBJECT_H

#include "HControlGlobal.h"
#include <QtCore/QObject>

class QPainter;

HE_CONTROL_BEGIN_NAMESPACE

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
    void saveScreen(QString fileName);
    void saveFullScreen(QString fileName);

protected:
    HScreenObject(HScreenObjectPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HScreenObjectPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HSCREENOBJECT_H
