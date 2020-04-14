/***************************************************************************************************
**      2019-06-27  HAnimationProgress 动画进度
***************************************************************************************************/

#ifndef HANIMATIONPROGRESS_H
#define HANIMATIONPROGRESS_H

#include "HAbstractProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAnimationProgressPrivate;

class HAnimationProgress : public HAbstractProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAnimationProgress)
    Q_PROPERTY(bool animationEnable READ isAnimationEnable WRITE setAnimationEnable)
    Q_PROPERTY(int duration READ duration WRITE setDuration)
    Q_PROPERTY(double currentValue READ currentValue WRITE setCurrentValue)

public:
    explicit HAnimationProgress(QWidget *parent = nullptr);

public:
    bool isAnimationEnable() const;
    int duration() const;
    double currentValue() const;

public slots:
    virtual void setValue(double value) override;
    virtual void setAnimationEnable(bool b);
    virtual void setDuration(int value);
    virtual void setCurrentValue(double value);

protected:
    HAnimationProgress(HAnimationProgressPrivate &p, QWidget *parent = nullptr);

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HANIMATIONPROGRESS_H
