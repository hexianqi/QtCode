#include "HDemoWidget_p.h"
#include "ui_HDemoWidget.h"
#include "HFlatStyle.h"
#include "HAntLine.h"
#include "HTiledBackground.h"
#include "HBattery.h"
#include "HMultiStyleButton.h"
#include "HLightButton.h"
#include "HSwitchButton.h"
#include "HButtonColorPanel.h"
#include "HCpuMemoryLabel.h"
#include "HDiskSizeTable.h"
#include "HCustomGraphics.h"
#include "HArcGauge.h"
#include "HCarGauge.h"
#include "HClockGauge.h"
#include "HCompassGauge.h"
#include "HMiniGauge.h"
#include "HKnobGauge.h"
#include "HPanelGauge.h"
#include "HPercentGauge.h"
#include "HSpeedGauge.h"
#include "HWeatherGauge.h"
#include "HImageCalendar.h"
#include "HLedNumber.h"
#include "HLightPoint.h"
#include "HMagicFish.h"
#include "HMagicMouse.h"
#include "HNavButton.h"
#include "HNavLabel.h"
#include "HPanelItem.h"
#include "HButtonProgressBar.h"
#include "HColorProgressBar.h"
#include "HRingProgressBar.h"
#include "HRoundProgressBar.h"
#include "HTristateProgressBar.h"
#include "HStateProgressBar.h"
#include "HRbTableHeaderView.h"
#include "HBarRuler.h"
#include "HThermometerRuler.h"
#include "HSlideNavigation.h"

#include "HButtonLineEdit.h"
#include "HClearLineEdit.h"
#include "HResetLineEdit.h"
#include "HFileChooser.h"
#include "HColorButton.h"
#include "HRichTextButton.h"
#include "HColorComboBox.h"
#include "HTwoColorIndicator.h"
#include "HHueSatPicker.h"
#include "HHueSatRadialPicker.h"
#include "HLedWidget.h"
#include "HNavigationSlider.h"
#include "HLongSpinBox.h"
#include "HTextSpinBox.h"
#include "HNumPad.h"
#include "HRichTextEdit.h"
#include "HConfigPanel.h"
#include "HTaskPanel.h"
#include "HNavigationPanel.h"

#include <QtCore/QTimer>
#include <QtCore/QRandomGenerator>
#include <QtWidgets/QTableWidget>
#include <QtGui/QStandardItemModel>


HE_BEGIN_NAMESPACE

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
    d_ptr->style = new HFlatStyle(this);

//    addSlideNavigation();
    addAntLine();
    addBackground();
    addButton();
    addColorPanel();
    addCpuMemoryLabel();
    addCustomGraphics();
    addGauge();
    addImageCalendar();
    addLedNumber();
    addLightPoint();
    addMagic();

    addNav();
    addPanel();
    addProgressBar();
    addRuler();

    addww();
}

void HDemoWidget::addAntLine()
{
    auto l = new QGridLayout;
    auto w1 = new HAntLine;
    w1->setLineSpeed(500);
    auto w2 = new HAntLine;
    w2->setLineStyle(HAntLine::LineStyle_RoundedRect);
    w2->setLength(10);
    auto w3 = new HAntLine;
    w3->setLineStyle(HAntLine::LineStyle_Ellipse);
    w3->setLineColor(Qt::red);
    auto w4 = new HAntLine;
    w4->setLineStyle(HAntLine::LineStyle_Circle);
    w4->setLineWidth(5);
    l->addWidget(w1, 0, 0);
    l->addWidget(w2, 0, 1);
    l->addWidget(w3, 1, 0);
    l->addWidget(w4, 1, 1);
    addTab(l, tr("蚂蚁线"));
}

void HDemoWidget::addBackground()
{
    ui->tabWidget->addTab(new HTiledBackground, tr("背景"));
}

void HDemoWidget::addButton()
{
    auto l = new QGridLayout;
    auto cb = new HMultiStyleButton;
    auto lb = new HLightButton;
    auto sb1 = new HSwitchButton;
    auto sb2 = new HSwitchButton;
    auto sb3 = new HSwitchButton;
    sb1->setButtonStyle(HSwitchButton::ButtonStyle_Rect);
    sb2->setButtonStyle(HSwitchButton::ButtonStyle_CircleIn);
    sb3->setButtonStyle(HSwitchButton::ButtonStyle_CircleOut);
    l->addWidget(cb, 0, 0);
    l->addWidget(lb, 0, 1);
    l->addWidget(sb1, 1, 0);
    l->addWidget(sb2, 1, 1);
    l->addWidget(sb3, 1, 2);
    addTab(l, tr("按钮"));
}

