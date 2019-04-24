#ifndef HGRADEDETAILWIDGET_P_H
#define HGRADEDETAILWIDGET_P_H

#include "HGradeDetailWidget.h"
#include <QModelIndex>

HE_GUI_BEGIN_NAMESPACE

class HGradeDetailWidgetPrivate
{
public:
    IGradeCollection *grades = nullptr;
    IGrade *grade = nullptr;
    QStringList optionals;
    QStringList selecteds;
    QStringList unselecteds;
};

HE_GUI_END_NAMESPACE

#endif // HGRADEDETAILWIDGET_P_H
