#include "HDemoWidget_p.h"
#include "ui_HDemoWidget.h"
#include "HFaltStyle.h"
#include "HAntLine.h"
#include "HBattery.h"
#include "HBarRuler.h"
#include "HCpuMemoryLabel.h"
#include "HGaugeArc.h"
#include "HSlideNavigation.h"
#include "HRbTableHeaderView.h"
#include <QtCore/QTimer>
#include <QtWidgets/QTableWidget>
#include <QtGui/QStandardItemModel>

HE_CONTROL_BEGIN_NAMESPACE

HDemoWidget::HDemoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HDemoWidget),
    d_ptr(new HDemoWidgetPrivate)
{
    ui->setupUi(this);
    init();
}

HDemoWidget::~HDemoWidget()
{
    delete ui;
}

void HDemoWidget::init()
{
    d_ptr->style = new HFaltStyle(this);
//    addSlideNavigation();
    addCpuMemoryLabel();
    addBarRuler();
    addAntLine();
    addBattery();
    addGaugeArc();
    addMultHeaderTableView();
    addMultHeaderTableWidget();
}

void HDemoWidget::addCpuMemoryLabel()
{
    auto w = new HCpuMemoryLabel();
    w->setFont(QFont("Microsoft Yahei", 13));
    w->setStyleSheet("QLabel{ background-color: #000000; color: #64B8FF; }");
    w->start(1500);
    ui->tabWidget->addTab(w, tr("资源管理器"));
}

void HDemoWidget::addBarRuler()
{
    auto w = new HBarRuler();
    w->setValue(30);    
    auto timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, &QTimer::timeout, this, [=] { w->setValue(qrand() % 100); });
    timer->start();
    ui->tabWidget->addTab(w, tr("柱状标尺"));
}

//void HDemoWidget::addSlideNavigation()
//{
//    auto widget = new HSlideNavigation;
//    widget->setBarRadious(10);
//    widget->setItemRadious(10);
//    widget->setItemBackgroundStart(QColor(255, 0, 0));
//    widget->setItemBackgroundEnd(QColor(225, 20, 10));
//    widget->addItem("第一名");
//    widget->addItem("第二名");
//    widget->addItem("第三名");
//    widget->addItem("第四名");
//    widget->addItem("第五名");
//    widget->addItem("第六名");
//    widget->addItem("第七名");
//    widget->addItem("第八名");
//    ui->tabWidget->addTab(widget, tr("导航"));
//}

void HDemoWidget::addAntLine()
{
    auto l = new QGridLayout;
    auto w1 = new HAntLine;
    w1->setLineSpeed(500);
    auto w2 = new HAntLine;
    w2->setLineStyle(HAntLine::RoundedRect);
    w2->setLength(10);
    auto w3 = new HAntLine;
    w3->setLineStyle(HAntLine::Ellipse);
    w3->setLineColor(Qt::red);
    auto w4 = new HAntLine;
    w4->setLineStyle(HAntLine::Circle);
    w4->setLineWidth(5);
    l->addWidget(w1, 0, 0);
    l->addWidget(w2, 0, 1);
    l->addWidget(w3, 1, 0);
    l->addWidget(w4, 1, 1);
    addTab(l, tr("蚂蚁线"));
}

void HDemoWidget::addBattery()
{
    auto l = new QGridLayout;
    auto b = new HBattery;
    auto s = new QSlider;
    s->setOrientation(Qt::Horizontal);
    s->setSingleStep(10);
    connect(s, &QSlider::valueChanged, b, &HBattery::setValue);
    l->addWidget(b, 0, 0);
    l->addWidget(s, 1, 0);
    addTab(l, tr("电池电量"));
    d_ptr->style->setStyle(s, 8, "#505050", "#1ABC9C", "#1ABC9C");
}

void HDemoWidget::addGaugeArc()
{
    auto l = new QGridLayout;
    auto g = new HGaugeArc;
    auto c = new QComboBox;
    auto s = new QSlider;
    c->addItem(tr("圆形指示器"), HGaugeArc::Circle);
    c->addItem(tr("指针指示器"), HGaugeArc::Indicator);
    c->addItem(tr("圆角指针指示器"), HGaugeArc::IndicatorR);
    c->addItem(tr("三角形指示器"), HGaugeArc::Triangle);
    s->setOrientation(Qt::Horizontal);
    s->setSingleStep(10);
    connect(c, &QComboBox::currentTextChanged, this, [=](QString /*index*/) { g->setPointerStyle((HGaugeArc::PointerStyle)c->currentIndex()); });
    connect(s, &QSlider::valueChanged, g, &HGaugeArc::setValue);

    l->addWidget(g, 0, 0, 1, 2);
    l->addWidget(c, 1, 0);
    l->addWidget(s, 1, 1);
    addTab(l, tr("圆弧仪表盘"));
}

