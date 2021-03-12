/***************************************************************************************************
**      2019-06-19  HCircularProgress 等待进度条。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class ICircular;
class HCircularProgressPrivate;

class HCircularProgress : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool reverse READ isReverse WRITE setReverse)
    Q_PROPERTY(int step READ step WRITE step)
    Q_PROPERTY(int duration READ duration WRITE setDuration)

public:
    explicit HCircularProgress(QWidget *parent = nullptr);
    ~HCircularProgress() override;

public:
    QSize sizeHint() const override;
    bool isReverse() const;
    int step() const;
    int duration() const;

public slots:
    void setReverse(bool b);
    void step(int value);
    void setDuration(int value);

public:
    void setCircular(ICircular *);

protected:
    HCircularProgress(HCircularProgressPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void updateValue();
    virtual void changeCircular(QAction *);

protected:
    QScopedPointer<HCircularProgressPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
