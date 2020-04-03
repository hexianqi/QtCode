#include "HColorPicker.h"
#include "ui_HColorPicker.h"
#include "HControlHelper.h"
#include <QtCore/QTimer>
#include <QtWidgets/QDesktopWidget>
#include <QtGui/QScreen>
#include <QtGui/QIcon>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HColorPicker::HColorPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HColorPicker)
{
    ui->setupUi(this);
    init();
}

HColorPicker::~HColorPicker()
{
    if (_timer->isActive())
        _timer->stop();
    delete ui;
}

void HColorPicker::showColorValue()
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

void HColorPicker::init()
{
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &HColorPicker::showColorValue);
    _timer->start(200);

    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);
    setWindowIcon(QIcon(":/image/tools/ColorPicker.ico"));
    setWindowTitle("屏幕拾色器");
    HControlHelper::centerWidget(this);
}

HE_CONTROL_END_NAMESPACE
