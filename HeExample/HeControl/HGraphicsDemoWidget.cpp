#include "HGraphicsDemoWidget_p.h"
#include "ui_HGraphicsDemoWidget.h"
#include "HGraphicsHelper.h"
#include "HGraphicsView.h"
#include "HGraphicsColorBoardItem.h"
#include "HGraphicsDiscButtonItem.h"
#include "HGraphicsNoteItem.h"
#include "HGraphicsPixmapItem.h"
#include "HGraphicsSliderItem.h"
#include "HRulerWidget.h"
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QScrollBar>
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
        item->setItemFix(HGraphicsObject::ItemFix(value));
}

void HGraphicsDemoWidget::init()
{
    QStringList list;
    for (int i = 0; i < 100; i++)
        list << tr("测试内容%1").arg(i);

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
    auto item4 = new HGraphicsSliderItem(Qt::Horizontal);
    auto item5 = new HGraphicsColorBoardItem;
    auto item6 = new HGraphicsNoteItem();
    item6->setTitle(tr("测试标题"));
    item6->setContent(list);
    auto item7 = new HGraphicsDiscButtonItem;
    d_ptr->items << item3 << item4 << item5 << item6 << item7;
    d_ptr->scene = new QGraphicsScene(this);
    d_ptr->scene->setSceneRect(0, 0, 1500, 1500);
    d_ptr->scene->addItem(item1);
    d_ptr->scene->addItem(item2);
    for (auto item : d_ptr->items)
        d_ptr->scene->addItem(item);

    auto horizontalRuler = new HRulerWidget(Qt::Horizontal);
    auto verticalRuler = new HRulerWidget(Qt::Vertical);
    auto graphicsView = new HGraphicsView;
    graphicsView->setScene(d_ptr->scene);
    graphicsView->setFixedSize(700, 700);
    graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    graphicsView->centerOn(item1);
    ui->gridLayout->addWidget(horizontalRuler, 1, 1);
    ui->gridLayout->addWidget(verticalRuler, 2, 0, 1, 1, Qt::AlignRight);
    ui->gridLayout->addWidget(graphicsView, 2, 1);

    connect(ui->comboBox_1, SIGNAL(currentIndexChanged(int)), this, SLOT(setItemFix(int)));
    connect(item5, &HGraphicsColorBoardItem::colorPicked, this, [=](QColor value) { qDebug() << value.toRgb(); });
    connect(graphicsView->horizontalScrollBar(), &QScrollBar::valueChanged, [=] { horizontalRuler->setOffset(graphicsView->mapToScene(0,0).x()); });
    connect(graphicsView->verticalScrollBar(),&QScrollBar::valueChanged, [=] { verticalRuler->setOffset(graphicsView->mapToScene(0,0).y()); });
    connect(graphicsView, &HGraphicsView::mouseMovePos, [=](QPointF pos)
            {
                horizontalRuler->setSlidingPos(pos.x());
                verticalRuler->setSlidingPos(pos.y());
            });
}

HE_END_NAMESPACE
