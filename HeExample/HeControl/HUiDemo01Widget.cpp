#include "HUiDemo01Widget_p.h"
#include "ui_HUiDemo01Widget.h"
#include "HIconFontFactory.h"
#include "HIconFontStyle.h"
#include "HQssStyle.h"
#include <QtWidgets/QStyle>

HE_BEGIN_NAMESPACE

HUiDemo01Widget::HUiDemo01Widget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HUiDemo01WidgetPrivate),
    ui(new Ui::HUiDemo01Widget)
{
    ui->setupUi(this);
    initForm();
    initStyle();
    initLeftMain();
    initLeftConfig();
}

HUiDemo01Widget::~HUiDemo01Widget()
{
    delete ui;
}

void HUiDemo01Widget::initForm()
{
    auto widgetFont = this->font();
    widgetFont.setPixelSize(25);
    d_ptr->style = new HIconFontStyle(this);
    d_ptr->style->setIcon(ui->labIco, 0xf073, 30);
    d_ptr->style->setIcon(ui->btnMin, 0xf068);
    d_ptr->style->setIcon(ui->btnMax, 0xf067);
    d_ptr->style->setIcon(ui->btnClose, 0xf00d);
    ui->labTitle->setFont(widgetFont);
    ui->labTitle->setText("智能访客管理平台");
    ui->btnMain->setIcon(QIcon(":/Resources/image/main.png"));
    ui->btnConfig->setIcon(QIcon(":/Resources/image/config.png"));
    ui->btnData->setIcon(QIcon(":/Resources/image/find.png"));
    ui->btnHelp->setIcon(QIcon(":/Resources/image/help.png"));
    ui->btnExit->setIcon(QIcon(":/Resources/image/main.png"));
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTitle->installEventFilter(this);
    ui->widgetTop->setProperty("nav", "top");
    ui->widgetLeftMain->setProperty("flag", "left");
    ui->widgetLeftConfig->setProperty("flag", "left");
    ui->stackedWidget->setStyleSheet("QLabel{font:60px;}");
    ui->page1->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(60));
    ui->page2->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(25));
    setProperty("form", true);
    setProperty("canMove", true);
    setWindowTitle(ui->labTitle->text());
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
}

void HUiDemo01Widget::initStyle()
{
    auto style = new HQssStyle(this);
    style->selectStyle(tr("黑色风格1"));
    setPalette(style->toPalette());
    setStyleSheet(style->toStyleSheet());
    d_ptr->border = style->color("HighColor:");
    d_ptr->normalBackground = style->color("NormalColorStart:");
    d_ptr->normalText = style->color("TextColor:");
    d_ptr->darkBackground = style->color("PanelColor:");
    d_ptr->darkText = style->color("TextColor:");
}

void HUiDemo01Widget::initLeftMain()
{
    auto icons = QList<QChar>() << 0xf030 << 0xf03e << 0xf247;
    d_ptr->btnMain << ui->tbtnMain1 << ui->tbtnMain2 << ui->tbtnMain3;
    for (auto btn : d_ptr->btnMain)
        connect(btn, &QToolButton::clicked, this, &HUiDemo01Widget::leftMainClick);
    HIconFontStyle::StyleColor styleColor;
    styleColor.position = "left";
    styleColor.iconPixelSize = 18;
    styleColor.iconImageSize = QSize(35, 25);
    styleColor.borderWidth = 4;
    styleColor.borderColor = d_ptr->border.name();
    styleColor.setColor(d_ptr->normalBackground.name(), d_ptr->normalText.name(), d_ptr->darkBackground.name(), d_ptr->darkText.name());
    d_ptr->style->setStyle(ui->widgetLeftMain, d_ptr->btnMain, icons, styleColor);
    ui->tbtnMain1->click();
}

void HUiDemo01Widget::initLeftConfig()
{
    auto icons = QList<QChar>() << 0xf031 << 0xf036 << 0xf249 << 0xf055 << 0xf05a << 0xf249;
    d_ptr->btnConfig << ui->tbtnConfig1 << ui->tbtnConfig2 << ui->tbtnConfig3 << ui->tbtnConfig4 << ui->tbtnConfig5 << ui->tbtnConfig6;
    for (auto btn : d_ptr->btnConfig)
        connect(btn, &QToolButton::clicked, this, &HUiDemo01Widget::leftConfigClick);
    HIconFontStyle::StyleColor styleColor;
    styleColor.position = "left";
    styleColor.iconPixelSize = 16;
    styleColor.iconImageSize = QSize(20, 20);
    styleColor.borderWidth = 3;
    styleColor.borderColor = d_ptr->border.name();
    styleColor.setColor(d_ptr->normalBackground.name(), d_ptr->normalText.name(), d_ptr->darkBackground.name(), d_ptr->darkText.name());
    d_ptr->style->setStyle(ui->widgetLeftConfig, d_ptr->btnConfig, icons, styleColor);
    ui->tbtnConfig1->click();
}

void HUiDemo01Widget::leftMainClick()
{
    auto b = qobject_cast<QAbstractButton *>(sender());
    if (b == nullptr)
        return;
    for (auto btn : d_ptr->btnMain)
        btn->setChecked(btn == b);
    ui->lab1->setText(b->text());
}

void HUiDemo01Widget::leftConfigClick()
{
    auto b = qobject_cast<QAbstractButton *>(sender());
    if (b == nullptr)
        return;
    for (auto btn : d_ptr->btnConfig)
        btn->setChecked(btn == b);
    ui->lab2->setText(b->text());
}

void HUiDemo01Widget::on_btnMain_clicked()
{
    auto btns = ui->widgetTop->findChildren<QAbstractButton *>();
    for (auto btn : btns)
        btn->setChecked(btn == ui->btnMain);
    ui->stackedWidget->setCurrentIndex(0);
}

void HUiDemo01Widget::on_btnConfig_clicked()
{
    auto btns = ui->widgetTop->findChildren<QAbstractButton *>();
    for (auto btn : btns)
        btn->setChecked(btn == ui->btnConfig);
    ui->stackedWidget->setCurrentIndex(1);
}

void HUiDemo01Widget::on_btnData_clicked()
{
    auto btns = ui->widgetTop->findChildren<QAbstractButton *>();
    for (auto btn : btns)
        btn->setChecked(btn == ui->btnData);
    ui->stackedWidget->setCurrentIndex(2);
}

void HUiDemo01Widget::on_btnHelp_clicked()
{
    auto btns = ui->widgetTop->findChildren<QAbstractButton *>();
    for (auto btn : btns)
        btn->setChecked(btn == ui->btnHelp);
    ui->stackedWidget->setCurrentIndex(3);
}

void HUiDemo01Widget::on_btnExit_clicked()
{
    exit(0);
}

void HUiDemo01Widget::on_btnMin_clicked()
{
    showMinimized();
}

void HUiDemo01Widget::on_btnMax_clicked()
{
    d_ptr->max = !d_ptr->max;
    if (d_ptr->max)
        showMaximized();
    else
        showNormal();
    setProperty("canMove", !d_ptr->max);
}

void HUiDemo01Widget::on_btnClose_clicked()
{
    close();
}

bool HUiDemo01Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->widgetTitle)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
            on_btnMax_clicked();
    }
    return QWidget::eventFilter(watched, event);
}

HE_END_NAMESPACE