void HDemoWidget::addColorPanel()
{
    auto l = new QGridLayout;
    auto cp = new HButtonColorPanel;
    auto la = new QLabel;
    la->setMinimumWidth(30);
    l->addWidget(cp, 0, 0);
    l->addWidget(la, 0, 1);
    connect(cp, &HButtonColorPanel::colorPicked, this, [=](QColor color) { la->setStyleSheet(QString("background:%1;").arg(color.name())); });
    addTab(l, tr("颜色面板"));
}

void HDemoWidget::addCpuMemoryLabel()
{
    auto l = new QGridLayout;
    auto w = new HCpuMemoryLabel();
    auto d = new HDiskSizeTable();
    w->setFont(QFont("Microsoft Yahei", 13));
    w->setStyleSheet("QLabel{ background-color: #000000; color: #64B8FF; }");
    w->start(1500);
    l->addWidget(w, 0, 0);
    l->addWidget(d, 1, 0);
    addTab(l, tr("资源管理器"));
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

void HDemoWidget::addCustomGraphics()
{
    ui->tabWidget->addTab(new HCustomGraphics, tr("自定义多边形"));
}

void HDemoWidget::addGauge()
{
    auto l = new QGridLayout;
    auto c = new QComboBox;
    auto s = new QSlider;
    auto arc = new HArcGauge;
    auto car = new HCarGauge;
    auto clock = new HClockGauge;
    auto knob = new HKnobGauge;
    auto mini = new HMiniGauge;
    auto panel = new HPanelGauge;
    auto percent = new HPercentGauge;
    auto speed = new HSpeedGauge;
    auto compass = new HCompassGauge;
    auto weather = new HWeatherGauge;

    c->addItems(QStringList() << tr("圆形指示器") << tr("指针指示器") << tr("圆角指针指示器") << tr("三角形指示器"));
    s->setOrientation(Qt::Horizontal);
    s->setSingleStep(10);
    connect(c, &QComboBox::currentTextChanged, this, [=](QString /*index*/) {
        arc->setPointerStyle(static_cast<HControlType::PointerStyle>(c->currentIndex()));
        car->setPointerStyle(static_cast<HControlType::PointerStyle>(c->currentIndex()));
        knob->setPointerStyle(static_cast<HControlType::PointerStyle>(c->currentIndex()));
        mini->setPointerStyle(static_cast<HControlType::PointerStyle>(c->currentIndex()));
    });
    connect(s, &QSlider::valueChanged, this, [=](int value) {
        arc->setValue(value);
        car->setValue(value);
        knob->setValue(value);
        mini->setValue(value);
        panel->setValue(value);
        percent->setValue(value);
        speed->setValue(value);
        compass->setValue(value * 3.6);
        weather->setValue(value - 50);});

    l->addWidget(arc, 0, 0);
    l->addWidget(car, 0, 1);
    l->addWidget(knob, 0, 2);
    l->addWidget(mini, 0, 3);
    l->addWidget(panel, 1, 0);
    l->addWidget(percent, 1, 1);
    l->addWidget(speed, 1, 2);
    l->addWidget(weather, 1, 3);
    l->addWidget(compass, 2, 1);
    l->addWidget(clock, 2, 2);
    l->addWidget(c, 3, 0, 1, 2);
    l->addWidget(s, 4, 0, 1, 4);
    addTab(l, tr("仪表盘"));
}

void HDemoWidget::addImageCalendar()
{
    ui->tabWidget->addTab(new HImageCalendar, tr("日历"));
}

void HDemoWidget::addLedNumber()
{
    ui->tabWidget->addTab(new HLedNumber, tr("LED"));
}

void HDemoWidget::addLightPoint()
{
    ui->tabWidget->addTab(new HLightPoint, tr("闪灯"));
}

void HDemoWidget::addMagic()
{
    auto l = new QGridLayout;
    auto f = new HMagicFish;
    auto m = new HMagicMouse;
    auto s = new QSlider;
    s->setOrientation(Qt::Horizontal);
    s->setSingleStep(10);
    s->setRange(0, 360);
    connect(s, &QSlider::valueChanged, f, &HMagicFish::setAngle);
    connect(s, &QSlider::valueChanged, m, &HMagicMouse::setAngle);
    l->addWidget(f, 0, 0);
    l->addWidget(m, 0, 1);
    l->addWidget(s, 1, 0, 1, 2);
    addTab(l, tr("魔法"));
}

void HDemoWidget::addProgressBar()
{
    auto l = new QGridLayout;
    auto s = new QSlider;
    auto bpb = new HButtonProgressBar;
    auto cpb = new HColorProgressBar;
    auto rpb = new HRingProgressBar;
    auto opb = new HRoundProgressBar;
    auto tpb = new HTristateProgressBar;
    auto spb = new HStateProgressBar;

    s->setOrientation(Qt::Horizontal);
    s->setSingleStep(10);

    cpb->setTextPosition(HColorProgressBar::TextPosition_OnBar);
    cpb->setBarStyle(HColorProgressBar::BarStyle_Gradual);
    cpb->setDecimal(1);
    cpb->setBarBackColor(QColor(250, 250, 250));
    cpb->setTextForeColor(Qt::white);
    cpb->setTextBackColor(QColor(24, 189, 155));
    cpb->setBarForeDataColors(QGradientStops() << QGradientStop(0, Qt::green) << QGradientStop(0.5, Qt::yellow) << QGradientStop(1, Qt::red));
    cpb->setFixedHeight(60);

    rpb->setAlarmMode(2);

    spb->setNotes(QStringList() << "a" << "b" << "c" << "d" << "e");
    spb->setStates(QStringList() << "A" << "B" << "C" << "D" << "E");

    connect(s, &QSlider::valueChanged, this, [=](int value) {
        cpb->setValue(value);
        rpb->setValue(value);
        opb->setValue(value);
        tpb->setValue1(value);
        tpb->setValue2(value + 10);
        tpb->setValue3(value + 20);
        spb->setValue(value / 10);  });
    l->addWidget(bpb, 0, 0);
    l->addWidget(cpb, 0, 1);
    l->addWidget(rpb, 0, 2);
    l->addWidget(opb, 1, 0);
    l->addWidget(tpb, 1, 1, 1, 2);
    l->addWidget(spb, 2, 0, 1, 3);
    l->addWidget(s, 3, 0, 1, 3);
    addTab(l, tr("进度条"));
}

void HDemoWidget::addNav()
{
    auto l = new QGridLayout;
    auto nb = new HNavButton;
    auto nl = new HNavLabel;
    nb->setText(tr("导航按钮"));
    nl->setText(tr("导航标签"));
    l->addWidget(nb, 0, 0);
    l->addWidget(nl, 0, 1);
    addTab(l, tr("导航"));
}

void HDemoWidget::addPanel()
{
    ui->tabWidget->addTab(new HPanelItem, tr("面板"));
}

void HDemoWidget::addRuler()
{
    auto l = new QGridLayout;
    auto b = new HBarRuler;
    auto t = new HThermometerRuler;
    auto timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, &QTimer::timeout, this, [=] {
        b->setValue(QRandomGenerator::global()->bounded(100));
        t->setValue(QRandomGenerator::global()->bounded(100)); });
    timer->start();
    l->addWidget(b, 0, 0);
    l->addWidget(t, 0, 1);
    addTab(l, tr("标尺"));
}

