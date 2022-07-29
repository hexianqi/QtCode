#include "HTestResultWidget_p.h"
#include "ui_HTestResultWidget.h"
#include "HeCore/HCore.h"
#include "HePlugin/HRbTableHeaderView.h"
#include <QtGui/QColor>

HE_USE_NAMESPACE

HTestResultWidgetPrivate::HTestResultWidgetPrivate()
{
    testItems = QStringList() << "[实测电压]" << "[实测电流]" << "[色温]" << "[色坐标x]" << "[色坐标y]" << "[显色指数Ra]" << "[显色指数R9]";

}

HTestResultWidget::HTestResultWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTestResultWidgetPrivate),
    ui(new Ui::HTestResultWidget)
{
    ui->setupUi(this);
    initialize();
}

HTestResultWidget::~HTestResultWidget()
{
    delete ui;
}

void HTestResultWidget::setLedType()
{
    d_ptr->ledCount = 3;
    int i, j;
    auto size = d_ptr->testItems.size();
    auto general = QStringList() << tr("BIN") << tr("POL") << tr("测试结果");
    auto labels = QList<QStringList>() << QStringList() << general;

    QList<HRbTableHeaderView *> list;
    for (i = 0; i < 2; i++)
    {
        auto prefix = labels.at(i).size();
        auto head = new HRbTableHeaderView(Qt::Horizontal, 2, prefix + d_ptr->ledCount * size, this);
        auto model = head->model();
        head->setRowHeight(0, 30);
        head->setRowHeight(1, 30);
        head->setDefaultSectionSize(65);
        head->setSectionsClickable(true);
        for (int j = 0; j < prefix; j++)
        {
            head->setSpan(0, j, 2, 1);
            head->setCellBackgroundColor(model->index(0, j), 0xFFE4C4);
            model->setData(model->index(0, j), labels.at(i).at(j), Qt::DisplayRole);
        }
        for (j = 0; j < d_ptr->ledCount; j++)
        {
            auto column = prefix + j * size;
            head->setSpan(0, column, 1, size);
            head->setCellBackgroundColor(model->index(0, column), 0xFFF5EE);
            model->setData(model->index(0, column), tr("晶%1").arg(j + 1), Qt::DisplayRole);
            for (int k = 0; k < size; k++)
            {
                model->setData(model->index(1, column + k), HCore::toCaption(d_ptr->testItems.at(k)), Qt::DisplayRole);
            }
        }
        list << head;
    }

    ui->tableWidget_2->setHorizontalHeader(list.at(0));
    ui->tableWidget_3->setHorizontalHeader(list.at(1));
}

void HTestResultWidget::clearResult()
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_3->clearContents();
    ui->tableWidget_3->setRowCount(0);
    ui->tableWidget_4->clearContents();
}

void HTestResultWidget::initialize()
{
    QString qss = "QHeaderView::section, QTableCornerButton::section \
                  { margin:0px; \
                    color:black; \
                    border:1px solid #CDC0B0; \
                    border-left-width:0px; \
                    border-right-width:1px; \
                    border-top-width:0px; \
                    border-bottom-width:1px; \
                    background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #FFFAFA, stop:1 #FFF5EE); }";

    ui->tableWidget_2->setMinimumHeight(260);
    ui->tableWidget_2->setVerticalHeaderLabels(QStringList() << tr("最大值") << tr("最小值") << tr("平均值") << tr("合格数量") << tr("合格占比"));
    ui->tableWidget_2->setStyleSheet(qss);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidget_4->setMinimumWidth(190);
    ui->tableWidget_4->setHorizontalHeaderLabels(QStringList() << tr("BIN") << tr("数量") << tr("占比(%)"));
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->splitter_1->setStretchFactor(2, 3);
    ui->splitter_2->setStretchFactor(0, 3);
    ui->splitter_2->setStretchFactor(1, 1);
    setLedType();
}


