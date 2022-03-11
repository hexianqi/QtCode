#include "HIconFontHelper_p.h"
#include "HDrawHelper.h"
#include "HIconFontFactory.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QPixmap>
#include <QtGui/QPen>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

HE_BEGIN_NAMESPACE

HIconFontHelper::HIconFontHelper(QObject *parent) :
    QObject(parent),
    d_ptr(new HIconFontHelperPrivate)
{
    init();
}

HIconFontHelper::~HIconFontHelper() = default;

HIconFontHelper::StyleColor::StyleColor()
{
    position = "left";
    defaultBorder = false;

    iconPixelSize = 12;
    iconImageSize = QSize(15, 15);

    borderWidth = 3;
    borderColor = "#029FEA";

    normalBackground = "#292F38";
    normalTextColor = "#54626F";
    hoverBackground = "#40444D";
    hoverTextColor = "#FDFDFD";
    pressedBackground = "#404244";
    pressedTextColor = "#FDFDFD";
    checkedBackground = "#44494F";
    checkedTextColor = "#FDFDFD";
}

void HIconFontHelper::StyleColor::setColor(const QString &normalBackground, const QString &normalTextColor, const QString &darkBackground, const QString &darkTextColor)
{
    this->normalBackground = normalBackground;
    this->normalTextColor = normalTextColor;
    this->hoverBackground = darkBackground;
    this->hoverTextColor = darkTextColor;
    this->pressedBackground = darkBackground;
    this->pressedTextColor = darkTextColor;
    this->checkedBackground = darkBackground;
    this->checkedTextColor = darkTextColor;
}

QFont HIconFontHelper::getFont()
{
    return d_ptr->font;
}

QPixmap HIconFontHelper::getPixmap(const QColor &color, QChar icon, quint32 fontSize, QSize imageSize, int flags)
{
    QPen pen(color);
    d_ptr->font.setPixelSize(fontSize);
    return QPixmap::fromImage(HDrawHelper::createFontImage(d_ptr->font, icon, imageSize, pen, flags));
}

void HIconFontHelper::setFamilie(const QString &value)
{
    if (d_ptr->family == value || !d_ptr->factory->families().contains(value))
        return;
    d_ptr->family = value;
    d_ptr->font = d_ptr->factory->createFont(value);
}

void HIconFontHelper::setIcon(QLabel *label, QChar icon, quint32 size)
{
    d_ptr->font.setPixelSize(size);
    label->setFont(d_ptr->font);
    label->setText(icon);
}

void HIconFontHelper::setIcon(QAbstractButton *btn, QChar icon, quint32 size)
{
    d_ptr->font.setPixelSize(size);
    btn->setFont(d_ptr->font);
    btn->setText(icon);
}

void HIconFontHelper::setPixmap(QAbstractButton *btn, const QColor &color, QChar icon, quint32 fontSize, QSize imageSize, int flags)
{
    btn->setIcon(getPixmap(color, icon, fontSize, imageSize, flags));
}

