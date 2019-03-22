#include "HAbstractBuilder_p.h"
#include <QWidget>
#include <QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractBuilder::HAbstractBuilder(QObject *parent)
    : QObject(parent), d_ptr(new HAbstractBuilderPrivate)
{

}

HAbstractBuilder::HAbstractBuilder(HAbstractBuilderPrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{

}

HAbstractBuilder::~HAbstractBuilder()
{
    qDebug() << __func__;
}

void HAbstractBuilder::initialize(QVariantMap /*param*/)
{
}

void HAbstractBuilder::buildAll()
{
    buildFactory();
    buildConfigManage();
    buildTestData();
    buildDevice();
    buildThread();
    buildModel();
    buildTestWidget();
}

HE_GUI_END_NAMESPACE