void HDemoWidget::addMultHeaderTableView()
{
    auto hHead = new HRbTableHeaderView(Qt::Horizontal, 3, 4);
    auto hModel = hHead->model();
    hHead->setSectionsClickable(true);
    hHead->setSpan(0, 0, 3, 0);
    hHead->setSpan(0, 1, 2, 2);
    hHead->setSpan(1, 3, 2, 1);
    hHead->setRowHeight(0, 30);
    hHead->setRowHeight(1, 30);
    hHead->setRowHeight(2, 30);
    hModel->setData(hModel->index(0, 0), QString("cell1"), Qt::DisplayRole);
    hModel->setData(hModel->index(0, 1), QString("cell2"), Qt::DisplayRole);
    hModel->setData(hModel->index(2, 1), QString("cell3"), Qt::DisplayRole);
    hModel->setData(hModel->index(2, 2), QString("cell4"), Qt::DisplayRole);
    hModel->setData(hModel->index(0, 3), QString("cell5"), Qt::DisplayRole);
    hModel->setData(hModel->index(1, 3), QString("cell5"), Qt::DisplayRole);
    hHead->setCellBackgroundColor(hModel->index(0, 0), 0xCFCFCF);
    hHead->setCellBackgroundColor(hModel->index(0, 1), 0xCFCFCF);

    auto vHead = new HRbTableHeaderView(Qt::Vertical, 4, 3);
    auto vModel = vHead->model();
    vHead->setSectionsClickable(true);
    vHead->setSpan(0, 0, 0, 3);
    vHead->setSpan(1, 0, 3, 0);
    vHead->setSpan(1, 1, 2, 0);
    vHead->setRowHeight(0, 30);
    vHead->setRowHeight(1, 30);
    vHead->setRowHeight(2, 30);
    vHead->setColumnWidth(0, 50);
    vHead->setColumnWidth(1, 50);
    vHead->setColumnWidth(2, 50);
    vModel->setData(vModel->index(0, 0), QString("cell1"), Qt::DisplayRole);
    vModel->setData(vModel->index(1, 0), QString("cell2"), Qt::DisplayRole);
    vModel->setData(vModel->index(1, 1), QString("cell3"), Qt::DisplayRole);
    vModel->setData(vModel->index(3, 1), QString("cell4"), Qt::DisplayRole);
    vModel->setData(vModel->index(1, 2), QString("cell5"), Qt::DisplayRole);
    vModel->setData(vModel->index(2, 2), QString("cell6"), Qt::DisplayRole);
    vModel->setData(vModel->index(3, 2), QString("cell7"), Qt::DisplayRole);
    vHead->setCellBackgroundColor(vModel->index(0, 0), Qt::cyan);
    vHead->setCellBackgroundColor(vModel->index(1, 0), 0xCFCFCF);

    auto dataModel = new QStandardItemModel;
    for (int i = 0; i < 4; i++)
    {
        QList<QStandardItem *> items;
        for (int j = 0; j < 4; j++)
            items.append(new QStandardItem(QString("item(%1,%2)").arg(i).arg(j)));
        dataModel->appendRow(items);
    }

    auto view = new QTableView();
    view->resize(800, 600);
    view->setModel(dataModel);
    view->setHorizontalHeader(hHead);
    view->setVerticalHeader(vHead);
    ui->tabWidget->addTab(view, tr("多标题表格1"));
}

void HDemoWidget::addMultHeaderTableWidget()
{
    auto widget1 = new QTableWidget;
    widget1->setColumnCount(2);
    widget1->setRowCount(1);
    widget1->horizontalHeader()->setStretchLastSection(true);
    widget1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    widget1->verticalHeader()->setVisible(false);
    widget1->setHorizontalHeaderLabels(QStringList() << "结果" << "球编号");

    auto widget2 = new QTableWidget;
    widget2->setColumnCount(2);
    widget2->setRowCount(1);
    widget2->horizontalHeader()->setStretchLastSection(true);
    widget2->verticalHeader()->setVisible(false);
    widget2->setHorizontalHeaderLabels(QStringList() << "结果" << "漏泄量");

    auto widget3 = new QTableWidget;
    widget3->setColumnCount(2);
    widget3->setRowCount(1);
    widget3->horizontalHeader()->setStretchLastSection(true);
    widget3->verticalHeader()->setVisible(false);
    widget3->setHorizontalHeaderLabels(QStringList() << "结果" << "漏泄量");

    auto rootWidget = new QTableWidget;
    rootWidget->setColumnCount(3);
    rootWidget->setRowCount(1);
    rootWidget->horizontalHeader()->setStretchLastSection(true);
    rootWidget->verticalHeader()->setVisible(false);
    rootWidget->verticalHeader()->setStretchLastSection(true);
    rootWidget->setHorizontalHeaderLabels(QStringList() << "过球" << "主管泄漏" << "全车泄漏");
    rootWidget->setCellWidget(0, 0, widget1);
    rootWidget->setCellWidget(0, 1, widget2);
    rootWidget->setCellWidget(0, 2, widget3);

    ui->tabWidget->addTab(rootWidget, tr("多标题表格2"));
}

void HDemoWidget::addTab(QLayout *layout, QString title)
{
    auto w = new QWidget;
    w->setLayout(layout);
    ui->tabWidget->addTab(w, title);
}

HE_CONTROL_END_NAMESPACE
