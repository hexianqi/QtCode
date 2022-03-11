#include "HImageSwitch_p.h"
#include <QtGui/QPainter>


HE_BEGIN_NAMESPACE

HImageSwitch::HImageSwitch(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HImageSwitchPrivate)
{
    setButtonStyle(ButtonStyle_2);
}

HImageSwitch::HImageSwitch(HImageSwitchPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    setButtonStyle(ButtonStyle_2);
}

HImageSwitch::~HImageSwitch() = default;


QSize HImageSwitch::sizeHint() const
{
    return {87, 28};
}

QSize HImageSwitch::minimumSizeHint() const
{
    return {87, 28};
}

bool HImageSwitch::isChecked() const
{
    return d_ptr->checked;
}

HImageSwitch::ButtonStyle HImageSwitch::buttonStyle() const
{
    return d_ptr->buttonStyle;
}

void HImageSwitch::setChecked(bool b)
{
    if (d_ptr->checked == b)
        return;
    d_ptr->checked = b;
    d_ptr->imageName = d_ptr->checked ? d_ptr->imageNameOn : d_ptr->imageNameOff;
    update();
}

void HImageSwitch::setButtonStyle(HImageSwitch::ButtonStyle value)
{
    if (d_ptr->buttonStyle == value)
        return;
    d_ptr->buttonStyle = value;
    if (d_ptr->buttonStyle == ButtonStyle_1)
    {
        d_ptr->imageNameOff = ":/fyqy/imageswitch/check_off_1.png";
        d_ptr->imageNameOn = ":/fyqy/imageswitch/check_on_1.png";
        resize(87, 28);
    }
    else if (d_ptr->buttonStyle == ButtonStyle_2)
    {
        d_ptr->imageNameOff = ":/fyqy/imageswitch/check_off_2.png";
        d_ptr->imageNameOn = ":/fyqy/imageswitch/check_on_2.png";
        resize(87, 28);
    }
    else if (d_ptr->buttonStyle == ButtonStyle_3)
    {
        d_ptr->imageNameOff = ":/fyqy/imageswitch/check_off_3.png";
        d_ptr->imageNameOn = ":/fyqy/imageswitch/check_on_3.png";
        resize(96, 38);
    }
    d_ptr->imageName = d_ptr->checked ? d_ptr->imageNameOn : d_ptr->imageNameOff;
    update();
    updateGeometry();
}

void HImageSwitch::mousePressEvent(QMouseEvent *)
{
    setChecked(!d_ptr->checked);
    emit clicked();
}

void HImageSwitch::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);

    QPixmap pm(d_ptr->imageName);
    if (pm.isNull())
        return;

    pm = pm.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    int x = rect().center().x() - pm.width() / 2;
    int y = rect().center().y() - pm.height() / 2;
    painter.drawPixmap(x, y, pm);
}

HE_END_NAMESPACE
