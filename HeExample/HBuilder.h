/***************************************************************************************************
**      2019-05-29  建造者模式。
**                  https://blog.csdn.net/liang19890820/article/details/66968761
***************************************************************************************************/

#ifndef HBUILDER_H
#define HBUILDER_H

#include <string>

using namespace std;

// 电脑
class Computer
{
public:
    void setCpu(string value);
    void setMainboard(string value);
    void setRam(string value);
    void setVideoCard(string value);

    string getCPU();
    string getMainboard();
    string getRam();
    string getVideoCard();

private:
    string _cpu;
    string _mainboard;
    string _ram;
    string _videoCard;
};

// 建造者接口，组装流程
class IBuilder
{
public:
    // 创建 CPU
    virtual void buildCpu() = 0;
    // 创建主板
    virtual void buildMainboard() = 0;
    // 创建内存
    virtual void buildRam() = 0;
    // 创建显卡
    virtual void buildVideoCard() = 0;
    // 获取建造后的产品
    virtual Computer *getResult() = 0;
};

// ThinkPad 系列
class ThinkPadBuilder : public IBuilder
{
public:
    ThinkPadBuilder();
    virtual ~ThinkPadBuilder() = default;;

public:
    void buildCpu() override;
    void buildMainboard() override;
    void buildRam() override;
    void buildVideoCard() override;
    Computer *getResult() override;

private:
    Computer *_computer;
};

// Yoga 系列
class YogaBuilder : public IBuilder
{
public:
    YogaBuilder();
    virtual ~YogaBuilder() = default;

public:
    void buildCpu() override;
    void buildMainboard() override;
    void buildRam() override;
    void buildVideoCard() override;
    Computer *getResult() override;

private:
    Computer *_computer;
};

// 指挥者
class Direcror
{
public:
    void create(IBuilder *builder);
};

#endif // HBUILDER_H
