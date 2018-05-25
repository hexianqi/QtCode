#ifndef HMAINWINDOW_P_H
#define HMAINWINDOW_P_H

#include "HMainWindow.h"
#include <QMap>

class QLabel;

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HMainWindowPrivate
{
public:
    HMainWindowPrivate(HMainWindow *p);

public:
    HMainWindow *q_ptr;
    QString fileName;
    IModel *model;
    QMap<QString, QLabel *> labels;
};

HE_GUI_END_NAMESPACE

#endif // HMAINWINDOW_P_H
