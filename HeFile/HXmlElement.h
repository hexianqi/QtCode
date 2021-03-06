/***************************************************************************************************
**      2018-06-19  HXmlElement 重新封装的XML元素类，目的是为了简化XML查询操作。
***************************************************************************************************/

#ifndef HXMLELEMENT_H
#define HXMLELEMENT_H

#include "HFileGlobal.h"
#include <QtCore/QScopedPointer>
#include <functional>

class QDomElement;

HE_FILE_BEGIN_NAMESPACE

class HXmlElementPrivate;

class HE_FILE_EXPORT HXmlElement
{
public:
    // 装载XML文档
    static HXmlElement *load(QString fileName);
    // 解析XML文档
    static HXmlElement *parse(QString fileName, QDomElement *domElement, HXmlElement *parent);

public:
    // 元素名称
    QString name();
    // 父节点
    HXmlElement *parent();
    // 子节点
    QList<HXmlElement*> childs();
    void setChild(QList<HXmlElement*> value);
    // 属性
    QString attribute(QString name);
    void setAttribute(QString name, QString value);

public:
    // 保存到文件
    bool save();
    bool save(QString fileName);
    // 添加节点
    HXmlElement *createChild(QString name);
    // 移除子节点
    void removeChild(HXmlElement *xe);
    // 遍历所有元素 查找符合条件的首个元素
    HXmlElement *findElement(std::function<bool(HXmlElement *)> func);
    // 遍历所有元素 查找符合条件的所有元素
    QList<HXmlElement *> findElementAll(std::function<bool(HXmlElement *)> func);
    // 遍历所有元素 执行
    void forEach(std::function<void(HXmlElement *)> func);

protected:
    HXmlElement(QString fileName, QDomElement *domElement, HXmlElement *parent);
    HXmlElement(HXmlElementPrivate &);

private:
    QScopedPointer<HXmlElementPrivate> d_ptr;
};

HE_FILE_END_NAMESPACE

#endif // HXMLELEMENT_H
