/***************************************************************************************************
**      2019-05-09  ISqlBrowser 数据库浏览器接口。
***************************************************************************************************/

#ifndef ISQLBROWSER_H
#define ISQLBROWSER_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtWidgets/QWidget>

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlBrowser : public QWidget, public IInitializeable
{
    Q_OBJECT

public:
    using QWidget::QWidget;
};

HE_SQL_END_NAMESPACE



#endif // ISQLBROWSER_H
