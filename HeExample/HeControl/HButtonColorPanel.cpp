#include "HButtonColorPanel_p.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

HE_CONTROL_BEGIN_NAMESPACE

HButtonColorPanel::HButtonColorPanel(QWidget *parent) :
    HAbstractColorPanel(*new HButtonColorPanelPrivate, parent)
{
    init();
}

HButtonColorPanel::HButtonColorPanel(HButtonColorPanelPrivate &p, QWidget *parent) :
    HAbstractColorPanel(p, parent)
{
    init();
}

HButtonColorPanel::~HButtonColorPanel()
{
}

QSize HButtonColorPanel::sizeHint() const
{
    return QSize(400, 300);
}

QSize HButtonColorPanel::minimumSizeHint() const
{
    return QSize(40, 30);
}

int HButtonColorPanel::space() const
{
    Q_D(const HButtonColorPanel);
    return d->gridLayout->spacing();
}

int HButtonColorPanel::columnCount() const
{
    Q_D(const HButtonColorPanel);
    return d->columnCount;
}

int HButtonColorPanel::borderRadius() const
{
    Q_D(const HButtonColorPanel);
    return d->borderRadius;
}

int HButtonColorPanel::borderWidth() const
{
    Q_D(const HButtonColorPanel);
    return d->borderWidth;
}

QColor HButtonColorPanel::borderColor() const
{
    Q_D(const HButtonColorPanel);
    return d->borderColor;
}

QStringList HButtonColorPanel::colors() const
{
    Q_D(const HButtonColorPanel);
    return d->colors;
}

void HButtonColorPanel::setSpace(int value)
{
    Q_D(HButtonColorPanel);
    if (d->gridLayout->spacing() == value)
        return;
    d->gridLayout->setSpacing(value);
}

void HButtonColorPanel::setColumnCount(int value)
{
    Q_D(HButtonColorPanel);
    if (d->columnCount == value)
        return;
    d->columnCount = value;
    initButton();
}

void HButtonColorPanel::setBorderRadius(int value)
{
    Q_D(HButtonColorPanel);
    if (d->borderRadius == value)
        return;
    d->borderRadius = value;
    initStyle();
}

void HButtonColorPanel::setBorderWidth(int value)
{
    Q_D(HButtonColorPanel);
    if (d->borderWidth == value)
        return;
    d->borderWidth = value;
    initStyle();
}

void HButtonColorPanel::setBorderColor(const QColor &value)
{
    Q_D(HButtonColorPanel);
    if (d->borderColor == value)
        return;
    d->borderColor = value;
    initStyle();
}

void HButtonColorPanel::setColors(const QStringList &value)
{
    Q_D(HButtonColorPanel);
    if (d->colors == value)
        return;
    d->colors = value;
    initButton();
}

void HButtonColorPanel::init()
{
    Q_D(HButtonColorPanel);
    d->colors << "#FEFEFE" << "#EEEEEF" << "#DCDDDD" << "#C9CACA" << "#B6B6B7" << "#A1A1A1" << "#8B8B8C" << "#757475" << "#5F5D5D" << "#474443" << "#303030"
              << "#00A2E9" << "#009B4C" << "#FFF000" << "#E62129" << "#E40082" << "#B04B87" << "#F08519" << "#F4B3B3" << "#897870" << "#D2CDE6" << "#A79CCB"
              << "#758FC8" << "#7C6FB0" << "#9288B1" << "#566892" << "#5E5872" << "#7789A4" << "#008FD7" << "#A0D9F6" << "#B8CEDA" << "#98AAB4" << "#75838A"
              << "#50585D" << "#5B7877" << "#4B8D7F" << "#769C9B" << "#5BA997" << "#5FA776" << "#62C3D0" << "#56AAB7" << "#B9CCBC" << "#D5EAD8" << "#A6D4AE"
              << "#99A99C" << "#9AA780" << "#BCC774" << "#BBC99A" << "#ACCE22" << "#D9E483" << "#5F5C50" << "#8B8979" << "#B6B49E" << "#B6B281" << "#DED572"
              << "#FFF582" << "#FFF9B1" << "#FFFCDB" << "#B39B77" << "#D59961" << "#DAB96B" << "#EF8641" << "#F6AE45" << "#F5B06E" << "#FDD100" << "#FBD7A3"
              << "#89765B" << "#AC6249" << "#D0753B" << "#EF8762" << "#F5B193" << "#FADAC9" << "#AF8283" << "#CF7771" << "#FF696B" << "#CF788A" << "#E61D4C"
              << "#EF8781" << "#E95A6F" << "#D49D9E" << "#876474" << "#AC6484" << "#F4B5D0" << "#D49EB6" << "#B39FA8" << "#D8C0CB" << "#B3719D" << "#CA5599"
              << "#CD81B3" << "#B593B3" << "#D0A9CD" << "#745E73" << "#977B95" << "#A878B1" << "#A72185" << "#934787" << "#804E9A" << "#7B5882" << "#714588";
    d->gridLayout = new QGridLayout(this);
    d->gridLayout->setSpacing(2);
    d->gridLayout->setMargin(0);
    initButton();
    initStyle();
}

void HButtonColorPanel::initButton()
{
    Q_D(HButtonColorPanel);
    qDeleteAll(d->buttons);
    d->buttons.clear();

    for (int i = 0; i < d->colors.size(); i++)
    {
        auto w = new QPushButton;
        w->setObjectName("pushButton_" + d->colors.at(i));
        w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        w->setStyleSheet(QString("QPushButton { background:%1; }").arg(d->colors.at(i)));
        connect(w, &QPushButton::pressed, this, &HButtonColorPanel::handleButtonPressed);
        d->gridLayout->addWidget(w, i / d->columnCount, i % d->columnCount);
        d->buttons << w;
    }
}

void HButtonColorPanel::initStyle()
{
    Q_D(HButtonColorPanel);
    QStringList qss;
    qss << QString("QPushButton { border:none; border-radius:%1px;}").arg(d->borderRadius)
        << QString("QPushButton:hover { border:%1px solid %2; }").arg(d->borderWidth).arg(d->borderColor.name());
    setStyleSheet(qss.join("\n"));
}

void HButtonColorPanel::handleButtonPressed()
{
    setCurrentColor(QColor(sender()->objectName().right(7)));
}

HE_CONTROL_END_NAMESPACE
