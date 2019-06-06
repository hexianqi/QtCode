#include "HControlHelper.h"
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

void HControlHelper::centerWidget(QWidget *widget)
{
    auto size = QApplication::primaryScreen()->availableSize();
    widget->move((size.width() - widget->width()) / 2, (size.height() - widget->height()) / 2);
    widget->setFixedSize(widget->width(), widget->height());
}

HE_CONTROL_END_NAMESPACE
