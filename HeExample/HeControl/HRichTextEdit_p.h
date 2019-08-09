#ifndef HRICHTEXTEDIT_P_H
#define HRICHTEXTEDIT_P_H

#include "HRichTextEdit.h"

class QToolBar;
class QComboBox;
class QFontComboBox;

HE_CONTROL_BEGIN_NAMESPACE

class HColorButton;

class HRichTextEditPrivate
{
public:
    HRichTextEdit::Options options = HRichTextEdit::AllOptions;
    QToolBar *toolBar;
    QFontComboBox *fontComboBox;
    QComboBox *sizeComboBox;
    HColorButton *colorButton;
    QTextList *currentList = nullptr;
    QAction *fontAction;
    QAction *fontSizeAction;
    QAction *boldAction;
    QAction *italicAction;
    QAction *underlineAction;
    QAction *alignLeftAction;
    QAction *alignCenterAction;
    QAction *alignRightAction;
    QAction *alignJustifyAction;
    QAction *colorAction;
    QAction *listAtion;
    QList<QAction *> separators;

};

HE_CONTROL_END_NAMESPACE

#endif // HRICHTEXTEDIT_P_H
