/***************************************************************************************************
**      2019-05-30  解释器模式
**                  https://blog.csdn.net/zang141588761/article/details/53483645
***************************************************************************************************/

#ifndef HINTERPRETER_H
#define HINTERPRETER_H

#include <string>
#include <map>

//#include <typeinfo>

using namespace std;

/***********************************
**  场景：四则运算
************************************/

// 抽象表达式类
class Expression
{
public:
    virtual ~Expression() = default;

public:
    // 解析公式和数值，
    // 其中var中的key是公式中的参数，
    // value值是具体的数字,如a = 100; b = 20; c = 40
    virtual int interpreter(map<string, int> &var) = 0;
};

// 变量解析器（终结符表达式）
class VarExpression : public Expression
{
public:
    VarExpression(string key);
    ~VarExpression() override;

public:
    // 从map中取出变量的值
    int interpreter(map<string, int> &var) override;

private:
    string _key;
};

// 抽象运算符号解析器
class SymbolExpression : public Expression
{
public:
    SymbolExpression(Expression *left, Expression *right);

public:
    Expression *getLeft();
    Expression *getRight();

protected:
    Expression *_left;
    Expression *_right;
};

// 加法解析器
class AddExpression : public SymbolExpression
{
public:
    AddExpression(Expression *left, Expression *right);
    ~AddExpression() override;

public:
    // 把左右两个表达式运算的结果加起来
    int interpreter(map<string, int> &var) override;
};

// 减法解析器
class SubExpression : public SymbolExpression
{
public:
    SubExpression(Expression *left, Expression *right);
    ~SubExpression() override;

public:
    // 把左右两个表达式运算的结果相减
    int interpreter(map<string, int> &var) override;
};

// 解析器封装类，这个类是根据迪米特法则进行封装，目的是让Client只与直接朋友打交道，相当于Facade
class Calculator
{
public:
    // 构造函数传参，并解析表达式，构建语法树
    Calculator(string expStr);
    ~Calculator();

public:
    // 开始运算
    int run(map<string, int> &var);

private:
    // 删除最终的生成的抽象树
    void deltree(Expression *);

private:
    Expression *_expression;
};

/*******************************************************************************************************************
**                         场景：开发一套机器人控制程序
**   机器人控制程序中包含一些简单的英文控制指令，每一个指令对应一个表达式(expression)，
** 该表达式可以是简单表达式也可以是复合表达式，每一个简单表达式由移动方向(direction)，
** 移动方式(action)和移动距离(distance)三部分组成，其中移动方向包括上(up)、下(down)、
** 左(left)、右(right)；移动方式包括移动(move)和快速移动(run)；移动距离为一个正整数。
** 两个表达式之间可以通过与(and)连接，形成复合(composite)表达式。
**   用户通过对图形化的设置界面进行操作可以创建一个机器人控制指令，机器人在收到指令
** 后将按照指令的设置进行移动，例如输入控制指令：up move 5，则“向上移动5个单位”；
** 输入控制指令：down  run 10 and left move 20，则“向下快速移动10个单位再向左移动20个单位”
**
**                             文法规则
** expression ::= direction action distance | composite    // 表达式
** composite ::= expression 'and' expression               // 复合表达式
** direction ::= 'up' | 'down' | 'left' | 'right'          // 移动方向
** action ::= 'move' | 'run'                               // 移动方式
** distance ::= an integer                                 // 移动距离
** 上述语言一共定义了五条文法规则，对应五个语言单位，这些语言单位可以分为两类，
** 终结符（也称为终结符表达式）：例如direction、action和distance，它们是语言的最小组成单位，不能再进行拆分；
** 非终结符（也称为非终结符表达式），例如expression和composite，它们都是一个完整的句子，包含一系列终结符或非终结符。
********************************************************************************************************************/

// 抽象解释器类
class AbstractExpression
{
public:
    virtual ~AbstractExpression() = default;

public:
    // 解释操作
    virtual string interpret() = 0;
};

// And解释器：非终结符表达式
class AndExpression : public AbstractExpression
{
public:
    AndExpression(AbstractExpression *_left, AbstractExpression *_right);

public:
    string interpret();
    AbstractExpression *getLeft();
    AbstractExpression *getRight();

private:
    AbstractExpression *_left;
    AbstractExpression *_right;
};

// 简单句子解释器：非终结符表达式
// 如：up move 5，表示“向上移动5个单位
class SentenceExpression : public AbstractExpression
{
public:
    SentenceExpression(AbstractExpression *_direction, AbstractExpression *_action, AbstractExpression *_distance);

public:
    string interpret();
    AbstractExpression *getDirection();
    AbstractExpression *getAction();
    AbstractExpression *getDistance();

private:
    AbstractExpression *_direction;
    AbstractExpression *_action;
    AbstractExpression *_distance;
};

//  方向解释器：终结符表达式
class DirectionExpression : public AbstractExpression
{
public:
    DirectionExpression(string direction);

public:
    string interpret();

private:
    string _direction;
};

// 动作解释器：(终结符表达式)
class ActionExpression : public AbstractExpression
{
public:
    ActionExpression(string action);

public:
    string interpret();

private:
    string _action;
};

//距离解释器：（终结符表达式）
class DistanceExpression : public AbstractExpression
{
public:
    DistanceExpression(string distance);

public:
    string interpret();

private:
    string _distance;
};

//指令处理类：工具类
class InstructionHandler
{
public:
    InstructionHandler();

public:
    void handle(string instruction);
    string output();

private:
    // 删除最终的生成的抽象树
    void delTree(AbstractExpression *);

private:
    AbstractExpression *_expression;
};

#endif // HINTERPRETER_H
