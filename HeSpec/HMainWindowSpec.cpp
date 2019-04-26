#include "HMainWindowSpec_p.h"
#include "HeData/IConfigManage.h"
#include "HBuilderSpec.h"
#include <QtCore/QDebug>

HE_DATA_USE_NAMESPACE

HMainWindowSpec::HMainWindowSpec(QWidget *parent, const HCallorHelper &helper)
    : HAbstractMainWindow(*new HMainWindowSpecPrivate(this), helper, parent)
{
}

HMainWindowSpec::~HMainWindowSpec()
{
    qDebug() << __func__;
}

void HMainWindowSpec::initImportExport()
{
    Q_D(HMainWindowSpec);
    HAbstractMainWindow::initImportExport();
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),           ConfigContainType::CCT_Spec);
}

void HMainWindowSpec::initBuilder()
{
    Q_D(HMainWindowSpec);
    d->builder = new HBuilderSpec(this);
    d->builder->buildAll();
}

