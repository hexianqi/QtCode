#include "HTestWidget3000_p.h"
#include "ui_HTestWidget3000.h"
#include "HeCore/HCore.h"
#include "HePlugin/HRbTableHeaderView.h"

HE_USE_NAMESPACE

HTestWidget3000Private::HTestWidget3000Private()
{
    displays = QStringList() << "[实测电压]" << "[实测电流]" << "[色温]" << "[色坐标x]" << "[色坐标y]" << "[显色指数Ra]" << "[显色指数R9]";

}

HTestWidget3000::HTestWidget3000(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTestWidget3000Private),
    ui(new Ui::HTestWidget3000)
{
    ui->setupUi(this);
    initialize();
}

HTestWidget3000::~HTestWidget3000()
{
    delete ui;
}

void HTestWidget3000::setLedType()
{
//    d_ptr->ledCount = 3;
//    auto size = d_ptr->displays.size();
//    QList<HRbTableHeaderView *> header;
//    for (int i = 0; i < 2; i++)
//    {
//        auto head = new HRbTableHeaderView(Qt::Horizontal, 2, d_ptr->ledCount * size);
//        auto model = head->model();
//        head->setSpan(0, 0, 2, 0);
//        head->setSectionsClickable(true);
//        for (int j = 0; j < d_ptr->ledCount; j++)
//        {
//            head->setRowHeight(0, 30);
//            head->setSpan(0, j * size + 1, 1, size);
//            head->setCellBackgroundColor(model->index(0, j * size), 0xCFCFCF);
//            model->setData(model->index(0, j * size + 1), tr("晶%1").arg(j + 1), Qt::DisplayRole);
//            for (int k = 0; k < size; k++)
//            {
//                model->setData(model->index(1, j * size + k + 1), HCore::toCaptionUnit(d_ptr->displays.at(k)), Qt::DisplayRole);
//            }
//        }
//        header << head;
//    }

//    ui->tableWidget_2->setHorizontalHeader(header.at(0));
//    ui->tableWidget_2->setColumnHidden(0, true);
//    ui->tableWidget_3->setHorizontalHeader(header.at(1));

    auto hHead = new HRbTableHeaderView(Qt::Horizontal, 2, 5);
    auto hModel = hHead->model();
    hHead->setSectionsClickable(true);
 //   hHead->setSpan(0, 4, 2, 1);
    hHead->setSpan(0, 0, 1, 2);
    hHead->setSpan(0, 2, 1, 2);
    hHead->setRowHeight(0, 30);
    hHead->setRowHeight(1, 50);
//    hHead->setRowHeight(2, 30);
    hModel->setData(hModel->index(0, 0), QString("cell1"), Qt::DisplayRole);
    hModel->setData(hModel->index(0, 2), QString("cell2"), Qt::DisplayRole);
    hModel->setData(hModel->index(1, 1), QString("cell5"), Qt::DisplayRole);
    hModel->setData(hModel->index(1, 2), QString("cell6"), Qt::DisplayRole);
    hModel->setData(hModel->index(1, 3), QString("cell7"), Qt::DisplayRole);
    hModel->setData(hModel->index(1, 4), QString("cell8"), Qt::DisplayRole);
    hHead->setCellBackgroundColor(hModel->index(0, 0), 0xCFCFCF);
    hHead->setCellBackgroundColor(hModel->index(0, 1), 0xCFCFCF);

    ui->tableWidget_2->setHorizontalHeader(hHead);


}

void HTestWidget3000::initialize()
{
    ui->tableWidget_2->setVerticalHeaderLabels(QStringList() << tr("测试项目") << tr("最大值") << tr("最小值") << tr("平均值") << tr("NG数量") << tr("NG占比"));
    ui->tableWidget_4->setHorizontalHeaderLabels(QStringList() << tr("BIN") << tr("数量") << tr("占比（%）"));
    ui->tableWidget_4->horizontalHeader()->setStretchLastSection(true);
    ui->splitter_1->setStretchFactor(1, 1);
    ui->splitter_1->setStretchFactor(2, 5);
    ui->splitter_2->setStretchFactor(0, 3);
    ui->splitter_2->setStretchFactor(1, 1);
    setLedType();


}


