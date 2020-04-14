#include "HComposite.h"
#include "HDesignPattern.h"
#include <iostream>

TransparentComponent::TransparentComponent(string name)
{
    _name  = name;
}

TransparentLeaf::TransparentLeaf(string name):
    TransparentComponent(name)
{

}

void TransparentLeaf::add(TransparentComponent *)
{
    cout << "Can't add to a Leaf" << endl;
}

void TransparentLeaf::remove(TransparentComponent *)
{
    cout << "Can't remove from a Leaf" << endl;
}

TransparentComponent *TransparentLeaf::getChild(int /*index*/)
{
    cout << "Can't get child from a Leaf" << endl;
    return nullptr;
}

void TransparentLeaf::operation(int indent)
{
    string str(indent, '-');
    cout << str << " " << _name <<endl;
}

TransparentComposite::TransparentComposite(string name) :
    TransparentComponent(name)
{

}

TransparentComposite::~TransparentComposite()
{
    while (!_elements.empty())
    {
        auto it = _elements.begin();
        SAFE_DELETE(*it);
        _elements.erase(it);
    }
}

void TransparentComposite::add(TransparentComponent *p)
{
    _elements.push_back(p);
}

void TransparentComposite::remove(TransparentComponent *p)
{
    auto it = _elements.begin();
    while (it != _elements.end())
    {
        if (*it == p)
        {
            SAFE_DELETE(p);
            _elements.erase(it);
            break;
        }
        ++it;
    }
}

TransparentComponent *TransparentComposite::getChild(int index)
{
    if (index >= _elements.size())
        return nullptr;
    return _elements[index];
}

void TransparentComposite::operation(int indent)
{
    string str(indent, '-');
    cout << str << "+ " << _name << endl;
    // 显示每个节点的孩子
    for (auto it = _elements.begin(); it != _elements.end(); it++)
        (*it)->operation(indent + 2);
}

SafeComponent::SafeComponent(string name)
{
    _name = name;
}

SafeLeaf::SafeLeaf(string name) :
    SafeComponent(name)
{

}

void SafeLeaf::operation(int indent)
{
    string str(indent, '-');
    cout << str << " " << _name <<endl;
}

SafeComposite::SafeComposite(string name) :
    SafeComponent(name)
{

}

SafeComposite::~SafeComposite()
{
    while (!_elements.empty())
    {
        auto it = _elements.begin();
        SAFE_DELETE(*it);
        _elements.erase(it);
    }
}

void SafeComposite::add(SafeComponent *p)
{
    _elements.push_back(p);
}

void SafeComposite::remove(SafeComponent *p)
{
    auto it = _elements.begin();
    while (it != _elements.end())
    {
        if (*it == p)
        {
            SAFE_DELETE(p);
            _elements.erase(it);
            break;
        }
        ++it;
    }
}

SafeComponent *SafeComposite::getChild(int index)
{
    if (index >= _elements.size())
        return nullptr;
    return _elements[index];
}

void SafeComposite::operation(int indent)
{
    string str(indent, '-');
    cout << str << "+ " << _name << endl;
    // 显示每个节点的孩子
    for (auto it = _elements.begin(); it != _elements.end(); it++)
        (*it)->operation(indent + 2);
}
