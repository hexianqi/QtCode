#include "HInterpreter.h"
#include <iostream>
#include <stack>
#include <typeinfo>
#include <vector>

/***************************************************************************
 * 字符串分割
 * 函数     : Split
 * 功能     : 分割STL标准字符串
 * 返回值   : void
 * 参数     : Container<std::basic_string<CharT> >& v 存放分割结果
 * 参数     : const std::basic_string<CharT>& s 待分割字符串
 * 参数     : const std::basic_string<CharT>& c 分割字符串
*****************************************************************************/
// -------------------------------------------------------------------------
template<typename CharT, template<typename S, typename Q = allocator<S>> class Container>
void Split(Container<basic_string<CharT>> &v, const basic_string<CharT> &s, const basic_string<CharT> &c);

template<template<typename S, typename Q = allocator<S>> class Container>
void Split(Container<basic_string<char>> &v, const basic_string<char> &s, const basic_string<char> &c)
{
    if (0 == c.length())
        return;

    basic_string<char>::size_type pos1 = 0;
    basic_string<char>::size_type pos2 = s.find(c);
    while (basic_string<char>::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }

    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

VarExpression::VarExpression(string key)
{
    _key = key;
}

int VarExpression::interpreter(map<string, int> &var)
{
    return var[_key];
}

VarExpression::~VarExpression()
{
    cout << "~VarExpression()" << endl;
}

SymbolExpression::SymbolExpression(Expression *left, Expression *right)
{
    _left = left;
    _right = right;
}

Expression *SymbolExpression::getLeft()
{
    return _left;
}

Expression *SymbolExpression::getRight()
{
    return _right;
}

AddExpression::AddExpression(Expression *left, Expression *right) :
    SymbolExpression(left, right)
{
}

int AddExpression::interpreter(map<string, int> &var)
{
    return _left->interpreter(var) + _right ->interpreter(var);
}

AddExpression::~AddExpression()
{
    cout << "~AddExpression()" << endl;
}

SubExpression::SubExpression(Expression *left, Expression *right) :
    SymbolExpression(left, right)
{
}

int SubExpression::interpreter(map<string, int> &var)
{
    return _left->interpreter(var) - _right ->interpreter(var);
}

SubExpression::~SubExpression()
{
    cout << "~SubExpression()" << endl;
}

Calculator::Calculator(string expStr)
{
    _expression = nullptr;
    Expression *left  = nullptr;
    Expression *right = nullptr;
    stack<Expression *> stkExp; // 栈，用来暂存中间结果

    /**************************************************
     * 从左到向分析表达式（如:a+b-c)，最终的语法树如下：
     *            -
     *          /   \
     *         +     c
     *       /   \
     *      a     b
    ***************************************************/
    for(size_t i = 0; i < expStr.length(); i++)
    {
        switch(expStr[i])
        {
        case '+':  //加法
            // 1.先从栈中取出左操作数
            left = stkExp.top();
            stkExp.pop();
            // 2.从表达式中取出+号后面的右操作数，并生成终结符解析对象
            right = new VarExpression(expStr.substr(++i, 1));
            // 3.将左右操作数相加，并把结果放入栈中
            stkExp.push(new AddExpression(left, right));
            break;
        case '-':
            // 1.先从栈中取出左操作数
            left = stkExp.top();
            stkExp.pop();
            // 2.从表达式中取出-号后面的右操作数，并生成终结符解析对象
            right = new VarExpression(expStr.substr(++i, 1));
            //3.将左右操作数相减，并把结果放入栈中
            stkExp.push(new SubExpression(left, right));
            break;
        default:
            // 如果是变量（终结符）：如a+b+c中的a\b\c，
            // 则直接生成对应的变量解析器对象
            stkExp.push(new VarExpression(expStr.substr(i, 1)));
        }
    }
    //栈中保存的就是最终语法树的根结点（本例为SuuExpression对象）
    if (!stkExp.empty())
    {
        _expression = stkExp.top();
        stkExp.pop();
    }
}

Calculator::~Calculator()
{
    deltree(_expression);
    _expression = nullptr;
}

int Calculator::run(map<string, int> &var)
{
    return (_expression == nullptr) ? 0 : _expression->interpreter(var);
}

void Calculator::deltree(Expression *p)
{
    auto branch = dynamic_cast<SymbolExpression *>(p);
    // 分支结点
    if (branch != nullptr)
    {
        // 左子树
        deltree(branch->getLeft());
        // 右子树
        deltree(branch->getRight());
        // 结点
        delete p;
    }
    else // 叶子结点
        delete p;
}

AndExpression::AndExpression(AbstractExpression *left, AbstractExpression *right)
{
    _left  = left;
    _right = right;
}

string AndExpression::interpret()
{
    return _left->interpret() + "再" + _right->interpret();
}

AbstractExpression *AndExpression::getLeft()
{
    return _left;
}

AbstractExpression *AndExpression::getRight()
{
    return _right;
}

SentenceExpression::SentenceExpression(AbstractExpression *direction, AbstractExpression *action, AbstractExpression *distance)
{
    _direction = direction;
    _action = action;
    _distance = distance;
}

string SentenceExpression::interpret()
{
    return _direction->interpret() + _action->interpret() + _distance->interpret();
}

AbstractExpression *SentenceExpression::getDirection()
{
    return _direction;
}

AbstractExpression *SentenceExpression::getAction()
{
    return _action;
}

AbstractExpression *SentenceExpression::getDistance()
{
    return _distance;
}

DirectionExpression::DirectionExpression(string direction)
{
    _direction = direction;
}

string DirectionExpression::interpret()
{
    if (_direction =="up")
        return "向上";
    if (_direction == "down")
        return "向下";
    if (_direction == "left")
        return "向左";
    if (_direction == "right")
        return "向右";
    return "无效指令";
}

ActionExpression::ActionExpression(string action)
{
    _action = action;
}

string ActionExpression::interpret()
{
    if (_action == "move")
        return "移动";
    if (_action == "run")
        return "快速移动";
    return "无效指令";
}

DistanceExpression::DistanceExpression(string distance)
{
    _distance = distance;
}

string DistanceExpression::interpret()
{
    return _distance;
}

InstructionHandler::InstructionHandler() :
    _expression(nullptr)
{

}

void InstructionHandler::handle(string instruction)
{
//    AbstractExpression *left = nullptr;
//    AbstractExpression *right = nullptr;
//    AbstractExpression *direction = nullptr;
//    AbstractExpression *action = nullptr;
//    AbstractExpression *distance = nullptr;

    if (_expression != nullptr)
    {
        delTree(_expression);
        _expression = nullptr;
    }

    // 声明一个栈对象用于存储抽象语法树
    stack<AbstractExpression *> stkExp;
    vector<string> words;
    // 以空格分隔指令字符串
    Split(words, instruction, " ");

    for(size_t i = 0; i < words.size(); i++)
    {
        // 本实例采用栈的方式来处理指令，如果遇到and则将其后的三个单词连成一个简单句子（Sentence）
        // 作为"and"的右表达式，而将栈顶弹出的表达式作为"and"的左表达式，最后将新的And表达式压入栈中
        if (words[i] == "and")
        {
            //从弹出栈顶作为and的左表达式
            auto left = stkExp.top();
            stkExp.pop();
            auto direction = new DirectionExpression(words[++i]);
            auto action = new ActionExpression(words[++i]);
            auto distance = new DistanceExpression(words[++i]);
            // 组成一个简单表达式作为And的右表达式
            auto right = new SentenceExpression(direction, action, distance);
            // 生成And表达式，并压入栈中
            stkExp.push(new AndExpression(left, right));
        }
        // 如果不是and表达式，就从头开始进行解释，将前3个单词作为Sentence
        // 的三个操作数，生成简单表达式解析器后压入栈中
        else
        {
            auto direction = new DirectionExpression(words[i]);
            auto action = new ActionExpression(words[++i]);
            auto distance = new DistanceExpression(words[++i]);
            // 组成一个简单表达式作为And的右表达式
            stkExp.push(new SentenceExpression(direction, action, distance));
        }
    }

    if(!stkExp.empty())
    {
        _expression = stkExp.top();
        stkExp.pop();
    }
}

string InstructionHandler::output()
{
    return _expression == nullptr ? "" : _expression->interpret();
}

void InstructionHandler::delTree(AbstractExpression *p)
{
    auto andExp = dynamic_cast<AndExpression*>(p);
    auto sentenceExp = dynamic_cast<SentenceExpression*>(p);

    if (andExp != nullptr)  // And表达式
    {
        auto left = andExp->getLeft();
        auto right = andExp->getRight();
        delTree(left);
        delTree(right);
        delete andExp;
    }
    else if(sentenceExp != nullptr) // 简单句子表达式
    {
        auto dir = sentenceExp->getDirection();
        auto act = sentenceExp->getAction();
        auto dis = sentenceExp->getDistance();
        delTree(dir);
        delTree(act);
        delTree(dis);
        delete sentenceExp;
    }
    else if (typeid(*p) == typeid(DirectionExpression)
             || typeid(*p) == typeid(ActionExpression)
             || typeid(*p) == typeid(DistanceExpression)) // 叶子结果
     {
         delete p;
     }
}

