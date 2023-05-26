#include "HMainWindow7000_p.h"
#include "HBuilder7000.h"
#include "HeData/IConfigManage.h"

HMainWindow7000::HMainWindow7000(QWidget *parent) :
    HAbstractMainWindow(*new HMainWindow7000Private, parent)
{
}

HMainWindow7000::~HMainWindow7000() = default;

void HMainWindow7000::initImportExport()
{
    Q_D(HMainWindow7000);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   IConfigManage::ContainSpec);
    d->importExport.insert(tr("2.电定标数据(&E)..."),     IConfigManage::ContainElec);
    d->importExport.insert(tr("3.光定标数据(&L)..."),     IConfigManage::ContainLuminous);
    d->importExport.insert(tr("4.色容差数据(&C)..."),     IConfigManage::ContainChromatism);
    d->importExport.insert(tr("5.分级数据(&G)..."),       IConfigManage::ContainGrade);
    d->importExport.insert(tr("6.调整数据(&A)..."),       IConfigManage::ContainAdjust);
    d->importExport.insert(tr("7.布局数据(&O)..."),       IConfigManage::ContainLocation);
}

void HMainWindow7000::initBuilder()
{
    Q_D(HMainWindow7000);
    d->builder = new HBuilder7000(this);
    d->builder->buildAll();
}

void HMainWindow7000::initWindow()
{
    HAbstractMainWindow::initWindow();
    setIconSize(QSize(60, 60));
}

