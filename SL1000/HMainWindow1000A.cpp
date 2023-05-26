#include "HMainWindow1000A_p.h"
#include "HBuilder1000A.h"
#include "HeData/IConfigManage.h"

HMainWindow1000A::HMainWindow1000A(QWidget *parent) :
    HAbstractMainWindow(*new HMainWindow1000APrivate, parent)
{
}

HMainWindow1000A::~HMainWindow1000A() = default;

void HMainWindow1000A::initImportExport()
{
    Q_D(HMainWindow1000A);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   IConfigManage::ContainSpec);
    d->importExport.insert(tr("2.电定标数据(&E)..."),     IConfigManage::ContainElec);
    d->importExport.insert(tr("3.光定标数据(&L)..."),     IConfigManage::ContainLuminous);
    d->importExport.insert(tr("4.色容差数据(&C)..."),     IConfigManage::ContainChromatism);
    d->importExport.insert(tr("5.分级数据(&G)..."),       IConfigManage::ContainGrade);
    d->importExport.insert(tr("6.调整数据(&A)..."),       IConfigManage::ContainAdjust);
}

void HMainWindow1000A::initBuilder()
{
    Q_D(HMainWindow1000A);
    d->builder = new HBuilder1000A(this);
    d->builder->buildAll();
}

void HMainWindow1000A::initWindow()
{
    HAbstractMainWindow::initWindow();
    setIconSize(QSize(60, 60));
}

