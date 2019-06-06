/***************************************************************************************************
**      2019-05-29  TransparentComponent 透明组合模式
**                  SafeComponent 安全组合模式
**                  https://blog.csdn.net/liang19890820/article/details/71240662
***************************************************************************************************/

#ifndef HCOMPOSITE_H
#define HCOMPOSITE_H

#include <string>
#include <vector>

using namespace std;

class TransparentComponent
{
public:
    TransparentComponent(string name);
    virtual ~TransparentComponent() = default;

public:
    // 添加构件
    virtual void add(TransparentComponent *) = 0;
    // 删除构件
    virtual void remove(TransparentComponent *) = 0;
    // 获取构件
    virtual TransparentComponent *getChild(int index) = 0;
    // 显示构件（以缩进的方式）
    virtual void operation(int indent) = 0;

private:
    TransparentComponent() = default;

protected:
    string _name;
};

class TransparentLeaf : public TransparentComponent
{
public:
    TransparentLeaf(string name);

public:
    void add(TransparentComponent *) override;
    void remove(TransparentComponent *) override;
    TransparentComponent *getChild(int index) override;
    void operation(int indent) override;

private:
    TransparentLeaf() = default;;
};

class TransparentComposite : public TransparentComponent
{
public:
    TransparentComposite(string name);
    ~TransparentComposite() override;

public:
    void add(TransparentComponent *) override;
    void remove(TransparentComponent *) override;
    TransparentComponent *getChild(int index) override;
    void operation(int indent) override;

private:
    TransparentComposite() = default;

private:
    vector<TransparentComponent *> _elements;
};

class SafeComponent
{
public:
    SafeComponent(string name);
    virtual ~SafeComponent() = default;

public:
    // 显示构件（以缩进的方式）
    virtual void operation(int indent) = 0;

private:
    SafeComponent() = default;

protected:
    string _name;
};

class SafeLeaf : public SafeComponent
{
public:
    SafeLeaf(string name);

public:
    void operation(int indent) override;

private:
    SafeLeaf() = default;
};

class SafeComposite : public SafeComponent
{
public:
    SafeComposite(string name);
    ~SafeComposite() override;

public:
    void add(SafeComponent *);
    void remove(SafeComponent *);
    SafeComponent *getChild(int index);
    void operation(int indent) override;

private:
    SafeComposite() = default;

private:
    vector<SafeComponent *> _elements;
};

#endif // HCOMPOSITE_H