void HIconFontHelper::setStyle(QWidget *widget, QList<QAbstractButton *> btns, QList<QChar> icons, const HIconFontHelper::StyleColor &styleColor)
{
    if (btns.count() <= 0 || icons.count() <= 0 || btns.count() != icons.count())
        return;

    int i,j;
    auto position = styleColor.position;
    auto iconPixelSize = styleColor.iconPixelSize;
    auto iconImageSize = styleColor.iconImageSize;
    auto borderWidth = styleColor.borderWidth;

    // 根据不同的位置计算边框
    QString border;
    if (position == "top")
        border = QString("border-width:%1px 0px 0px 0px; padding-top:%1px; padding-bottom:%2px;").arg(borderWidth).arg(borderWidth * 2);
    else if (position == "bottom")
        border = QString("border-width:0px 0px %1px 0px; padding-bottom:%1px; padding-top:%2px;").arg(borderWidth).arg(borderWidth * 2);
    else if (position == "left")
        border = QString("border-width:0px 0px 0px %1px; padding-left:%1px; padding-right:%2px;").arg(borderWidth).arg(borderWidth * 2);
    else if (position == "right")
        border = QString("border-width:0px %1px 0px 0px; padding-right:%1px; padding-left:%2px;").arg(borderWidth).arg(borderWidth * 2);

    // 如果图标是左侧显示则需要让没有选中的按钮左侧也有加深的边框,颜色为背景颜色
    // 如果图标在文字上面而设置的边框是 top bottom 也需要启用加深边框
    QStringList qss;
    if (styleColor.defaultBorder)
        qss << QString("QWidget[flag=\"%1\"] QAbstractButton { border-style:solid; border-radius:0px; %2 border-color:%3; color:%4; background:%5; }")
                   .arg(position).arg(border).arg(styleColor.normalBackground).arg(styleColor.normalTextColor).arg(styleColor.normalBackground);
    else
        qss << QString("QWidget[flag=\"%1\"] QAbstractButton { border-style:none; border-radius:0px; padding:5px; color:%2; background:%3; }")
                   .arg(position).arg(styleColor.normalTextColor).arg(styleColor.normalBackground);

    // 悬停+按下+选中
    qss << QString("QWidget[flag=\"%1\"] QAbstractButton:hover { border-style:solid; %2 border-color:%3; color:%4; background:%5; }")
               .arg(position).arg(border).arg(styleColor.borderColor).arg(styleColor.hoverTextColor).arg(styleColor.hoverBackground);
    qss << QString("QWidget[flag=\"%1\"] QAbstractButton:pressed { border-style:solid; %2 border-color:%3; color:%4; background:%5; }")
               .arg(position).arg(border).arg(styleColor.borderColor).arg(styleColor.pressedTextColor).arg(styleColor.pressedBackground);
    qss << QString("QWidget[flag=\"%1\"] QAbstractButton:checked { border-style:solid; %2 border-color:%3; color:%4; background:%5; }")
               .arg(position).arg(border).arg(styleColor.borderColor).arg(styleColor.checkedTextColor).arg(styleColor.checkedBackground);

    // 窗体背景颜色+按钮背景颜色
    qss << QString("QWidget#%1 { background:%2; }")
               .arg(widget->objectName()).arg(styleColor.normalBackground);
    qss << QString("QWidget>QAbstractButton { border-width:0px; background-color:%1; color:%2; }")
               .arg(styleColor.normalBackground).arg(styleColor.normalTextColor);
    qss << QString("QWidget>QAbstractButton:hover { background-color:%1; color:%2; }")
               .arg(styleColor.hoverBackground).arg(styleColor.hoverTextColor);
    qss << QString("QWidget>QAbstractButton:pressed { background-color:%1; color:%2; }")
               .arg(styleColor.pressedBackground).arg(styleColor.pressedTextColor);
    qss << QString("QWidget>QAbstractButton:checked { background-color:%1; color:%2; }")
               .arg(styleColor.checkedBackground).arg(styleColor.checkedTextColor);

    // 设置样式表
    widget->setStyleSheet(qss.join(""));

    //可能会重复调用设置所以先要移除上一次的
    for (i = 0; i < btns.count(); i++)
    {
        for (j = 0; j < d_ptr->btns.count(); j++)
        {
            if (d_ptr->btns.at(j) == btns.at(i))
            {
                disconnect(btns.at(i), &QAbstractButton::toggled, this, &HIconFontHelper::toggled);
                d_ptr->btns.at(j)->removeEventFilter(this);
                d_ptr->btns.removeAt(j);
                d_ptr->pixNormal.removeAt(j);
                d_ptr->pixHover.removeAt(j);
                d_ptr->pixPressed.removeAt(j);
                d_ptr->pixChecked.removeAt(j);
                break;
            }
        }
    }

    // 存储对应按钮对象,方便鼠标移上去的时候切换图片
    int checkedIndex = -1;
    for (i = 0; i < btns.count(); i++)
    {
        auto icon = icons.at(i);
        auto pixNormal = getPixmap(styleColor.normalTextColor, icon, iconPixelSize, iconImageSize);
        auto pixHover = getPixmap(styleColor.hoverTextColor, icon, iconPixelSize, iconImageSize);
        auto pixPressed = getPixmap(styleColor.pressedTextColor, icon, iconPixelSize, iconImageSize);
        auto pixChecked = getPixmap(styleColor.checkedTextColor, icon, iconPixelSize, iconImageSize);

        // 记住最后选中的按钮
        auto btn = btns.at(i);
        if (btn->isChecked())
            checkedIndex = i;

        btn->setIcon(pixNormal);
        btn->setIconSize(iconImageSize);
        btn->installEventFilter(this);
        connect(btn, &QAbstractButton::toggled, this, &HIconFontHelper::toggled);

        d_ptr->btns << btn;
        d_ptr->pixNormal << pixNormal;
        d_ptr->pixHover << pixHover;
        d_ptr->pixPressed << pixPressed;
        d_ptr->pixChecked << pixChecked;
    }

    // 主动触发一下选中的按钮
    if (checkedIndex >= 0)
        QMetaObject::invokeMethod(btns.at(checkedIndex), "toggled", Q_ARG(bool, true));
}

void HIconFontHelper::init()
{
    d_ptr->factory = new HIconFontFactory(this);
    setFamilie("FontAwesome");
}

void HIconFontHelper::toggled(bool checked)
{
    // 选中和不选中设置不同的图标
    auto btn = qobject_cast<QAbstractButton *>(sender());
    auto index = d_ptr->btns.indexOf(btn);
    btn->setIcon(checked ? d_ptr->pixChecked.at(index) : d_ptr->pixNormal.at(index));
}

bool HIconFontHelper::eventFilter(QObject *watched, QEvent *event)
{
    if (watched->inherits("QAbstractButton"))
    {
        auto btn = qobject_cast<QAbstractButton *>(watched);
        auto index = d_ptr->btns.indexOf(btn);
        auto checked = btn->isChecked();
        if (index >= 0)
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
                if (mouseEvent->button() == Qt::LeftButton)
                    btn->setIcon(checked ? d_ptr->pixChecked.at(index) : d_ptr->pixPressed.at(index));
            }
            else if (event->type() == QEvent::Enter)
                btn->setIcon(checked ? d_ptr->pixChecked.at(index) : d_ptr->pixHover.at(index));
            else if (event->type() == QEvent::Leave)
                btn->setIcon(checked ? d_ptr->pixChecked.at(index) : d_ptr->pixNormal.at(index));
        }
    }
    return QObject::eventFilter(watched, event);
}

HE_END_NAMESPACE


