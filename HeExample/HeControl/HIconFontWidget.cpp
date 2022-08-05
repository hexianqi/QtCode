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

void HIconFontWidget::setFontFamily(const QString &value)
{
    if (d_ptr->fontFamily == value)
        return;
    d_ptr->fontFamily = value;
    d_ptr->font = d_ptr->fontFactory->createFont(value);
    d_ptr->font.setPixelSize(15);
    d_ptr->scene->clear();

    auto x = 0;
    auto range = d_ptr->fontFactory->fontRange(value);
    for (int i = range.x(); i <= range.y(); i++)
    {
        if (!checkIcon(i))
            continue;
        auto item = new HGraphicsTextItem;
        item->setFont(d_ptr->font);
        item->setPlainText((QChar)i);
        item->setToolTip(QString("0x%1").arg(i, 0, 16));
        item->setPos((x % 20) * 30, (x / 20) * 30);
        d_ptr->scene->addItem(item);
        x++;
    }
  //  d_ptr->scene->setSceneRect(QRectF(0, 0, 636, (x / 20) * 30 + 36));
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
//    auto layout = new QGraphicsGridLayout;
//    layout->addItem(new QGraphicsTextItem("123"), 0, 0);
//    layout->addItem(pushButton, 0, 1);

//    QGraphicsWidget *form = new QGraphicsWidget;
//    form->setLayout(layout);
//    scene.addItem(form);





    ui->comboBox_01->addItems(d_ptr->fontFactory->families());
    ui->splitter->setStretchFactor(0, 10);





    connect(ui->comboBox_01, &QComboBox::currentTextChanged, this, &HIconFontWidget::setFontFamily);
    ui->comboBox_01->setCurrentIndex(0);

}



HE_END_NAMESPACE
