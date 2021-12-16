#include "HSqlOutput_p.h"
#include "ISqlTableModel.h"
#include "HSql.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITextExport.h"
#include "HeData/ITextExportTemplate.h"
#include "HeData/IPrint.h"
#include "HeData/IPrintTemplate.h"
#include <QtSql/QSqlRecord>

HE_BEGIN_NAMESPACE

HSqlOutputPrivate::HSqlOutputPrivate()
{
    textExport = HAppContext::getContextPointer<ITextExport>("ITextExport");
    print = HAppContext::getContextPointer<IPrint>("IPrint");
}

HSqlOutput::HSqlOutput(QObject *parent) :
    QObject(parent),
    d_ptr(new HSqlOutputPrivate)
{
}

HSqlOutput::HSqlOutput(HSqlOutputPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HSqlOutput::~HSqlOutput() = default;


void HSqlOutput::initialize(QVariantMap /*param*/)
{

}

QString HSqlOutput::typeName()
{
    return "HSqlOutput";
}

void HSqlOutput::setModel(ISqlTableModel *p)
{
    if (d_ptr->model == p)
        return;
    d_ptr->model = p;
}

void HSqlOutput::setTextTemplate(ITextExportTemplate *p)
{
    if (d_ptr->textTemplate == p)
        return;
    d_ptr->textTemplate = p;
}

void HSqlOutput::setPrintTemplate(IPrintTemplate *p)
{
    if (d_ptr->printTemplate == p)
        return;
    d_ptr->printTemplate = p;
}

void HSqlOutput::outputExcel()
{
    if (!isValid())
        return;

    auto type = HSql::toType(d_ptr->model->field());
    auto data = HSql::toData(type, d_ptr->model->currentRecord());
    saveExcel(type, data);
}

void HSqlOutput::outputExcel(int index, int count)
{
    if (!d_ptr->model->isValid(index))
        return;

    QVariantList list;
    auto type = HSql::toType(d_ptr->model->field());
    auto surplus = d_ptr->model->rowCount() - index;
    count = count == -1 ? surplus : qBound(0, count, surplus);
    for (int i = 0; i < count; i++)
        list << HSql::toData(type, d_ptr->model->record(index + i));
    saveExcel(type, list);
}

void HSqlOutput::print()
{
    if (!preparePrint())
        return;
    d_ptr->print->print();
}

void HSqlOutput::printPreview()
{
    if (!preparePrint())
        return;
    d_ptr->print->printPreview();
}

void HSqlOutput::printPdf()
{
    if (!preparePrint())
        return;
    d_ptr->print->printPdf();
}

bool HSqlOutput::isValid()
{
    return d_ptr->model->isValid(d_ptr->model->currentRow());
}

bool HSqlOutput::preparePrint()
{
    if (!isValid())
        return false;
    auto data = HSql::toData(d_ptr->printTemplate->dataType(), d_ptr->model->currentRecord());
    d_ptr->printTemplate->setData(data);
    d_ptr->print->setPrintTemplate(d_ptr->printTemplate);
    return true;
}

void HSqlOutput::saveExcel(QStringList type, QVariant data)
{
    d_ptr->textTemplate->setDataType(type);
    d_ptr->textTemplate->setData(data);
    d_ptr->textExport->setTextTemplate(d_ptr->textTemplate);
    d_ptr->textExport->save();
}

HE_END_NAMESPACE
