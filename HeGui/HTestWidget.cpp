#include "HTestWidget_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeData/IDataFactory.h"
#include "HeData/IExcelStream.h"
#include "HeData/ITestData.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/HSql.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QToolBar>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HTestWidgetPrivate::HTestWidgetPrivate()
{
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("ISqlHandle");
    excelStream = HAppContext::getContextPointer<IDataFactory>("IDataFactory")->createExcelStream("HExcelStream");
}

HTestWidget::HTestWidget(QWidget *parent) :
    HAbstractTestWidget(*new HTestWidgetPrivate, parent)
{
}

HTestWidget::HTestWidget(HTestWidgetPrivate &p, QWidget *parent) :
    HAbstractTestWidget(p, parent)
{
}

HTestWidget::~HTestWidget()
{
    qDebug() << __func__;
}

void HTestWidget::init()
{
    createWidget();
    createAction();
    createMenu();
    createToolBar();
    initToolBar();
}

void HTestWidget::createAction()
{
    Q_D(HTestWidget);
    d->actionStart = new QAction(tr("测量(&S)"), this);
    d->actionStart->setIcon(QIcon(":/image/Start02.png"));
    d->actionStart->setIconText(tr("测量"));
    d->actionStart->setShortcut(Qt::Key_F3);
    d->actionStop = new QAction(tr("停止(&T)"), this);
    d->actionStop->setIcon(QIcon(":/image/Stop02.png"));
    d->actionStop->setIconText(tr("停止"));
    d->actionStop->setShortcut(Qt::Key_F4);
    d->actionStop->setEnabled(false);
    d->actionExportExcel = new QAction(tr("导出结果(&E)"), this);
    d->actionExportExcel->setIcon(QIcon(":/image/Excel.png"));
    d->actionExportExcel->setIconText(tr("导出结果"));
    d->actionExportDatabase = new QAction(tr("保存数据库(&D)"), this);
    d->actionExportDatabase->setIcon(QIcon(":/image/DbComit.png"));
    d->actionExportDatabase->setIconText(tr("保存数据库"));
    d->actionClear = new QAction(tr("清除结果(&R)..."), this);
    d->actionClear->setIcon(QIcon(":/image/Clear.png"));
    d->actionClear->setIconText(tr("清除结果"));
    connect(d->actionStart, &QAction::triggered, this, [=] { setTest(true); });
    connect(d->actionStop, &QAction::triggered, this, [=] { setTest(false); });
    connect(d->actionExportExcel, &QAction::triggered, this, &HTestWidget::exportExcel);
    connect(d->actionExportDatabase, &QAction::triggered, this, &HTestWidget::exportDatabase);
    connect(d->actionClear, &QAction::triggered, this, &HTestWidget::clearResult);

}

void HTestWidget::initToolBar()
{
    for (auto bar : toolBars())
        bar->setMovable(false);
}

void HTestWidget::exportExcel()
{
    Q_D(HTestWidget);
    QString text;
    text += HCore::toCaptionUnit(d->displays).join("\t") + "\n";
    text += d->testData->toString(d->displays).join("\t") + "\n";
    d->excelStream->setWriteContent(text);
    d->excelStream->saveAsFile();
}

void HTestWidget::exportDatabase()
{
    Q_D(HTestWidget);
    QVariantMap data;
    for (auto f : d->sqlHandle->field())
        data.insert(f, d->testData->data(HSql::toType(f)));
    d->sqlHandle->addRecord(data);
}

HE_GUI_END_NAMESPACE
