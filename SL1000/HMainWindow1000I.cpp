#include "HMainWindow1000I_p.h"
#include "HBuilder1000I.h"
#include "HeData/IConfigManage.h"

HMainWindow1000I::HMainWindow1000I(QWidget *parent, const HConstructionCallHelper &helper) :
    HAbstractMainWindow(*new HMainWindow1000IPrivate(this), helper, parent)
{
}

HMainWindow1000I::~HMainWindow1000I() = default;

void HMainWindow1000I::initImportExport()
{
    Q_D(HMainWindow1000I);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   IConfigManage::ContainSpec);
    d->importExport.insert(tr("2.电定标数据(&E)..."),     IConfigManage::ContainElec);
    d->importExport.insert(tr("3.光定标数据(&L)..."),     IConfigManage::ContainLuminous);
    d->importExport.insert(tr("4.分级数据(&G)..."),       IConfigManage::ContainGrade);
    d->importExport.insert(tr("5.调整数据(&A)..."),       IConfigManage::ContainAdjust);
}

void HMainWindow1000I::initBuilder()
{
    Q_D(HMainWindow1000I);
    d->builder = new HBuilder1000I(this);
    d->builder->buildAll();
}



