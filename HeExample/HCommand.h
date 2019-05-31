/***************************************************************************************************
**      2019-05-30  命令模式
**                  https://blog.csdn.net/liang19890820/article/details/62060457
***************************************************************************************************/

#ifndef HCOMMAND_H
#define HCOMMAND_H

#include <list>

using namespace std;


// 司机
class Reciever
{
public:
    // 接单
    void takeOrder();
    // 收款
    void receipt();
};

// 提供执行命令的接口
class Command
{
public:
    Command(Reciever *);
    virtual ~Command() = default;

public:
    // 执行命令
    virtual void execute() = 0;

protected:
    Reciever *_reciever;
};

// 打车
class TakeCommand : public Command
{
public:
    TakeCommand(Reciever *);

public:
    void execute() override;
};

// 付款
class PayCommand : public Command
{
public:
    PayCommand(Reciever *);

public:
    void execute() override;
};

// 命令的持有者
class Invoker
{
public:
    Invoker();

public:
    // 添加命令
    void addCmd(Command *);
    // 删除命令
    void deleteCmd(Command *);
    // 执行命令
    void notify();

private:
    list<Command *> _cmds;
};

#endif // HCOMMAND_H
