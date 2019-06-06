/***************************************************************************************************
**      2019-05-29  桥接模式
**                  https://blog.csdn.net/liang19890820/article/details/66974516
***************************************************************************************************/

#ifndef HBRIDGE_H
#define HBRIDGE_H

// 电器
class IElectricalEquipment
{
public:
    virtual ~IElectricalEquipment() = default;

public:
    // 打开
    virtual void powerOn() = 0;
    // 关闭
    virtual void powerOff() = 0;
};

// 电灯
class Light : public IElectricalEquipment
{
public:
    void powerOn() override;
    void powerOff() override;
};

// 风扇
class Fan : public IElectricalEquipment
{
public:
    void powerOn() override;
    void powerOff() override;
};

// 开关
class ISwitch
{
public:
    ISwitch(IElectricalEquipment *);
    virtual ~ISwitch() = default;

public:
    // 打开电器
    virtual void on() = 0;
    // 关闭电器
    virtual void off() = 0;

protected:
    IElectricalEquipment *_ee;
};

// 拉链式开关
class PullChainSwitch : public ISwitch
{
public:
    PullChainSwitch(IElectricalEquipment *);

public:
    void on() override;
    void off() override;
};

// 两位开关
class TwoPositionSwitch : public ISwitch
{
public:
    TwoPositionSwitch(IElectricalEquipment *);

public:
    void on() override;
    void off() override;
};

#endif // HBRIDGE_H
