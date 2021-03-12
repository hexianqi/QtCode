#pragma once
#include "HFileChooser.h"
#include "HButtonLineEdit_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFileChooserPrivate : public HButtonLineEditPrivate
{
public:
    QCompleter *completer;
    QFileDialog::FileMode fileMode = QFileDialog::AnyFile;
    QFileDialog::AcceptMode acceptMode = QFileDialog::AcceptOpen;
    bool native = true;
    QString filter;
    QIcon icon;
};

HE_CONTROL_END_NAMESPACE
