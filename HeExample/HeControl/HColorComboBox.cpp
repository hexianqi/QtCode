#include "HColorComboBox_p.h"
#include "HColorModel.h"
#include <QtCore/QMimeData>
#include <QtGui/QtEvents>
#include <QtWidgets/QStylePainter>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QColorDialog>

HE_CONTROL_BEGIN_NAMESPACE

HColorComboBox::HColorComboBox(QWidget *parent) :
    QComboBox(parent),
    d_ptr(new HColorComboBoxPrivate)
{
    init();
}

HColorComboBox::HColorComboBox(HColorComboBoxPrivate &p, QWidget *parent) :
    QComboBox(parent),
    d_ptr(&p)
{
    init();
}

HColorComboBox::~HColorComboBox() = default;

QStringList HColorComboBox::colors() const
{
    return d_ptr->model->colors();
}

QColor HColorComboBox::currentColor() const
{
    return color(currentIndex());
}

QColor HColorComboBox::color(int index) const
{
    return itemData(index, Qt::DecorationRole).value<QColor>();
}

bool HColorComboBox::isColorDialogEnabled() const
{
    return d_ptr->colorDialogEnabled;
}

int HColorComboBox::colorCount() const
{
    return d_ptr->model->rowCount();
}

void HColorComboBox::setColors(const QStringList &value)
{
    d_ptr->model->setColors(value);
    handleActivated(0);
    update();
}

void HColorComboBox::setCurrentColor(const QColor &value)
{
    int index = findData(value, Qt::DecorationRole);
    if (index != -1)
    {
        setCurrentIndex(index);
    }
    else
    {
        addColor(value, tr("自定义颜色"));
        setCurrentIndex(count() - 1);
    }
}

void HColorComboBox::setColorDialogEnabled(bool b)
{
    d_ptr->colorDialogEnabled = b;
}

void HColorComboBox::setStandardColors()
{
    d_ptr->model->setStandardColors();
}

void HColorComboBox::addColor(const QColor &color, const QString &name)
{
    d_ptr->model->addColor(color, name);
}

void HColorComboBox::insertColor(int index, const QColor &color, const QString &name)
{
    d_ptr->model->insertColor(index, color, name);
}

bool HColorComboBox::eventFilter(QObject *object, QEvent *event)
{
    if (object == view())
    {
        if (event->type() == QEvent::Show)
        {
            if (isColorDialogEnabled())
            {
                addItem(tr("其他"));
                int index = count() - 1;
                setItemData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
                setItemData(index, palette().color(QPalette::Button), Qt::BackgroundRole);
                setItemData(index, tr("自定义颜色"), Qt::ToolTipRole);
            }
            return false;
        }
        if (event->type() == QEvent::Hide)
        {
            if (isColorDialogEnabled())
                removeItem(count() - 1);
            return false;
        }
    }
    return QComboBox::eventFilter(object, event);
}

void HColorComboBox::paintEvent(QPaintEvent *)
{
    QStyleOptionComboBox option;
    initStyleOption(&option);
    if (option.currentIcon.isNull())
    {
        auto color = itemData(currentIndex(), Qt::DecorationRole).value<QColor>();
        if (color.isValid())
        {
            int size = style()->pixelMetric(QStyle::PM_ButtonIconSize, &option, this);
            QPixmap pixmap(size, size);
            pixmap.fill(color);
            option.currentIcon = pixmap;
        }
    }

    QStylePainter painter(this);
    painter.setPen(palette().color(QPalette::Text));
    painter.drawComplexControl(QStyle::CC_ComboBox, option);
    painter.drawControl(QStyle::CE_ComboBoxLabel, option);
}

void HColorComboBox::dragEnterEvent(QDragEnterEvent *e)
{
    QColor color;
    if (e->mimeData()->hasColor())
        color = e->mimeData()->colorData().value<QColor>();
    else if (e->mimeData()->hasText())
        color = QColor(e->mimeData()->text());
    if (color.isValid())
        e->acceptProposedAction();
}

void HColorComboBox::dropEvent(QDropEvent *e)
{
    if (e->source() == this)
        return;
    if (e->mimeData()->hasColor())
        setCurrentColor(e->mimeData()->colorData().value<QColor>());
    else
        setCurrentColor(e->mimeData()->text());
}

void HColorComboBox::handleActivated(int index)
{
    if (isColorDialogEnabled() && index == count() - 1)
        popupDialog();

    auto c = color(index);
    if (c.isValid())
        emit colorPicked(c);
}

void HColorComboBox::popupDialog()
{
    auto color = QColorDialog::getColor(currentColor(), this, tr("选取颜色"), QColorDialog::ShowAlphaChannel);
    if (!color.isValid())
        return;
    setCurrentColor(color);
}

void HColorComboBox::init()
{
    d_ptr->model = new HColorModel(this);
    connect(this, SIGNAL(activated(int)), this, SLOT(handleActivated(int)));
    setModel(d_ptr->model);
    setAcceptDrops(true);
    view()->installEventFilter(this);
    setStandardColors();
}

HE_CONTROL_END_NAMESPACE
