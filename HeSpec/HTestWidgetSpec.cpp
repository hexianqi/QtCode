#include "HTestWidgetSpec_p.h"
#include "ui_HTestWidgetSpec.h"

HTestWidgetSpec::HTestWidgetSpec(QWidget *parent) :
    HAbstractTestWidget(*new HTestWidgetSpecPrivate, parent),
    ui(new Ui::HTestWidgetSpec)
{
    ui->setupUi(this);
}

HTestWidgetSpec::~HTestWidgetSpec()
{
    delete ui;
}

QString HTestWidgetSpec::typeName()
{
    return "HTestWidgetSpec";
}

void HTestWidgetSpec::actionDone(HActionType action)
{

}
