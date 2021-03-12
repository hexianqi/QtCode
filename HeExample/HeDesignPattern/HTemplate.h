/***************************************************************************************************
**      2019-05-30  模版方法模式
***************************************************************************************************/

#pragma once

// 公司
class Company
{
public:
    virtual ~Company() = default;

public:
    // 校园招聘
    void recruit();

protected:
    // 宣讲会
    void careerTalk();
    // 接收简历
    void receiveResume();
    // 面试
    virtual void interview() = 0;
    // 发放 Offer
    virtual void offer() = 0;
};

// 阿里
class Alibaba : public Company
{
protected:
    void interview() override;
    void offer() override;
};

// 腾讯
class Tencent : public Company
{
protected:
    void interview() override;
    void offer() override;
};
