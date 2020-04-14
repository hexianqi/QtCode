#include "HImageBrowser_p.h"
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtGui/QImageReader>
#include <QtWidgets/QAction>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QFileDialog>

HE_CONTROL_BEGIN_NAMESPACE

HImageBrowser::HImageBrowser(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HImageBrowserPrivate)
{
    init();
}

HImageBrowser::HImageBrowser(HImageBrowserPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HImageBrowser::~HImageBrowser()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

QSize HImageBrowser::sizeHint() const
{
    return {300, 150};
}

QSize HImageBrowser::minimumSizeHint() const
{
    return {60, 30};
}

QColor HImageBrowser::backgroundStart() const
{
    return d_ptr->backgroundStart;
}

QColor HImageBrowser::backgroundEnd() const
{
    return d_ptr->backgroundEnd;
}

int HImageBrowser::bottomSpace() const
{
    return d_ptr->bottomSpace;
}

int HImageBrowser::buttonSpace() const
{
    return d_ptr->buttonSpace;
}

QSize HImageBrowser::iconSize() const
{
    return d_ptr->iconSize;
}

bool HImageBrowser::isFill() const
{
    return d_ptr->fill;
}

bool HImageBrowser::isFade() const
{
    return d_ptr->fade;
}

bool HImageBrowser::isKeyMove() const
{
    return d_ptr->keyMove;
}

void HImageBrowser::load()
{
    auto dir = QFileDialog::getExistingDirectory(this, tr("打开目录"),".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir.isEmpty())
        return;
    load(dir);
}

void HImageBrowser::load(const QString &folder)
{
    QDir dir(folder);
    if (!dir.exists())
        return;

    clear();

    QStringList filters;
    for (const auto &s : QImageReader::supportedImageFormats())
        filters << "*." + s;
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters(filters);
    for (const auto &f : dir.entryList())
        d_ptr->imageNames << folder + QDir::separator() + f;
    d_ptr->totalNum = d_ptr->imageNames.size();
    moveFirst();
}

void HImageBrowser::clear()
{
    d_ptr->currentIndex = -1;
    d_ptr->totalNum = 0;
    d_ptr->currentImage = QImage();
    d_ptr->imageNames.clear();
    update();
}

void HImageBrowser::setBackgroundStart(const QColor &value)
{
    if (d_ptr->backgroundStart == value)
        return;
    d_ptr->backgroundStart = value;
    update();
}

void HImageBrowser::setBackground(const QColor &value)
{
    if (d_ptr->backgroundEnd == value)
        return;
    d_ptr->backgroundEnd = value;
    update();
}

void HImageBrowser::setBottomSpace(int value)
{
    if (d_ptr->bottomSpace == value)
        return;
    d_ptr->bottomSpace = value;
    update();
}

void HImageBrowser::setButtonSpace(int value)
{
    if (d_ptr->buttonSpace == value)
        return;
    d_ptr->buttonSpace = value;
    update();
}

void HImageBrowser::setIconSize(QSize value)
{
    if (d_ptr->iconSize == value)
        return;
    d_ptr->iconSize = value;
    d_ptr->previous->setIconSize(value);
    d_ptr->next->setIconSize(value);
    calcGeo();
}

void HImageBrowser::setFill(bool b)
{
    if (d_ptr->fill == b)
        return;
    d_ptr->fill = b;
    update();
}

void HImageBrowser::setFade(bool b)
{
    if (d_ptr->fade == b)
        return;
    d_ptr->fade = b;
    if (b)
    {
        d_ptr->opacity = 0;
        d_ptr->timer->start();
    }
    else
    {
        d_ptr->timer->stop();
        d_ptr->opacity = 1;
        update();
    }
}

void HImageBrowser::setKeyMove(bool b)
{
    if (d_ptr->keyMove == b)
        return;
    d_ptr->keyMove = b;
    update();
}

void HImageBrowser::keyPressEvent(QKeyEvent *e)
{
    if (d_ptr->keyMove)
    {
        if (e->key() == Qt::Key_Left || e->key() == Qt::Key_Up)
            movePrevious();
        if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Down)
            moveNext();
    }
    QWidget::keyPressEvent(e);
}

void HImageBrowser::resizeEvent(QResizeEvent *)
{
    calcGeo();
}

void HImageBrowser::showEvent(QShowEvent *)
{
    calcGeo();
}

void HImageBrowser::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
    drawImage(&painter);
}

