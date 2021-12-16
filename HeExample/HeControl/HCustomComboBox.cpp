#include "HCustomComboBox_p.h"
#include <QtWidgets/QListView>

HE_BEGIN_NAMESPACE

HCustomComboBox::HCustomComboBox(QWidget *parent) :
    QComboBox(parent),
    d_ptr(new HCustomComboBoxPrivate)
{
    init();
}

HCustomComboBox::HCustomComboBox(HCustomComboBoxPrivate &p, QWidget *parent) :
    QComboBox(parent),
    d_ptr(&p)
{
    init();
}

HCustomComboBox::~HCustomComboBox() = default;

int HCustomComboBox::itemWidth() const
{
    return d_ptr->itemWidth;
}

int HCustomComboBox::itemHeight() const
{
    return d_ptr->itemHeight;
}

bool HCustomComboBox::isAutoWidth() const
{
    return d_ptr->autoWidth;
}

void HCustomComboBox::setItemWidth(int value)
{
    if (d_ptr->itemWidth == value)
        return;
    d_ptr->itemWidth = value;
    if (!d_ptr->autoWidth)
        view()->setFixedWidth(value);
}

void HCustomComboBox::setItemHeight(int value)
{
    if (d_ptr->itemHeight == value)
        return;
    d_ptr->itemHeight = value;
    setStyleSheet(QString("QComboBox QAbstractItemView::item { min-height:%1px; }").arg(value));
}

void HCustomComboBox::setAutoWidth(bool b)
{
    if (d_ptr->autoWidth == b)
        return;
    d_ptr->autoWidth = b;
}

void HCustomComboBox::showEvent(QShowEvent *)
{
    if (d_ptr->autoWidth)
    {
        auto fm = fontMetrics();
        for (int i = 0; i < count(); i++)
        {
            auto width = fm.width(itemText(i));
            if (width > d_ptr->itemWidth)
                d_ptr->itemWidth = width;
        }
        // 宽度增加像素,因为有边距
        view()->setFixedWidth(d_ptr->itemWidth + 20);
    }
}

void HCustomComboBox::init()
{
    setView(new QListView);
    setStyleSheet(QString("QComboBox QAbstractItemView::item { min-height:%1px; }").arg(d_ptr->itemHeight));
}

HE_END_NAMESPACE
