#include "HMainWindow2000_p.h"
#include "HBuilder2000.h"
#include "HeData/IConfigManage.h"
#include <QtCore/QDebug>

HE_DATA_USE_NAMESPACE

HMainWindow2000::HMainWindow2000(QWidget *parent, const HCallorHelper &helper) :
    HAbstractMainWindow(*new HMainWindow2000Private(this), helper, parent)
{
}

HMainWindow2000::~HMainWindow2000()
{
    qDebug() << __func__;
}

void HMainWindow2000::initImportExport()
{
    Q_D(HMainWindow2000);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   ConfigContainType::CCT_Spec);
    d->importExport.insert(tr("2.分级数据(&G)..."),       ConfigContainType::CCT_Grade);
}

void HMainWindow2000::initBuilder()
{
    Q_D(HMainWindow2000);
    d->builder = new HBuilder2000(this);
    d->builder->buildAll();
}
