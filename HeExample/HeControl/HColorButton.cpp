#include "HColorButton_p.h"
#include "HColorDrag.h"
#include "HColorModel.h"
#include "HColorPopup.h"
#include <QtCore/QMimeData>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QPainter>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>

HE_CONTROL_BEGIN_NAMESPACE

HColorButton::HColorButton(QWidget *parent) :
    QPushButton(parent),
    d_ptr(new HColorButtonPrivate)
{
    init();
}

HColorButton::HColorButton(HColorButtonPrivate &p, QWidget *parent) :
    QPushButton(parent),
    d_ptr(&p)
{
    init();
}

HColorButton::~HColorButton()
{
}

QStringList HColorButton::colors() const
{
    return d_ptr->model->colors();
}

QColor HColorButton::currentColor() const
{
    return d_ptr->currentColor;
}

bool HColorButton::isDragEnabled() const
{
    return d_ptr->dragEnabled;
}

bool HColorButton::isShowName() const
{
    return d_ptr->showName;
}

void HColorButton::setColors(const QStringList &value)
{
    d_ptr->model->setColors(value);
    setCurrentIndex(d_ptr->model->index(0, 0));
    update();
}

void HColorButton::setCurrentColor(const QColor &value)
{
    if (d_ptr->currentColor == value)
        return;

    auto index = d_ptr->model->contains(value);
    if (!index.isValid())
        index = d_ptr->model->addColor(value, findStandardColorName(value));
    setCurrentIndex(index);
}

void HColorButton::setDragEnabled(bool b)
{
    d_ptr->dragEnabled = b;
}

void HColorButton::setShowName(bool b)
{
    if (d_ptr->showName == b)
        return;
    d_ptr->showName = b;
    setText(b ? d_ptr->currentName : "");
}

void HColorButton::setStandardColors()
{
    d_ptr->model->setStandardColors();
}

void HColorButton::addColor(const QColor &color, const QString &name)
{
    d_ptr->model->addColor(color, name);
}

void HColorButton::clear()
{
    d_ptr->model->clear();
}

void HColorButton::mousePressEvent(QMouseEvent *e)
{
    if (d_ptr->dragEnabled && e->button() & Qt::LeftButton)
        d_ptr->pressPos = e->pos();
    QPushButton::mousePressEvent(e);
}

void HColorButton::mouseMoveEvent(QMouseEvent *e)
{
    if ((e->buttons() & Qt::LeftButton) && d_ptr->dragEnabled && (e->pos() - d_ptr->pressPos).manhattanLength() >= QApplication::startDragDistance())
    {
        auto drag = new HColorDrag(this, currentColor(), currentColor().name());
        drag->exec();
        setDown(false);
    }
    QPushButton::mouseMoveEvent(e);
}

void HColorButton::dragEnterEvent(QDragEnterEvent *e)
{
    QColor color;
    if (e->mimeData()->hasColor())
        color = e->mimeData()->colorData().value<QColor>();
    else if (e->mimeData()->hasText())
        color = QColor(e->mimeData()->text());
    if (color.isValid())
        e->acceptProposedAction();
}

void HColorButton::dropEvent(QDropEvent *e)
{
    if (e->source() == this)
        return;
    if (e->mimeData()->hasColor())
        setCurrentColor(e->mimeData()->colorData().value<QColor>());
    else
        setCurrentColor(e->mimeData()->text());
}

void HColorButton::setCurrentIndex(const QModelIndex &index)
{
    if (d_ptr->popup)
    {
        d_ptr->popup->hide();
        d_ptr->popup->setCurrentIndex(index);
    }

    d_ptr->currentColor = index.data(Qt::DecorationRole).value<QColor>();
    d_ptr->currentName = index.data(Qt::ToolTipRole).toString();

    QPixmap pixmap(64, 64);
    QPainter painter(&pixmap);
    painter.setBrush(d_ptr->currentColor);
    painter.drawRect(0, 0, pixmap.width() - 1, pixmap.height() - 1);

    setIcon(d_ptr->currentColor.isValid() ? pixmap : QIcon());
    if (d_ptr->showName)
        setText(d_ptr->currentName);
    if (d_ptr->currentColor.isValid())
        emit colorPicked(d_ptr->currentColor);
}

QString HColorButton::findStandardColorName(const QColor &color)
{
    for (auto name : QColor::colorNames())
    {
        if (color == QColor(name))
            return name;
    }
    return QString("Custom color");
}

QSize HColorButton::calcSize()
{
    if (!d_ptr->model)
        return QSize(80, 100);

    int margin = 2 * style()->pixelMetric(QStyle::PM_DefaultFrameWidth, nullptr, this) + 1;
    int cols = d_ptr->model->rowCount();
    int fit = qMax(3, (width() - margin) / 16);
    int fitRows = cols % fit == 0 ? cols / fit : (1 + cols / fit);
    int scExt = style()->pixelMetric(QStyle::PM_ScrollBarExtent, nullptr, this);
    if (fitRows <= 12)
        return QSize(fit * 16 + margin, fitRows * 16 + margin + 27);
    fit = qMax(3, (width() - margin - scExt) / 16);
    fitRows = cols / fit;
    return QSize(fit * 16 + margin + scExt + 1, 16 * 12 + margin + 30);
}

void HColorButton::showPopup()
{
    if (!d_ptr->popup)
    {
        d_ptr->popup = new HColorPopup(d_ptr->model, this);
        connect(d_ptr->popup, &HColorPopup::selectIndex, this, &HColorButton::setCurrentIndex);
        connect(d_ptr->popup, &HColorPopup::selectColor, this, &HColorButton::setCurrentColor);
    }
    auto point = mapToGlobal(rect().bottomLeft());
    auto avail = QApplication::primaryScreen()->availableGeometry();
    auto height = avail.height() - point.y();
    auto size = calcSize();
    if (size.height() > height)
        size.setHeight(height);
    d_ptr->popup->move(point);
    d_ptr->popup->setFixedSize(size);
    d_ptr->popup->show();
}

void HColorButton::init()
{
    d_ptr->model = new HColorModel(this);
    connect(this, &HColorButton::clicked, this, &HColorButton::showPopup);
    setStandardColors();
    setAcceptDrops(true);
    setCurrentIndex(d_ptr->model->index(0, 0));
    setWindowIcon(QIcon(":/image/ww/colorbutton.png"));
}

HE_CONTROL_END_NAMESPACE
