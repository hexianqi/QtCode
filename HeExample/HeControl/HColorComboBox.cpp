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

HColorComboBox::~HColorComboBox()
{
}

QColor HColorComboBox::color(int index) const
{
    return qvariant_cast<QColor>(itemData(index, Qt::DecorationRole));
}

bool HColorComboBox::isColorDialogEnabled() const
{
    return d_ptr->colorDialogEnabled;
}

int HColorComboBox::colorCount() const
{
    return d_ptr->model->rowCount();
}

QColor HColorComboBox::currentColor() const
{
    return color(currentIndex());
}

QStringList HColorComboBox::colors() const
{
    return d_ptr->model->colors();
}

void HColorComboBox::setStandardColors()
{
    d_ptr->model->setStandardColors();
}

void HColorComboBox::addColor(const QColor &color, const QString &name)
{
    insertColor(colorCount(), color, name);
}

void HColorComboBox::insertColor(int index, const QColor &color, const QString &name)
{
    d_ptr->model->insertColor(index, color, name);
}

void HColorComboBox::setColorDialogEnabled(bool b)
{
    d_ptr->colorDialogEnabled = b;
}

void HColorComboBox::setCurrentColor(const QColor &value)
{
    int i = findData(value, Qt::DecorationRole);
    if (i != -1)
    {
        setCurrentIndex(i);
    }
    else
    {
        addColor(value, tr("自定义颜色"));
        setCurrentIndex(count() - 1);
    }
}

void HColorComboBox::setColors(const QStringList &value)
{
    for (auto v : value)
    {
        auto s = v.split(",");
        addColor(QColor(s[0]), s[1]);
    }
    handleActivated(0);
    update();
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
        auto c = qvariant_cast<QColor>(itemData(currentIndex(), Qt::DecorationRole));
        if (c.isValid())
        {
            int size = style()->pixelMetric(QStyle::PM_ButtonIconSize, &option, this);
            QPixmap pm(size, size);
            pm.fill(c);
            option.currentIcon = pm;
        }
    }

    QStylePainter painter(this);
    painter.setPen(palette().color(QPalette::Text));
    painter.drawComplexControl(QStyle::CC_ComboBox, option);
    painter.drawControl(QStyle::CE_ComboBoxLabel, option);
}

void HColorComboBox::dragEnterEvent(QDragEnterEvent *e)
{
    QColor c;
    if (e->mimeData()->hasColor())
        c = qvariant_cast<QColor>(e->mimeData()->colorData());
    else if (e->mimeData()->hasText())
        c = QColor(e->mimeData()->text());
    if (c.isValid())
        e->acceptProposedAction();
}

void HColorComboBox::dropEvent(QDropEvent *e)
{
    if (e->source() == this)
        return;
    if (e->mimeData()->hasColor())
        setCurrentColor(qvariant_cast<QColor>(e->mimeData()->colorData()));
    else
        setCurrentColor(e->mimeData()->text());
}

void HColorComboBox::handleActivated(int index)
{
    if (isColorDialogEnabled() && index == count() - 1)
        popupDialog();

    auto c = color(index);
    if (c.isValid())
        emit activated(c);
}

void HColorComboBox::popupDialog()
{
    auto c = QColorDialog::getColor(currentColor(), this, tr("选取颜色"), QColorDialog::ShowAlphaChannel);
    if (!c.isValid())
        return;
    setCurrentColor(c);
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
