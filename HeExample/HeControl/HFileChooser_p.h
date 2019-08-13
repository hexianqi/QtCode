#ifndef HFILECHOOSER_P_H
#define HFILECHOOSER_P_H

#include "HFileChooser.h"
#include "HButtonLineEdit_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFileChooserPrivate : public HButtonLineEditPrivate
{
public:
    QAbstractItemModel *model;
    QCompleter *completer;
    QFileDialog::FileMode fileMode = QFileDialog::AnyFile;
    QFileDialog::AcceptMode acceptMode = QFileDialog::AcceptOpen;
    bool native = true;
    QString filter;
    QIcon icon;
};

HE_CONTROL_END_NAMESPACE

#endif // HFILECHOOSER_P_H