void HImageBrowser::drawBackground(QPainter *painter)
{
    auto gradient = QLinearGradient(QPoint(0, 0), QPoint(0, height()));
    gradient.setColorAt(0.0, d_ptr->backgroundStart);
    gradient.setColorAt(1.0, d_ptr->backgroundEnd);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRect(rect());
    painter->restore();
}

void HImageBrowser::drawImage(QPainter *painter)
{
    if (d_ptr->totalNum <= 0)
        return;

    painter->save();
    painter->setOpacity(d_ptr->opacity);
    if (d_ptr->fill)
    {
        painter->drawImage(rect(), d_ptr->currentImage);
        painter->restore();
    }
    else
    {
        int x = rect().center().x() - d_ptr->currentImage.width() / 2;
        int y = rect().center().y() - d_ptr->currentImage.height() / 2;
        painter->drawImage(QPoint(x, y), d_ptr->currentImage);
        painter->restore();
    }
}

void HImageBrowser::moveFirst()
{
    moveTo(0);
}

void HImageBrowser::movePrevious()
{
    moveTo(d_ptr->currentIndex - 1);
}

void HImageBrowser::moveNext()
{
    moveTo(d_ptr->currentIndex + 1);
}

void HImageBrowser::moveLast()
{
    moveTo(d_ptr->totalNum - 1);
}

void HImageBrowser::moveTo(int index)
{
    if (index < 0 || index >= d_ptr->totalNum || index == d_ptr->currentIndex)
        return;
    d_ptr->currentIndex = index;
    d_ptr->currentImage = QImage(d_ptr->imageNames.at(index));
    if (d_ptr->fade)
    {
        d_ptr->opacity = 0;
        d_ptr->timer->start();
    }
    else
        update();
}

void HImageBrowser::doFading()
{
    d_ptr->opacity += 0.05;
    if (d_ptr->opacity > 1.0)
    {
        d_ptr->opacity = 1.0;
        d_ptr->timer->stop();
    }
    update();
}

void HImageBrowser::calcGeo()
{
    d_ptr->previous->move(d_ptr->buttonSpace, (height() - d_ptr->previous->height()) / 2);
    d_ptr->next->move(width() - d_ptr->buttonSpace - d_ptr->next->width(), (height() - d_ptr->next->height()) / 2);
}

void HImageBrowser::init()
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(100);
    d_ptr->previous = new QToolButton(this);
    d_ptr->previous->setIcon(QIcon(":/image/beautify/back.png"));
    d_ptr->previous->setIconSize(d_ptr->iconSize);
    d_ptr->next = new QToolButton(this);
    d_ptr->next->setIcon(QIcon(":/image/beautify/next.png"));
    d_ptr->next->setIconSize(d_ptr->iconSize);
    auto actionLoad = new QAction(tr("载入"), this);
    auto actionClear = new QAction("清空", this);
    auto actionFill = new QAction(tr("填充"), this);
    auto actionFade = new QAction(tr("渐变"), this);
    actionFill->setCheckable(true);
    actionFade->setCheckable(true);
    addAction(actionLoad);
    addAction(actionClear);
    addAction(actionFill);
    addAction(actionFade);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setStyleSheet("QToolButton { background-color:rgba(0,0,0,0); border-style:none; }");
    connect(d_ptr->timer, &QTimer::timeout, this, &HImageBrowser::doFading);
    connect(d_ptr->previous, &QToolButton::clicked, this, &HImageBrowser::movePrevious);
    connect(d_ptr->next, &QToolButton::clicked, this, &HImageBrowser::moveNext);
    connect(actionLoad, &QAction::triggered, this, [=] { load(); });
    connect(actionClear, &QAction::triggered, this, &HImageBrowser::clear);
    connect(actionFill, &QAction::triggered, this, &HImageBrowser::setFill);
    connect(actionFade, &QAction::triggered, this, &HImageBrowser::setFade);
    calcGeo();
}

HE_CONTROL_END_NAMESPACE
