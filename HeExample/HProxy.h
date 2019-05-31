/***************************************************************************************************
**      2019-05-30  代理模式
**                  https://blog.csdn.net/liang19890820/article/details/78533179
***************************************************************************************************/

#ifndef HPROXY_H
#define HPROXY_H

// 电信运营商
class ITelco
{
public:
    virtual ~ITelco() = default;

public:
    // 充值
    virtual void recharge(int money) = 0;
};

// 中国移动
class CMCC : public ITelco
{
public:
    void recharge(int money) override;
};

// 代理点
class Proxy : public ITelco
{
public:
    Proxy();
    ~Proxy() override;

public:
    void recharge(int money) override;

private:
    CMCC *_CMCC;
};

#endif // HPROXY_H
