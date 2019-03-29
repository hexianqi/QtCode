#include "HMainWindowSpec_p.h"
#include "HeData/IConfigManage.h"
#include "HBuilderSpec.h"

#include <QDebug>

HE_DATA_USE_NAMESPACE

HMainWindowSpecPrivate::HMainWindowSpecPrivate(HMainWindowSpec *q) :
    HMainWindowPrivate(q)
{
}

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
    HAbstractMainWindow::initImportExport();
    Q_D(HMainWindowSpec);
    d->importExport.insert(tr("1.光谱定标数据(&S)..."),           ConfigContainType::CCT_Spec);
}

void HMainWindowSpec::createBuilder()
{
    Q_D(HMainWindowSpec);
    d->builder = new HBuilderSpec(this);
    d->builder->buildAll();
}

