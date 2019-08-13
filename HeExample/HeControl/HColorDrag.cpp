#include "HColorDrag.h"
#include <QtCore/QMimeData>
#include <QtWidgets/QStyle>
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

HColorDrag::HColorDrag(QWidget *source, const QColor &color, const QString &name) :
    QDrag(source)
{
    auto size = source->style()->pixelMetric(QStyle::PM_ButtonIconSize, nullptr, source);
    auto pm = QPixmap(QSize(size, size));
    pm.fill(color);
    setPixmap(pm);
    auto data = new QMimeData;
    data->setColorData(color);
    data->setText(name);
    data->setImageData(pm.toImage());
    setMimeData(data);
}

HE_CONTROL_END_NAMESPACE
