#include "HMainWindow2000AC_p.h"
#include "HBuilder2000AC.h"
#include "HeData/IConfigManage.h"

HMainWindow2000AC::HMainWindow2000AC(QWidget *parent) :
    HAbstractMainWindow(*new HMainWindow2000ACPrivate, parent)
{
}

HMainWindow2000AC::~HMainWindow2000AC() = default;

void HMainWindow2000AC::initImportExport()
{
    Q_D(HMainWindow2000AC);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   IConfigManage::ContainSpec);
    d->importExport.insert(tr("2.色容差数据(&C)..."),     IConfigManage::ContainChromatism);
    d->importExport.insert(tr("3.分级数据(&G)..."),       IConfigManage::ContainGrade);
    d->importExport.insert(tr("4.调整数据(&A)..."),       IConfigManage::ContainAdjust);

}

void HMainWindow2000AC::initBuilder()
{
    Q_D(HMainWindow2000AC);
    d->builder = new HBuilder2000AC(this);
    d->builder->buildAll();
}
