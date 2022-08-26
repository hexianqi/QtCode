#include "HGraphicsDemoWidget_p.h"
#include "ui_HGraphicsDemoWidget.h"
#include "HGraphicsHelper.h"
#include "HGraphicsPixmapItem.h"
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsRectItem>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

class HTestGraphicsItem : public QGraphicsRectItem
{
public:
    explicit HTestGraphicsItem(QGraphicsItem *parent = nullptr);

public:
    void setItemFix(int);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    int _fix = 0;
};

HTestGraphicsItem::HTestGraphicsItem(QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{
    setFlags(ItemIsMovable | ItemIsFocusable | ItemIsSelectable | ItemSendsGeometryChanges);
}

void HTestGraphicsItem::setItemFix(int value)
{
    _fix = value % 3;
}

QVariant HTestGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if ((change == ItemPositionChange || change == ItemPositionHasChanged) && scene())
    {
        QVariant pos;
        if (_fix == 1)
            pos = HGraphicsHelper::fixByScene(this, value);
        else if (_fix == 2)
            pos = HGraphicsHelper::fixByOverlap(this, value);
        if (pos.isValid())
            return pos;
    }
    return QGraphicsRectItem::itemChange(change, value);
}

HGraphicsDemoWidget::HGraphicsDemoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HGraphicsDemoWidget),
    d_ptr(new HGraphicsDemoWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HGraphicsDemoWidget::~HGraphicsDemoWidget()
{
    delete ui;
}

void HGraphicsDemoWidget::setItemFix(int value)
{
    for (auto item : d_ptr->items)
        item->setItemFix(value);
}

void HGraphicsDemoWidget::init()
{
    ui->comboBox_1->addItems(QStringList() << tr(" 不限制 ") << tr(" 限制图形项范围 ") << tr(" 限制图形项碰撞 "));
    auto item1 = new HTestGraphicsItem;
    item1->setRect(0, 0, 100, 200);
    item1->setPos(10, 10);
    item1->setBrush(Qt::red);
    auto item2 = new HTestGraphicsItem;
    item2->setRect(0, 0, 100, 200);
    item2->setPos(200, 200);
    item2->setBrush(Qt::green);
    auto item3 = new HGraphicsPixmapItem();
    item3->setPixmap(QPixmap(":/Resources/image/about.png"));
    d_ptr->scene = new QGraphicsScene(this);
    d_ptr->scene->setSceneRect(0, 0, 1100, 700);
    d_ptr->scene->addItem(item1);
    d_ptr->scene->addItem(item2);
    d_ptr->scene->addItem(item3);

    d_ptr->items << item1 << item2;
    ui->graphicsView->setScene(d_ptr->scene);
    ui->graphicsView->setFixedSize(1200, 800);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    connect(ui->comboBox_1, SIGNAL(currentIndexChanged(int)), this, SLOT(setItemFix(int)));
}

HE_END_NAMESPACE
