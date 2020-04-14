/***************************************************************************************************
**      2019-05-08  HOptionalTableExtend 表格视图扩展 - 显示可选。
***************************************************************************************************/

#ifndef HOPTIONALTABLEEXTEND_H
#define HOPTIONALTABLEEXTEND_H

#include "HAbstractTableExtend.h"

class HOptionalTableExtendPrivate;

class QDESIGNER_WIDGET_EXPORT HOptionalTableExtend : public HAbstractTableExtend
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HOptionalTableExtend)

public:
    explicit HOptionalTableExtend(QObject *parent = nullptr);

public:
    void setTableView(QTableView *) override;

public:
    void setDisplay(const QStringList &);
    void setOptional(const QStringList &);
    void setSelected(const QStringList &);

public:
    QStringList selected();

protected:
    void editSelected();
    void setColumnHidden();
};

#endif // HOPTIONALTABLEEXTEND_H
