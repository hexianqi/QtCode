/***************************************************************************************************
**      2019-04-19  IItemDetailWidget 项详情窗体接口。
***************************************************************************************************/

#ifndef IDATADETAILWIDGET_H
#define IDATADETAILWIDGET_H

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IDataDetailWidget : public QWidget, public IInitializeable
{
    Q_OBJECT

public:
    using QWidget::QWidget;

signals:
    void sourceChanged(QStringList names, QString name);

public:
    // 启用
    virtual void start() = 0;
    // 导入文件
    virtual void importFile() = 0;
    // 导出文件
    virtual void exportFile() = 0;
    // 添加项
    virtual void addItem(QString name) = 0;
    // 删除项
    virtual void delItem(QString name) = 0;
    // 设置当前项
    virtual void setCurrentItem(QString name) = 0;
    // 保存数据
    virtual void saveData() = 0;
};

HE_GUI_END_NAMESPACE

#endif // IDATADETAILWIDGET_H
