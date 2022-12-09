#include "HMainWindow1000RGB_p.h"
#include "HBuilder1000RGB.h"
#include "HeData/IConfigManage.h"

HMainWindow1000RGB::HMainWindow1000RGB(QWidget *parent, const HConstructionCallHelper &helper) :
    HAbstractMainWindow(*new HMainWindow1000RGBPrivate(this), helper, parent)
{
}

HMainWindow1000RGB::~HMainWindow1000RGB() = default;

void HMainWindow1000RGB::initImportExport()
{
    Q_D(HMainWindow1000RGB);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   IConfigManage::ContainSpec);
    d->importExport.insert(tr("2.电定标数据(&E)..."),     IConfigManage::ContainElec);
    d->importExport.insert(tr("3.光定标数据(&L)..."),     IConfigManage::ContainLuminous);
//    d->importExport.insert(tr("4.色容差数据(&C)..."),     IConfigManage::ContainChromatism);
//    d->importExport.insert(tr("5.分级数据(&G)..."),       IConfigManage::ContainGrade);
//    d->importExport.insert(tr("6.调整数据(&A)..."),       IConfigManage::ContainAdjust);
}

void HMainWindow1000RGB::initBuilder()
{
    Q_D(HMainWindow1000RGB);
    d->builder = new HBuilder1000RGB(this);
    d->builder->buildAll();
}
