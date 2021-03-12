/***************************************************************************************************
**      2019-05-30  状态模式
***************************************************************************************************/

#pragma once

class TrafficLights;

// 信号灯的状态
class IState
{
public:
    virtual void handle() = 0;
};

// 红灯
class RedLight : public IState
{
public:
    RedLight(TrafficLights *);
    virtual ~RedLight() = default;

public:
    void handle() override;

private:
    TrafficLights *_context;
};

// 绿灯
class GreenLight : public IState
{
public:
    GreenLight(TrafficLights *);
    virtual ~GreenLight() = default;

public:
    void handle() override;

private:
    TrafficLights *_context;
};

// 黄灯
class YellowLight : public IState
{
public:
    YellowLight(TrafficLights *);
    virtual ~YellowLight() = default;

public:
    void handle() override;

private:
    TrafficLights *_context;
};

// 交通信号灯
class TrafficLights
{
public:
    TrafficLights();

public:
    void setState(IState *);
    void request();

private:
    IState* _state;
};
