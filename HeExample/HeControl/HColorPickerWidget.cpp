#include "HColorPickerWidget.h"
#include "ui_HColorPickerWidget.h"
#include "HControlHelper.h"
#include <QtCore/QTimer>
#include <QtWidgets/QDesktopWidget>
#include <QtGui/QScreen>
#include <QtGui/QIcon>

HE_CONTROL_BEGIN_NAMESPACE

HColorPickerWidget::HColorPickerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HColorPickerWidget)
{
    ui->setupUi(this);
    init();
}

HColorPickerWidget::~HColorPickerWidget()
{
    delete ui;
}

void HColorPickerWidget::showColorValue()
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();

    auto pixmap = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId(), x, y, 2, 2);
    if (pixmap.isNull())
        return;
    auto image = pixmap.toImage();
    if (image.isNull() || !image.valid(0, 0))
        return;
    auto color = image.pixelColor(0, 0);
    ui->lineEdit_1->setText(color.name().toUpper());
    ui->lineEdit_2->setText(QString("%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue()));
    ui->lineEdit_3->setText(QString("X:%1  Y:%2").arg(x).arg(y));
    ui->lable_4->setStyleSheet(QString("background-color: %1;").arg(color.name()));
}

void HColorPickerWidget::init()
{
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &HColorPickerWidget::showColorValue);
    _timer->start(200);

    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    setWindowIcon(QIcon(":/image/ColorPicker.ico"));
    HControlHelper::centerWidget(this);
}

HE_CONTROL_END_NAMESPACE
