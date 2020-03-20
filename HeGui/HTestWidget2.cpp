#include "HTestWidget2_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeData/IExcelStream.h"
#include "HeData/ITestData.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/ISqlPrint.h"
#include "HeSql/HSql.h"
#include <QtWidgets/QAction>

HE_GUI_BEGIN_NAMESPACE

HTestWidget2Private::HTestWidget2Private()
{
    sqlHandle = HAppContext::getContextPointer<ISqlHandle>("ISqlHandle");
    sqlPrint = HAppContext::getContextPointer<ISqlPrint>("ISqlPrint");
}

HTestWidget2::HTestWidget2(QWidget *parent) :
    HTestWidget(*new HTestWidget2Private, parent)
{
}

HTestWidget2::HTestWidget2(HTestWidget2Private &p, QWidget *parent) :
    HTestWidget(p, parent)
{
}

HTestWidget2::~HTestWidget2()
{
}

void HTestWidget2::createAction()
{
    Q_D(HTestWidget2);
    HTestWidget::createAction();
    d->actionExportDatabase = new QAction(tr("保存数据库(&D)"), this);
    d->actionExportDatabase->setIcon(QIcon(":/image/DbComit.png"));
    d->actionExportDatabase->setIconText(tr("保存数据库"));
    d->actionExportDatabase->setEnabled(false);
    d->actionPrintPreview = new QAction(tr("打印预览(&V)"), this);
    d->actionPrintPreview->setIcon(QIcon(":/image/PrintPreview.png"));
    d->actionPrintPreview->setIconText(tr("打印预览"));
    d->actionPrintPreview->setEnabled(false);
    connect(d->actionExportDatabase, &QAction::triggered, this, [=] { exportDatabase(true); });
    connect(d->actionPrintPreview, &QAction::triggered, this, &HTestWidget2::printPreview);
}

void HTestWidget2::exportExcel()
{
    Q_D(HTestWidget2);
    if (!canExport())
        return;
    QString text;
    text += HCore::toCaptionUnit(d->displays).join("\t") + "\n";
    text += d->testData->toString(d->displays).join("\t") + "\n";
    d->excelStream->setWriteContent(text);
    d->excelStream->saveAsFile();
}

void HTestWidget2::exportDatabase(bool edit)
{
    Q_D(HTestWidget2);
    if (!canExport())
        return;
    QVariantMap data;
    for (auto f : d->sqlHandle->field())
        data.insert(f, d->testData->data(HSql::toType(f)));
    d->sqlHandle->addRecord(data, edit);
}

void HTestWidget2::printPreview()
{
    Q_D(HTestWidget2);
    if (!canExport())
        return;
    exportDatabase(false);
    d->sqlPrint->printPreview();
}

HE_GUI_END_NAMESPACE
