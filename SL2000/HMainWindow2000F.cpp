#include "HMainWindow2000F_p.h"
#include "HBuilder2000F.h"
#include "HeData/IConfigManage.h"
#include <QtCore/QDebug>

HE_DATA_USE_NAMESPACE

HMainWindow2000F::HMainWindow2000F(QWidget *parent, const HCallorHelper &helper) :
    HAbstractMainWindow(*new HMainWindow2000FPrivate(this), helper, parent)
{
}

HMainWindow2000F::~HMainWindow2000F()
{
    qDebug() << __func__;
}

void HMainWindow2000F::initImportExport()
{
    Q_D(HMainWindow2000F);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),   IConfigManage::ContainSpec);
    d->importExport.insert(tr("2.电定标数据(&G)..."),     IConfigManage::ContainElec);
    d->importExport.insert(tr("3.光定标数据(&G)..."),     IConfigManage::ContainLuminous);
    d->importExport.insert(tr("4.色容差数据(&C)..."),     IConfigManage::ContainChromatism);
    d->importExport.insert(tr("5.分级数据(&G)..."),       IConfigManage::ContainGrade);
    d->importExport.insert(tr("6.调整数据(&A)..."),       IConfigManage::ContainAdjust2);
}

void HMainWindow2000F::initBuilder()
{
    Q_D(HMainWindow2000F);
    d->builder = new HBuilder2000F(this);
    d->builder->buildAll();
}

void HMainWindow2000F::initWindow()
{
    HAbstractMainWindow::initWindow();
    setIconSize(QSize(60, 60));
}
