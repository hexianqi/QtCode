#include "HControlDemoWidget_p.h"
#include "HNavigationWidget.h"
#include "HLightButton.h"
#include "HNavButton.h"
#include "HDiskSizeTable.h"
#include "HStyleWidget.h"
#include "HFlatStyleWidget.h"
#include "HQssCreator.h"
#include "HIconFontWidget.h"
#include "HSpliteWidget.h"
#include "HCodeCountWidget.h"
#include "HNetworkWidget.h"
#include "HRbTableHeaderView.h"
#include "HIconFontFactory.h"
#include "HDrawHelper.h"
#include <QtGui/QPen>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QGridLayout>
#include <QtGui/QStandardItemModel>

HE_CONTROL_BEGIN_NAMESPACE

HControlDemoWidget::HControlDemoWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HControlDemoWidgetPrivate)
{
    init();
}

HControlDemoWidget::HControlDemoWidget(HControlDemoWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HControlDemoWidget::~HControlDemoWidget()
{
}

void HControlDemoWidget::init()
{
    d_ptr->iconFacuory = new HIconFontFactory(this);
    initWidget();
    addLiuDianWu();
    addStyle();
    addTool();
    addElse();
}

void HControlDemoWidget::initWidget()
{
    auto layout = new QGridLayout(this);
    auto splitter = new QSplitter;
    auto nav = new HNavigationWidget;
    auto stacked = new QStackedWidget;    
    auto keys = QStringList() << tr("ludianwu") << tr("ww") << tr("DEMO") << tr("工具") << tr("其他");

    for (auto key : keys)
    {
        auto w = new QTabWidget;
        stacked->addWidget(w);
        nav->addItem(key);
        d_ptr->tabWidgets.insert(key, w);
    }

    splitter->addWidget(nav);
    splitter->addWidget(stacked);
    layout->addWidget(splitter);
    connect(nav, &HNavigationWidget::currentItemChanged, stacked, &QStackedWidget::setCurrentIndex);
    resize(1000, 800);
}

void HControlDemoWidget::addLiuDianWu()
{
    addLightButton();
    addNavButton();
    addExplorer();
}

void HControlDemoWidget::addStyle()
{
    addTab(tr("DEMO"), "Style", new HStyleWidget);
    addTab(tr("DEMO"), "Flat", new HFlatStyleWidget);
    addTab(tr("DEMO"), "Qss", new HQssCreator);
    addTab(tr("DEMO"), tr("字体图标"), new HIconFontWidget);
    addTab(tr("DEMO"), tr("分割界面"), new HSpliteWidget);
}

void HControlDemoWidget::addTool()
{
    addTab(tr("工具"), new HCodeCountWidget);
    addTab(tr("工具"), new HNetworkWidget);
}

void HControlDemoWidget::addElse()
{
    addMultHeaderTableView();
    addMultHeaderTableWidget();
}

void HControlDemoWidget::addLightButton()
{
    auto layout = new QHBoxLayout;
    auto lightButton1 = new HLightButton;
    auto lightButton2 = new HLightButton;
    auto lightButton3 = new HLightButton;
    lightButton2->setBackground(QColor(255, 107, 107));
    lightButton3->setBackground(QColor(24, 189, 155));
    layout->addWidget(lightButton1);
    layout->addWidget(lightButton2);
    layout->addWidget(lightButton3);
    addTab(tr("ludianwu"), tr("发光按钮"), layout);
}

void HControlDemoWidget::addNavButton()
{
    auto layout = new QGridLayout;
    auto layout1 = new QVBoxLayout;
    auto layout2 = new QVBoxLayout;
    auto layout3 = new QVBoxLayout;
    auto layout4 = new QVBoxLayout;
    auto layout5 = new QHBoxLayout;
    auto layout6 = new QHBoxLayout;
    auto iconFont = d_ptr->iconFacuory->createFont("FontAwesome");
    iconFont.setPixelSize(15);
    QFont font;
    font.setPixelSize(15);
    font.setBold(true);

    auto list1 = QStringList() << tr("学生管理") << tr("教师管理") << tr("成绩管理") << tr("记录查询");
    auto list2 = QStringList() << tr("首页") << tr("作品") << tr("论坛") << tr("群组") << tr("帮助");
    auto chars = QList<QChar>() << 0xf17b << 0xf002 << 0xf013 << 0xf021 << 0xf0e0 << 0xf135;

    // 例1
    {
        auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf061, QSize(15, 15), QColor("#646464")));
        auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf061, QSize(15, 15), QColor("#FFFFFF")));
        auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf061, QSize(15, 15), QColor("#FFFFFF")));
        for (int i = 0; i < list1.size(); i++)
        {
            auto button = new HNavButton;
            button->setText(list1[i]);
            button->setPaddingLeft(32);
            button->setLineSpace(6);
            button->setShowIcon(true);
            button->setIconSpace(15);
            button->setIconSize(QSize(10, 10));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            layout1->addWidget(button);
        }
    }
    // 例2
    {
        auto normalBackground = QColor("#2D9191");
        auto hoverBackground = QColor("#187294");
        auto checkBackground = QColor("#145C75");
        auto normalTextColor = QColor("#FFFFFF");
        auto hoverTextColor = QColor("#FFFFFF");
        auto checkTextColor = QColor("#FFFFFF");
        for (int i = 0; i < list1.size(); i++)
        {
            auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), normalTextColor));
            auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), hoverTextColor));
            auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), checkTextColor));
            auto button = new HNavButton;
            button->setText(list1[i]);
            button->setPaddingLeft(35);
            button->setLineSpace(0);
            button->setLineWidth(8);
            button->setLineColor(QColor(255, 107, 107));
            button->setShowTriangle(true);
            button->setShowIcon(true);
            button->setIconSpace(10);
            button->setIconSize(QSize(22, 22));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            button->setNormalBackground(normalBackground);
            button->setHoverBackground(hoverBackground);
            button->setCheckBackground(checkBackground);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            layout2->addWidget(button);
        }
    }
    // 例3
    {
        auto normalBackground = QColor("#292F38");
        auto hoverBackground = QColor("#1D2025");
        auto checkBackground = QColor("#1D2025");
        auto normalTextColor = QColor("#54626F");
        auto hoverTextColor = QColor("#FDFDFD");
        auto checkTextColor = QColor("#FDFDFD");
        for (int i = 0; i < list1.size(); i++)
        {
            auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), normalTextColor));
            auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), hoverTextColor));
            auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), checkTextColor));
            auto button = new HNavButton;
            button->setText(list1[i]);
            button->setPaddingLeft(35);
            button->setLineWidth(10);
            button->setLineColor(QColor("#029FEA"));
            button->setShowTriangle(true);
            button->setTextAlign(Qt::AlignLeft);
            button->setTrianglePosition(HNavButton::PositionLeft);
            button->setLinePosition(HNavButton::PositionRight);
            button->setShowIcon(true);
            button->setIconSpace(10);
            button->setIconSize(QSize(22, 22));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            button->setNormalBackground(normalBackground);
            button->setHoverBackground(hoverBackground);
            button->setCheckBackground(checkBackground);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            layout3->addWidget(button);
        }
    }
    // 例4
    {
        auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf105, QSize(15, 15), QColor("#646464")));
        auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf105, QSize(15, 15), QColor("#FFFFFF")));
        auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, 0xf105, QSize(15, 15), QColor("#FFFFFF")));
        for (int i = 0; i < list1.size(); i++)
        {
            auto button = new HNavButton;
            button->setText(list1[i]);
            button->setLineSpace(10);
            button->setLineWidth(10);
            button->setPaddingRight(25);
            button->setShowTriangle(true);
            button->setTextAlign(Qt::AlignRight);
            button->setTrianglePosition(HNavButton::PositionLeft);
            button->setLinePosition(HNavButton::PositionRight);
            button->setShowIcon(true);
            button->setIconSpace(25);
            button->setIconSize(QSize(15, 15));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            layout4->addWidget(button);
        }
    }
    // 例5
    {
        auto normalBackground = QColor("#292929");
        auto hoverBackground = QColor("#064077");
        auto checkBackground = QColor("#10689A");
        auto normalTextColor = QColor("#FFFFFF");
        auto hoverTextColor = QColor("#FFFF00");
        auto checkTextColor = QColor("#FFFFFF");
        for (int i = 0; i < list2.size(); i++)
        {
            auto iconNormal = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), normalTextColor));
            auto iconHover = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), hoverTextColor));
            auto iconCheck = QPixmap::fromImage(HDrawHelper::createFontImage(iconFont, chars[i], QSize(20, 20), checkTextColor));
            auto button = new HNavButton;
            button->setText(list2[i]);
            button->setFont(font);
            button->setPaddingLeft(20);
            button->setShowLine(false);
            button->setTextAlign(Qt::AlignCenter);
            button->setLinePosition(HNavButton::PositionBottom);
            button->setShowIcon(true);
            button->setIconSpace(15);
            button->setIconSize(QSize(22, 22));
            button->setIconNormal(iconNormal);
            button->setIconHover(iconHover);
            button->setIconCheck(iconCheck);
            button->setNormalBackground(normalBackground);
            button->setHoverBackground(hoverBackground);
            button->setCheckBackground(checkBackground);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            layout5->addWidget(button);
        }
    }
    // 例6
    {
        auto gradient1 = QLinearGradient(0, 0, 0, 30);
        gradient1.setColorAt(0.0, QColor("#3985BF"));
        gradient1.setColorAt(0.5, QColor("#2972A9"));
        gradient1.setColorAt(1.0, QColor("#1C6496"));
        auto gradient2 = QLinearGradient(0, 0, 0, 30);
        gradient2.setColorAt(0.0, QColor("#4897D1"));
        gradient2.setColorAt(0.5, QColor("#3283BC"));
        gradient2.setColorAt(1.0, QColor("#3088C3"));
        auto normalTextColor = QColor("#FFFFFF");
        auto hoverTextColor = QColor("#FFFF00");
        auto checkTextColor = QColor("#FFFFFF");
        for (int i = 0; i < list2.size(); i++)
        {
            auto button = new HNavButton;
            button->setText(list2[i]);
            button->setFont(font);
            button->setPaddingLeft(0);
            button->setLineSpace(0);
            button->setShowTriangle(true);
            button->setTextAlign(Qt::AlignCenter);
            button->setTrianglePosition(HNavButton::PositionBottom);
            button->setLinePosition(HNavButton::PositionTop);
            button->setNormalTextColor(normalTextColor);
            button->setHoverTextColor(hoverTextColor);
            button->setCheckTextColor(checkTextColor);
            button->setNormalBackgroundBrush(gradient1);
            button->setHoverBackgroundBrush(gradient2);
            button->setCheckBackgroundBrush(gradient2);
            layout6->addWidget(button);
        }
    }
    layout->addLayout(layout1, 0, 0);
    layout->addLayout(layout2, 0, 1);
    layout->addLayout(layout3, 0, 2);
    layout->addLayout(layout4, 0, 3);
    layout->addLayout(layout5, 1, 0, 1, 4);
    layout->addLayout(layout6, 2, 0, 1, 4);
    layout->addItem(new QSpacerItem(20, 20), 3, 0, 1, 4);
    addTab(tr("ludianwu"), tr("导航按钮"), layout);
}

