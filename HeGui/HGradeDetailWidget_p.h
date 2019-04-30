#ifndef HGRADEDETAILWIDGET_P_H
#define HGRADEDETAILWIDGET_P_H

#include "HGradeDetailWidget.h"

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
class IGrade;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HGradeDetailWidgetPrivate
{
public:
    HGradeDetailWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IGradeCollection *grades = nullptr;
    IGrade *grade = nullptr;
    QStringList optionals;
    QStringList selecteds;
    QStringList unselecteds;
};

HE_GUI_END_NAMESPACE

#endif // HGRADEDETAILWIDGET_P_H
