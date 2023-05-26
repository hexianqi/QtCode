#include "HMainWindowSpec_p.h"
#include "HBuilderSpec.h"
#include "HeData/IConfigManage.h"

HMainWindowSpec::HMainWindowSpec(QWidget *parent) :
    HAbstractMainWindow(*new HMainWindowSpecPrivate, parent)
{
}

HMainWindowSpec::~HMainWindowSpec() = default;

void HMainWindowSpec::initImportExport()
{
    Q_D(HMainWindowSpec);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),           IConfigManage::ContainSpec);
}

void HMainWindowSpec::initBuilder()
{
    Q_D(HMainWindowSpec);
    d->builder = new HBuilderSpec(this);
    d->builder->buildAll();
}
