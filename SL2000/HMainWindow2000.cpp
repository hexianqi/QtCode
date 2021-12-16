#include "HMainWindow2000_p.h"
#include "HBuilder2000.h"
#include "HeData/IConfigManage.h"

HMainWindow2000::HMainWindow2000(QWidget *parent, const HConstructionCallHelper &helper) :
    HAbstractMainWindow(*new HMainWindow2000Private(this), helper, parent)
{
}

HMainWindow2000::~HMainWindow2000() = default;

void HMainWindow2000::initImportExport()
{
    Q_D(HMainWindow2000);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   IConfigManage::ContainSpec);
    d->importExport.insert(tr("2.分级数据(&G)..."),       IConfigManage::ContainGrade);
    d->importExport.insert(tr("3.调整数据(&A)..."),       IConfigManage::ContainAdjust);
    d->importExport.insert(tr("4.色容差数据(&C)..."),     IConfigManage::ContainChromatism);
}

void HMainWindow2000::initBuilder()
{
    Q_D(HMainWindow2000);
    d->builder = new HBuilder2000(this);
    d->builder->buildAll();
}
