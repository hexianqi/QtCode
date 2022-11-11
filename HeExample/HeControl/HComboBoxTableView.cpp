#include "HComboBoxTableView_p.h"
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QLineEdit>

HE_BEGIN_NAMESPACE

HComboBoxTableView::HComboBoxTableView(QComboBox *parent) :
    QTableView(parent),
    d_ptr(new HComboBoxTableViewPrivate)
{
    d_ptr->comboBox = parent;
    init();
}

HComboBoxTableView::HComboBoxTableView(HComboBoxTableViewPrivate &p, QComboBox *parent) :
    QTableView(parent),
    d_ptr(&p)
{
    d_ptr->comboBox = parent;
    init();
}

HComboBoxTableView::~HComboBoxTableView()
{
}

void HComboBoxTableView::init()
{
    verticalHeader()->hide();
    horizontalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto model = new QStandardItemModel(this);
    model->setColumnCount(3);
    model->setRowCount(3);
    setModel(model);

    auto style = QString("QPushButton { color:#ffffff; padding:6px 10px 6px 10px; background-color:#00beac; font-size:24px; border-radius:6px; }"
                         "QPushButton:hover { background-color:#20c9b3; }"
                         "QPushButton:pressed { background-color:#01968c; }"
                         "QPushButton:checked { background-color:red; }");
    QList<QPushButton *> list;
    auto group = new QButtonGroup(this);

    for (int i = 1;i < 10;++i)
    {
        auto btn = new QPushButton(this);
        btn->setCheckable(true);
        btn->setStyleSheet(style);
        btn->setText(QString("%1").arg(i));
        list << btn;
        group->addButton(btn);
        connect(btn, &QPushButton::toggled, [=] { d_ptr->comboBox->setCurrentText(btn->text()); });
    }
    group->setExclusive(true);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            model->setItem(i, j, new QStandardItem());
            setIndexWidget(model->index(i,j),list[i * 3 + j]);
        }
    }
}

HE_END_NAMESPACE
