#include "HAbstractGradeItemDialog_p.h"
#include "HeData/IGradeItem.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractGradeItemDialog::HAbstractGradeItemDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new HAbstractGradeItemDialogPrivate)
{
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

HAbstractGradeItemDialog::HAbstractGradeItemDialog(HAbstractGradeItemDialogPrivate &p, QWidget *parent) :
    QDialog(parent),
    d_ptr(&p)
{
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

HAbstractGradeItemDialog::~HAbstractGradeItemDialog()
{
    qDebug() << __func__;
}

void HAbstractGradeItemDialog::setData(IGradeItem *p)
{
    d_ptr->data = p;
    d_ptr->type = p->types().first();
    showData();
}

void HAbstractGradeItemDialog::done(int result)
{
    if (result == QDialog::Accepted)
    {
        if (d_ptr->averageMode)
            averageLevels();
        saveData();
    }
    QDialog::done(result);
}

bool HAbstractGradeItemDialog::setAverageMode(bool b)
{
    if (d_ptr->averageMode == b)
        return false;
    d_ptr->averageMode = b;
    return true;
}

HE_GUI_END_NAMESPACE
