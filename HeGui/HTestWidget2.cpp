#include "HTestWidget2_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITextStream.h"
#include "HeData/ITestData.h"
#include "HeController/IMemento.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/ISqlPrint.h"
#include "HeSql/HSql.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HTestWidget2Private::HTestWidget2Private()
{
    memento = HAppContext::getContextPointer<IMemento>("IMementoTest");
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

void HTestWidget2::start()
{
    Q_D(HTestWidget2);
    HTestWidget::start();
    if (d->memento)
        d->memento->restore();
}

void HTestWidget2::stop()
{
    Q_D(HTestWidget2);
    HTestWidget::stop();
    if (d->memento)
        d->memento->save();
}

void HTestWidget2::closeEvent(QCloseEvent *event)
{
    qDebug() << __func__;
    Q_D(HTestWidget2);
    stop();
    if (d->memento)
        d->memento->writeFile();
    if (!d->records.isEmpty())
    {
        if (QMessageBox::question(this, tr("保存数据"), tr("是否保存到数据库？")) == QMessageBox::Yes)
            exportResult(0, d->records.count());
    }
    event->accept();
}

void HTestWidget2::createAction()
{
    Q_D(HTestWidget2);
    HTestWidget::createAction();
    d->actionPrintPreview = new QAction(tr("打印预览(&V)"), this);
    d->actionPrintPreview->setIcon(QIcon(":/image/PrintPreview.png"));
    d->actionPrintPreview->setIconText(tr("打印预览"));
    d->actionPrintPreview->setEnabled(false);
    d->actionExportDatabase = new QAction(tr("保存数据库(&D)"), this);
    d->actionExportDatabase->setIcon(QIcon(":/image/DbComit.png"));
    d->actionExportDatabase->setIconText(tr("保存数据库"));
    d->actionExportDatabase->setEnabled(false);
    connect(d->actionPrintPreview, &QAction::triggered, this, &HTestWidget2::printPreview);
    connect(d->actionExportDatabase, &QAction::triggered, this, &HTestWidget2::exportDatabase);
}

void HTestWidget2::exportExcel()
{
    Q_D(HTestWidget2);
    QString text;
    text += HCore::toCaptionUnit(d->displays).join("\t") + "\n";
    text += d->testData->toString(d->displays).join("\t") + "\n";
    d->stream->setContent(text);
    d->stream->saveAsFile();
}

void HTestWidget2::clearResult()
{
    Q_D(HTestWidget2);
    d->records.clear();
}

void HTestWidget2::removeResult(int index, int count)
{
    Q_D(HTestWidget2);
    if (count < 1 || index < 0)
        return;
    count = qMin(d->records.size() - index, count);
    for (int i = 0; i < count; i++)
        d->records.removeAt(index);
}

void HTestWidget2::exportResult(int index, int count)
{
    Q_D(HTestWidget2);
    if (count < 1 || index < 0)
        return;
    count = qMin(d->records.size() - index, count);
    for (int i = 0; i < count; i++)
        d->sqlHandle->addRecord(d->records.at(index + i), false);
}

void HTestWidget2::exportDatabase()
{
    Q_D(HTestWidget2);
    if (d->records.isEmpty())
        return;
    d->sqlHandle->addRecord(d->records.first());
}

void HTestWidget2::printPreview()
{
    Q_D(HTestWidget2);
    if (d->records.isEmpty())
        return;
    d->sqlHandle->addRecord(d->records.first(), false);
    d->sqlPrint->printPreview();
}

void HTestWidget2::saveRecord(bool append)
{
    Q_D(HTestWidget2);
    if (!append && !d->records.isEmpty())
        d->records.removeLast();
    QVariantMap data;
    for (const auto &f : d->sqlHandle->field())
        data.insert(f, d->testData->data(HSql::toType(f)));
    d->records.append(data);
}

HE_GUI_END_NAMESPACE
