#include "HIconFontWidget_p.h"
#include "ui_HIconFontWidget.h"
#include "HIconFontFactory.h"
#include "HDrawHelper.h"

HE_BEGIN_NAMESPACE

HGraphicsTextItem::HGraphicsTextItem(QGraphicsItem *parent) :
    QGraphicsTextItem(parent)
{
    setCacheMode(ItemCoordinateCache, QSize(20, 20));
    setAcceptHoverEvents(true);
}

void HGraphicsTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    setDefaultTextColor(Qt::red);
    emit hoverEntered();
}

void HGraphicsTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    setDefaultTextColor(Qt::black);
}

HIconFontWidget::HIconFontWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HIconFontWidget),
    d_ptr(new HIconFontWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HIconFontWidget::~HIconFontWidget()
{
    delete ui;
}

void HIconFontWidget::on_comboBox_01_currentTextChanged(const QString &value)
{
    if (d_ptr->fontFamily == value)
        return;
    d_ptr->fontFamily = value;
    d_ptr->font = d_ptr->fontFactory->createFont(value);
    d_ptr->font.setPixelSize(15);
    d_ptr->scene->clear();

    auto n = 0;
    auto range = d_ptr->fontFactory->fontRange(value);
    auto count = range.y() - range.x() + 1;
    for (int i = range.x(); i <= range.y(); i++)
    {
        if (!checkIcon(i))
            continue;
        auto item = new HGraphicsTextItem;
        item->setFont(d_ptr->font);
        item->setPlainText((QChar)i);
        item->setToolTip(QString("0x%1").arg(i, 0, 16));
        item->setPos((n % 20) * 30, (n / 20) * 30);
        d_ptr->scene->addItem(item);
        connect(item, &HGraphicsTextItem::hoverEntered, this, &HIconFontWidget::handleHoverEntered);
        n++;
    }
    ui->label_01->setText(QString("%1/%2").arg(n).arg(count));
}

void HIconFontWidget::handleHoverEntered()
{
    auto item = qobject_cast<HGraphicsTextItem *>(sender());
    if (item == nullptr)
        return;
    d_ptr->font.setPixelSize(d_ptr->iconSize);
    auto value = item->toolTip();
    auto icon = QChar(value.toInt(nullptr, 16));
    auto pixmap = QPixmap::fromImage(HDrawHelper::createFontImage(d_ptr->font, icon, QSize(d_ptr->iconSize, d_ptr->iconSize), QColor("#753775")));

    ui->label_02->setText(value);
    ui->label_03->setFont(d_ptr->font);
    ui->label_03->setText(icon);
    ui->label_04->setPixmap(pixmap);
    ui->pushButton_01->setFont(d_ptr->font);
    ui->pushButton_01->setText(icon);
    ui->toolButton_01->setIcon(pixmap);
    d_ptr->font.setPixelSize(15);
    ui->pushButton_02->setFont(d_ptr->font);
    ui->pushButton_02->setText(QString("%1 测试图标").arg((QChar)icon));
    ui->pushButton_03->setIcon(pixmap);
}

bool HIconFontWidget::checkIcon(int icon)
{
    d_ptr->font.setPixelSize(120);
    auto image = HDrawHelper::createFontImage(d_ptr->font, icon, QSize(120, 120), QColor(0xFF0000));
    auto height = image.height();
    auto width = image.width();
    for (int i = 0; i < height; i++)
    {
        auto line = image.scanLine(i);
        for (int j = 0; j < width; j++)
        {
            if (line[j] > 0x00)
                return true;
        }
    }
    return false;
}

void HIconFontWidget::init()
{
    d_ptr->fontFactory = new HIconFontFactory(this);
    d_ptr->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(d_ptr->scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->comboBox_01->addItems(d_ptr->fontFactory->families());
    ui->splitter->setStretchFactor(0, 10);
}

HE_END_NAMESPACE
