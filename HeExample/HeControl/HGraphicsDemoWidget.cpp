#include "HGraphicsDemoWidget_p.h"
#include "ui_HGraphicsDemoWidget.h"
#include "HGraphicsHelper.h"
#include "HGraphicsView.h"
#include "HGraphicsColorBoardItem.h"
#include "HGraphicsDiscButtonItem.h"
#include "HGraphicsFlowLayout.h"
#include "HGraphicsNoteItem.h"
#include "HGraphicsPixmapItem.h"
#include "HGraphicsSliderItem.h"
#include "HGraphicsProxyWidget.h"
#include "HRulerWidget.h"
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
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
    ui->comboBox_1->addItems(QStringList() << tr(" 不限制 ") << tr(" 限制图形项范围 ") << tr(" 限制图形项碰撞 "));
    connect(ui->comboBox_1, SIGNAL(currentIndexChanged(int)), this, SLOT(setItemFix(int)));

    d_ptr->scene = new QGraphicsScene(this);
    d_ptr->scene->setSceneRect(0, 0, 1500, 1500);

    addTestItem();
    addPixmapItem();
    addSliderItem();
    addColorBoardItem();
    addNoteItem();
    addDiscButtonItem();
    addProxyWidget();
    addFlowLayout();
    initGraphicsView();
}

void HGraphicsDemoWidget::initGraphicsView()
{
    auto layout = new QGridLayout;
    auto horizontalRuler = new HRulerWidget(Qt::Horizontal);
    auto verticalRuler = new HRulerWidget(Qt::Vertical);
    auto graphicsView = new HGraphicsView;
    graphicsView->setScene(d_ptr->scene);
    graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    graphicsView->centerOn(d_ptr->items.first());
    layout->addWidget(horizontalRuler, 0, 1, Qt::AlignBottom);
    layout->addWidget(verticalRuler, 1, 0, Qt::AlignRight);
    layout->addWidget(graphicsView, 1, 1);
    layout->setColumnStretch(0, 0);
    layout->setColumnStretch(1, 10);
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 10);
    ui->groupBox->setLayout(layout);

    connect(graphicsView->horizontalScrollBar(), &QScrollBar::valueChanged, [=] { horizontalRuler->setOffset(graphicsView->mapToScene(0,0).x()); });
    connect(graphicsView->verticalScrollBar(),&QScrollBar::valueChanged, [=] { verticalRuler->setOffset(graphicsView->mapToScene(0,0).y()); });
    connect(graphicsView, &HGraphicsView::mouseMovePos, [=](QPointF pos)
            {
                horizontalRuler->setSlidingPos(pos.x());
                verticalRuler->setSlidingPos(pos.y());
            });
}

void HGraphicsDemoWidget::addTestItem()
{
    auto item1 = new HTestGraphicsItem;
    item1->setRect(0, 0, 100, 200);
    item1->setPos(10, 10);
    item1->setBrush(Qt::red);
    auto item2 = new HTestGraphicsItem;
    item2->setRect(0, 0, 100, 200);
    item2->setPos(200, 200);
    item2->setBrush(Qt::green);
    d_ptr->scene->addItem(item1);
    d_ptr->scene->addItem(item2);
}

void HGraphicsDemoWidget::addPixmapItem()
{
    auto item = new HGraphicsPixmapItem();
    item->setPixmap(QPixmap(":/Resources/image/about.png"));
    d_ptr->items << item;
    d_ptr->scene->addItem(item);
}

void HGraphicsDemoWidget::addSliderItem()
{
    auto item = new HGraphicsSliderItem(Qt::Horizontal);
    d_ptr->items << item;
    d_ptr->scene->addItem(item);
}

void HGraphicsDemoWidget::addColorBoardItem()
{
    auto item = new HGraphicsColorBoardItem();
    d_ptr->items << item;
    d_ptr->scene->addItem(item);
    connect(item, &HGraphicsColorBoardItem::colorPicked, this, [=](QColor value) { qDebug() << value.toRgb(); });
}

void HGraphicsDemoWidget::addNoteItem()
{
    QStringList list;
    for (int i = 0; i < 100; i++)
        list << tr("测试内容%1").arg(i);
    auto item = new HGraphicsNoteItem();
    item->setTitle(tr("测试标题"));
    item->setContent(list);
    d_ptr->items << item;
    d_ptr->scene->addItem(item);
}

void HGraphicsDemoWidget::addDiscButtonItem()
{
    auto item = new HGraphicsDiscButtonItem();
    d_ptr->items << item;
    d_ptr->scene->addItem(item);
}

void HGraphicsDemoWidget::addProxyWidget()
{
    QString style = "QPushButton { border-style: none; border: 0px; color: #FFFFFF; border-radius:6px; background: #00beac; font-size:22px; font-weight:bold; }"
                    "QPushButton:hover { background: #ff0000; }"
                    "QPushButton:pressed { background: #00ffff; }";

    auto btn = new QPushButton("GraphicsProxyWidget");
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(style);

    auto groupBox = new QGroupBox("group");
    auto numberLabel = new QLabel("lable");
    auto numberEdit = new QLineEdit;
    auto layout = new QFormLayout;
    layout->addRow(numberLabel, numberEdit);
    layout->addRow(new QLabel("lable"), btn);
    groupBox->setLayout(layout);

    auto proxy = new HGraphicsProxyWidget;
    proxy->setCenterWidget(groupBox);
    proxy->setPos(100, 100);
    d_ptr->scene->addItem(proxy);
}

void HGraphicsDemoWidget::addFlowLayout()
{
    auto pushbutton1 = new QPushButton;
    auto pushbutton2 = new QPushButton;
    auto pushbutton3 = new QPushButton;
    auto pushbutton4 = new QPushButton;
    auto proxyWidget0 = new HGraphicsProxyWidget;
    auto proxyWidget1 = new QGraphicsProxyWidget;
    auto proxyWidget2 = new QGraphicsProxyWidget;
    auto proxyWidget3 = new QGraphicsProxyWidget;
    auto proxyWidget4 = new QGraphicsProxyWidget;
    auto layout = new HGraphicsFlowLayout;
    proxyWidget1->setWidget(pushbutton1);
    proxyWidget2->setWidget(pushbutton2);
    proxyWidget3->setWidget(pushbutton3);
    proxyWidget4->setWidget(pushbutton4);
    layout->addItem(proxyWidget1);
    layout->addItem(proxyWidget2);
    layout->addItem(proxyWidget3);
    layout->addItem(proxyWidget4);
    proxyWidget0->setCenterLayout(layout);
    d_ptr->scene->addItem(proxyWidget0);
}

HE_END_NAMESPACE
