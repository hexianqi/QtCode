#include "HAbstractTestDataEditDialog_p.h"
#include "HeCore/HAppContext.h"

HE_GUI_BEGIN_NAMESPACE

HAbstractTestDataEditDialogPrivate::HAbstractTestDataEditDialogPrivate()
{
    data0 = HAppContext::getContextPointer<ITestData>("ITestData");
}

ITestData *HAbstractTestDataEditDialogPrivate::data()
{
    return data1 == nullptr ? data0 : data1;
}

HAbstractTestDataEditDialog::HAbstractTestDataEditDialog(QWidget *parent) :
    ITestDataEditDialog(parent),
    d_ptr(new HAbstractTestDataEditDialogPrivate)
{
}

HAbstractTestDataEditDialog::HAbstractTestDataEditDialog(HAbstractTestDataEditDialogPrivate &p, QWidget *parent) :
    ITestDataEditDialog(parent),
    d_ptr(&p)
{
}

HAbstractTestDataEditDialog::~HAbstractTestDataEditDialog() = default;

void HAbstractTestDataEditDialog::setData(ITestData *p)
{
    d_ptr->data1 = p;
    showData();
}

void HAbstractTestDataEditDialog::done(int result)
{
    if (result == QDialog::Accepted)
        saveData();
    QDialog::done(result);
}

HE_GUI_END_NAMESPACE
