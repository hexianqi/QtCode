/***************************************************************************************************
**      2019-08-08  HRichTextEdit
***************************************************************************************************/

#ifndef HRICHTEXTEDIT_H
#define HRICHTEXTEDIT_H

#include "HControlGlobal.h"
#include <QtGui/QIcon>
#include <QtWidgets/QTextEdit>

HE_CONTROL_BEGIN_NAMESPACE

class HRichTextEditPrivate;

class HRichTextEdit : public QTextEdit
{
    Q_OBJECT
    Q_PROPERTY(Options options READ options WRITE setOptions)

public:
    enum Option
    {
        NoOptions = 0x0,
        FontFamily = 0x01,
        FontSize = 0x02,
        Style = 0x04,
        Alignment = 0x08,
        Color = 0x10,
        List = 0x20,
        AllOptions = FontFamily | FontSize | Style | Alignment | Color | List
    };
    Q_DECLARE_FLAGS(Options, Option)
    Q_FLAG(Options)

public:
    explicit HRichTextEdit(QWidget *parent = nullptr);
    ~HRichTextEdit() override;

public:
    Options options() const;

public slots:
    void setFontFocus();
    void setFont(const QFont &);
    void setBold(bool b);
    void setItalic(bool b);
    void setUnderline(bool b);
    void setAlignment(QAction *);
    void setList(bool b);
    void setColor(const QColor &);
    void setOptions(Options value);
    void updateActions();

protected:
    HRichTextEdit(HRichTextEditPrivate &p, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void contextMenuEvent(QContextMenuEvent *) override;
    void setCharFormat(const QTextCharFormat &);

protected:
    QScopedPointer<HRichTextEditPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HRICHTEXTEDIT_H
