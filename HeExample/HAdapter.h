/***************************************************************************************************
**      2019-05-29  适配器模式
**                  https://blog.csdn.net/liang19890820/article/details/66974516
***************************************************************************************************/

#ifndef HADAPTER_H
#define HADAPTER_H

// 俄罗斯提供的插座
class IRussiaSocket
{
public:
    // 使用双脚圆形充电（暂不实现）
    virtual void charge() = 0;
};

// 自带的充电器 - 两脚扁型
class OwnCharger
{
public:
    void chargeWithFeetFlat();
};

// 电源适配器
class PowerAdapter : public IRussiaSocket
{
public:
    PowerAdapter();
    virtual ~PowerAdapter();

public:
    void charge() override;

private:
    // 持有需要被适配的接口对象 - 自带的充电器
    OwnCharger *_charger;
};

#endif // HADAPTER_H