void HControlDemoWidget::addExplorer()
{
    auto layout = new QGridLayout;
//    auto w = new HCpuMemoryLabel();
    auto table = new HDiskSizeTable();
//    w->setFont(QFont("Microsoft Yahei", 13));
//    w->setStyleSheet("QLabel{ background-color: #000000; color: #64B8FF; }");
//    w->start(1500);
//    layout->addWidget(w, 0, 0);
    layout->addWidget(table, 1, 0);
    addTab(tr("ludianwu"), tr("资源管理器"), layout);
}

void HControlDemoWidget::addMultHeaderTableView()
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
    addTab(tr("其他"), tr("多标题表格1"), view);
}

void HControlDemoWidget::addMultHeaderTableWidget()
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

    addTab(tr("其他"), tr("多标题表格2"), rootWidget);
}

void HControlDemoWidget::addTab(QString key, QWidget *w)
{
    addTab(key, w->windowTitle(), w);
}

void HControlDemoWidget::addTab(QString key, QString title, QWidget *w)
{
    if (d_ptr->tabWidgets.contains(key))
        d_ptr->tabWidgets[key]->addTab(w, title);
}

void HControlDemoWidget::addTab(QString key, QString title, QLayout *layout)
{
    auto w = new QWidget;
    w->setLayout(layout);
    addTab(key, title, w);
}

HE_CONTROL_END_NAMESPACE
