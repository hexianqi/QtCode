#include "HTestTable.h"
#include "RbTableHeaderView.h"
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QTableWidget>

QTableView *HTestTable::multHeaderTableView()
{
    auto hHead = new RbTableHeaderView(Qt::Horizontal, 2, 4);
    auto hModel = hHead->model();
    hHead->setSectionsClickable(true);
    hHead->setSpan(0, 0, 2, 1);
    hHead->setSpan(0, 1, 1, 2);
    hHead->setSpan(1, 1, 1, 1);
    hHead->setSpan(1, 2, 1, 1);
    hHead->setSpan(1, 3, 1, 1);
    hModel->setData(hModel->index(0, 0), QString("cell1"), Qt::DisplayRole);
    hModel->setData(hModel->index(0, 1), QString("cell2"), Qt::DisplayRole);
    hModel->setData(hModel->index(1, 1), QString("cell3"), Qt::DisplayRole);
    hModel->setData(hModel->index(1, 2), QString("cell4"), Qt::DisplayRole);
    hModel->setData(hModel->index(1, 3), QString("cell5"), Qt::DisplayRole);

    auto vHead = new RbTableHeaderView(Qt::Vertical, 3, 2);
    auto vModel = vHead->model();
    vHead->setSectionsClickable(true);
    vHead->setSpan(0, 0, 1, 2);
    vHead->setSpan(1, 0, 2, 1);
    vHead->setSpan(1, 1, 1, 1);
    vHead->setSpan(2, 1, 1, 1);
    vModel->setData(vModel->index(0, 0), QString("cell1"), Qt::DisplayRole);
    vModel->setData(vModel->index(1, 0), QString("cell2"), Qt::DisplayRole);
    vModel->setData(vModel->index(1, 1), QString("cell3"), Qt::DisplayRole);
    vModel->setData(vModel->index(2, 1), QString("cell4"), Qt::DisplayRole);

    auto dataModel = new QStandardItemModel;
    for (int i = 0; i < 3; i++)
    {
        QList<QStandardItem*> items;
        for (int j = 0; j < 3; j++)
        {
            items.append(new QStandardItem(QString("item(%1,%2)").arg(i).arg(j)));
        }
        dataModel->appendRow(items);
    }

    auto view = new QTableView();
    view->resize(800, 600);
    view->setModel(dataModel);
    view->setHorizontalHeader(hHead);
    view->setVerticalHeader(vHead);
    return view;
}

QTableWidget *HTestTable::multHeaderTableWidget()
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
    rootWidget->setCellWidget(0,0,widget1);
    rootWidget->setCellWidget(0,1,widget2);
    rootWidget->setCellWidget(0,2,widget3);
    return rootWidget;
}
