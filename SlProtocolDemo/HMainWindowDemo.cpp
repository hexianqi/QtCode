#include "HMainWindowDemo_p.h"
#include "HeData/IConfigManage.h"
#include "HBuilderDemo.h"
#include <QtCore/QDebug>

HE_DATA_USE_NAMESPACE

HMainWindowDemo::HMainWindowDemo(QWidget *parent, const HCallorHelper &helper) :
    HAbstractMainWindow(*new HMainWindowDemoPrivate(this), helper, parent)
{
}

HMainWindowDemo::~HMainWindowDemo()
{
    qDebug() << __func__;
}

void HMainWindowDemo::initImportExport()
{
    Q_D(HMainWindowDemo);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),           IConfigManage::ContainSpec);
}

void HMainWindowDemo::initBuilder()
{
    Q_D(HMainWindowDemo);
    d->builder = new HBuilderSpec(this);
    d->builder->buildAll();
}
