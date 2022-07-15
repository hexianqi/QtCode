#include "HStationWidget_p.h"
#include <QtGui/QIcon>

HStationWidget::HStationWidget(int index, QWidget *parent) :
    QWidget(parent),
    d_ptr(new HStationWidgetPrivate)
{
    initialize(index);
}

HStationWidget::~HStationWidget()
{
}

void HStationWidget::initialize(int index)
{
    d_ptr->index = index;
    setWindowIcon(QIcon(QString(":/image/%1-0.png").arg(index + 1)));
}


