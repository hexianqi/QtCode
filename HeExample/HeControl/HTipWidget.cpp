#include "HTipWidget_p.h"
#include <QtCore/QStringListModel>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QBoxLayout>

HE_CONTROL_BEGIN_NAMESPACE

HTipWidget::HTipWidget(QWidget *parent) :
    QFrame(parent),
    d_ptr(new HTipWidgetPrivate)
{
    init();
}

HTipWidget::HTipWidget(HTipWidgetPrivate &p, QWidget *parent) :
    QFrame(parent),
    d_ptr(&p)
{
    init();
}

HTipWidget::~HTipWidget()
{
}

QStringList HTipWidget::tips() const
{
    return d_ptr->model->stringList();
}

int HTipWidget::currentTip() const
{
    return d_ptr->currentTip.row();
}

QIcon HTipWidget::defaultIcon() const
{
    return d_ptr->defaultIcon;
}

QSize HTipWidget::iconSize() const
{
    return d_ptr->iconSize;
}

Qt::Alignment HTipWidget::iconAlignment() const
{
    return d_ptr->label->alignment() & Qt::AlignVertical_Mask;
}

bool HTipWidget::isCheckVisible() const
{
    return d_ptr->check->isVisible();
}

bool HTipWidget::isCloseVisible() const
{
    return d_ptr->closeButton->isVisible();
}

bool HTipWidget::isTipsEnabled() const
{
    return d_ptr->check->isChecked();
}

QFrame::Shape HTipWidget::canvasFrameShape() const
{
    return d_ptr->browser->frameShape();
}

QWidget *HTipWidget::headerWidget() const
{
    return d_ptr->headerWidget;
}

QTextBrowser *HTipWidget::tipCanvas() const
{
    return d_ptr->browser;
}

void HTipWidget::setTips(QStringList value)
{
    if (d_ptr->model->stringList() == value)
        return;
    d_ptr->model->setStringList(value);
    setCurrentTip(0);
}

void HTipWidget::setCurrentTip(int value)
{
    value = qBound(0, value, d_ptr->model->rowCount() - 1);
    if (value == currentTip())
        return;
    d_ptr->currentTip = d_ptr->model->index(value, 0);
    showTip();
    emit tipChanged(value);
}

void HTipWidget::setDefaultIcon(const QIcon &value)
{
    d_ptr->defaultIcon = value;
    showTip();
}

void HTipWidget::setIconSize(QSize value)
{
    if (d_ptr->iconSize == value)
        return;
    d_ptr->iconSize = value;
    showTip();
}

void HTipWidget::setIconAlignment(Qt::Alignment value)
{
    d_ptr->label->setAlignment(value);
}

void HTipWidget::setCheckVisible(bool b)
{
    d_ptr->check->setVisible(b);
}

void HTipWidget::setCloseVisible(bool b)
{
    d_ptr->closeButton->setVisible(b);
}

void HTipWidget::setTipsEnabled(bool b)
{
    d_ptr->check->setChecked(b);
}

void HTipWidget::setCanvasFrameShape(QFrame::Shape value)
{
    d_ptr->browser->setFrameShape(value);
}

void HTipWidget::setHeaderWidget(QWidget *p)
{
    delete d_ptr->headerWidget;
    d_ptr->layout->insertWidget(0, p);
    d_ptr->headerWidget = p;
}

void HTipWidget::prevTip()
{
    int r = currentTip();
    setCurrentTip(r == 0 ? d_ptr->model->rowCount() - 1 : r - 1);
}

void HTipWidget::nextTip()
{
    int r = currentTip();
    setCurrentTip(r == d_ptr->model->rowCount() - 1 ? 0 : r + 1);
}

void HTipWidget::showTip()
{
    auto v = d_ptr->currentTip.data(Qt::DisplayRole);
    d_ptr->browser->setHtml(v.toString());
    if (v.type() == QVariant::Icon)
        d_ptr->label->setPixmap(qvariant_cast<QIcon>(v).pixmap(d_ptr->iconSize));
    else if (v.type() == QVariant::Pixmap)
        d_ptr->label->setPixmap(qvariant_cast<QPixmap>(v));
    else if (v.type() == QVariant::Image)
        d_ptr->label->setPixmap(QPixmap::fromImage(qvariant_cast<QImage>(v)));
    else
        d_ptr->label->setPixmap(d_ptr->defaultIcon.pixmap(d_ptr->iconSize));
}

void HTipWidget::init()
{
    d_ptr->iconSize = QSize(128, 128);
    d_ptr->model = new QStringListModel(this);
    d_ptr->currentTip = d_ptr->model->index(-1, 0);
    d_ptr->label = new QLabel;
    d_ptr->check = new QCheckBox(tr("打开时显示"));
    d_ptr->check->setChecked(true);
    d_ptr->prevButton = new QPushButton(tr("上一个"));
    d_ptr->nextButton = new QPushButton(tr("下一个"));
    d_ptr->closeButton = new QPushButton(tr("关闭"));
    d_ptr->browser = new QTextBrowser;
    d_ptr->browser->setOpenExternalLinks(true);

    setBackgroundRole(QPalette::Base);
    setFrameShape(d_ptr->browser->frameShape());
    setFrameShadow(d_ptr->browser->frameShadow());
    auto palette = d_ptr->browser->palette();
    setPalette(palette);
    palette.setColor(QPalette::Base, Qt::transparent);
    d_ptr->browser->setPalette(palette);
    setAutoFillBackground(true);
    d_ptr->browser->setAutoFillBackground(false);
    d_ptr->browser->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

    auto layout = new QHBoxLayout;
    layout->addWidget(d_ptr->check);
    layout->addStretch();
    layout->addWidget(d_ptr->prevButton);
    layout->addWidget(d_ptr->nextButton);
    layout->addWidget(d_ptr->closeButton);
    d_ptr->layout = new QVBoxLayout(this);
    d_ptr->layout->addWidget(d_ptr->label);
    d_ptr->layout->addWidget(d_ptr->browser);
    d_ptr->layout->addLayout(layout);

    connect(d_ptr->prevButton, &QPushButton::clicked, this, &HTipWidget::prevTip);
    connect(d_ptr->nextButton, &QPushButton::clicked, this, &HTipWidget::nextTip);
    connect(d_ptr->closeButton, &QPushButton::clicked, this, &HTipWidget::close);
    showTip();
}


HE_CONTROL_END_NAMESPACE
