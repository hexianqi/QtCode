#ifndef HXMLELEMENT_H
#define HXMLELEMENT_H

#include "HFileGlobal.h"
#include <QStringList>
#include <functional>

class QDomElement;

HE_FILE_BEGIN_NAMESPACE

// 重新封装的XML元素类，目的是为了简化XML查询操作
class HE_FILE_EXPORT HXmlElement
{
public:
    // 装载XML文档
    static HXmlElement *load(QString fileName);
    // 解析XML文档
    static HXmlElement *pares(QDomElement *domElement, HXmlElement *parent, QString fileName);

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
    HXmlElement *findElement(std::function<bool(HXmlElement*)> fun);
    // 遍历所有元素 查找符合条件的所有元素
    QList<HXmlElement*> findElementAll(std::function<bool(HXmlElement*)> fun);
    // 遍历所有元素 执行
    void forEach(std::function<void(HXmlElement*)> fun);

protected:
    HXmlElement(QDomElement *domElement, HXmlElement *parent, QString fileName);

protected:
    QString _fileName;
    QDomElement *_domElement;
    HXmlElement *_parent;
    QList<HXmlElement*> _childs;
};

HE_FILE_END_NAMESPACE

#endif // HXMLELEMENT_H
