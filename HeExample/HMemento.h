/***************************************************************************************************
**      2019-05-30  备忘录模式
**                  https://blog.csdn.net/liang19890820/article/details/79292435
***************************************************************************************************/

#ifndef HMEMENTO_H
#define HMEMENTO_H

#include <string>
#include <vector>

using namespace std;

// 日期时间
class DateTime
{
public:
    DateTime(string);

public:
    void setDateTime(string);
    string getDateTime();

private:
    string _dateTime;
};

// 一生
class Life
{
public:
    void setDateTime(string);
    // 仅用于打印
    string getDateTime();
    // 恢复日期时间
    void setMemento(DateTime *);
    // 创建日期时间
    DateTime *createMemento();

private:
    string _dateTime;
};

// 月光宝盒
class PandoraBox
{
public:
    PandoraBox(Life *);
    ~PandoraBox();

public:
    // 保存备份
    void save();
    // 穿越至上一时刻
    void undo();

private:
    Life *_life;
    vector<DateTime *> _history;
};


#endif // HMEMENTO_H
