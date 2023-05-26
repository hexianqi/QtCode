#include "HMainWindow2100DC_p.h"
#include "HBuilder2100DC.h"
#include "HeData/IConfigManage.h"

HMainWindow2100DC::HMainWindow2100DC(QWidget *parent) :
    HAbstractMainWindow(*new HMainWindow2100DCPrivate, parent)
{
}

HMainWindow2100DC::~HMainWindow2100DC() = default;

void HMainWindow2100DC::initImportExport()
{
    Q_D(HMainWindow2100DC);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   IConfigManage::ContainSpec);
    d->importExport.insert(tr("2.分级数据(&G)..."),       IConfigManage::ContainGrade);
    d->importExport.insert(tr("3.调整数据(&A)..."),       IConfigManage::ContainAdjust);
    d->importExport.insert(tr("4.色容差数据(&C)..."),     IConfigManage::ContainChromatism);
}

void HMainWindow2100DC::initBuilder()
{
    Q_D(HMainWindow2100DC);
    d->builder = new HBuilder2100DC(this);
    d->builder->buildAll();
}


