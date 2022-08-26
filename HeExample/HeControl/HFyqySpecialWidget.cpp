#include "HFyqySpecialWidget.h"
#include "ui_HFyqySpecialWidget.h"
#include "HShadeWidget.h"
#include "HControlHelper.h"
#include <QtWidgets/QDialog>

HE_BEGIN_NAMESPACE

HFyqySpecialWidget::HFyqySpecialWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HFyqySpecialWidget)
{
    ui->setupUi(this);
}

HFyqySpecialWidget::~HFyqySpecialWidget()
{
    if (_framelessWidget != nullptr)
    {
        _framelessWidget->close();
        _framelessWidget->deleteLater();
    }
    delete ui;
}

void HFyqySpecialWidget::on_pushButton_1_clicked()
{
    auto widget = new HShadeWidget(this);
    QDialog dialog(this);
    widget->addWatched(&dialog);
    dialog.setWindowTitle("遮罩层弹出窗体");
    dialog.resize(400, 300);
    dialog.exec();
}

void HFyqySpecialWidget::on_pushButton_2_clicked()
{
    if (_framelessWidget == nullptr)
    {
        _framelessWidget = new QWidget;
        _framelessWidget->setAttribute(Qt::WA_Mapped);
        HControlHelper::framelessWidget(_framelessWidget);
    }
    _framelessWidget->show();
}

HE_END_NAMESPACE