void HDemoWidget::addww()
{
    auto l = new QGridLayout;
    auto ble = new HButtonLineEdit;
    auto cle = new HClearLineEdit;
    auto rle = new HResetLineEdit;
    auto fl = new HFileChooser;
    auto cb = new HColorButton;
    auto rb = new HRichTextButton;
    auto ccb = new HColorComboBox;
    auto hsp = new HHueSatPicker;
    auto hsr = new HHueSatRadialPicker;
    auto led = new HLedWidget;
    auto tci = new HTwoColorIndicator;
    auto ln = new HNavigationSlider;
    auto np = new HNumPad;
    auto rte = new HRichTextEdit;
    auto lsb = new HLongSpinBox;
    auto tsb = new HTextSpinBox;
    tsb->setItems(QStringList() << "a" << "d" << "b" << "dsad" << "csss");
//    auto mw = new HConfigWidget;
//    auto mw = new HNavigationBar;
    auto mw = new HTaskPanel;

    mw->addWidget(hsp, hsp->windowIcon(), tr("颜色拾取器"));
    mw->addWidget(hsr, hsr->windowIcon(), tr("颜色拾取器2"));
    mw->addWidget(np, np->windowIcon(), tr("数字面板"));
    mw->addWidget(rte, rte->windowIcon(), tr("富文本编辑器"));
    connect(cb, &HColorButton::colorPicked, this, [=](const QColor &value) {
        hsp->setColor(value);
        hsr->setColor(value); });

    l->addWidget(ble, 0, 0);
    l->addWidget(cle, 0, 1);
    l->addWidget(rle, 1, 0);
    l->addWidget(fl, 1, 1);
    l->addWidget(cb, 2, 0);
    l->addWidget(rb, 2, 1);
    l->addWidget(ccb, 2, 2);
    l->addWidget(led, 3, 0);
    l->addWidget(tci, 3, 1);
    l->addWidget(lsb, 4, 1);
    l->addWidget(tsb, 4, 2);
    l->addWidget(ln, 5, 0, 1, 3);
    l->addWidget(mw, 6, 0, 1, 3);
    addTab(l, tr("ww"));
}

void HDemoWidget::addTab(QLayout *layout, const QString &title)
{
    auto w = new QWidget;
    w->setLayout(layout);
    ui->tabWidget->addTab(w, title);
}

HE_END_NAMESPACE
