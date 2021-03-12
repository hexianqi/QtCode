/***************************************************************************************************
**      2019-08-08  HRichTextButton
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QAbstractButton>

class QTextDocument;
class QStyleOptionButton;

HE_CONTROL_BEGIN_NAMESPACE

class HRichTextButtonPrivate;

class HRichTextButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString html READ html WRITE setHtml USER true)

public:
    explicit HRichTextButton(QWidget *parent = nullptr);
    ~HRichTextButton() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int w) const override;
    QString text() const;
    QString html() const;
    QTextDocument *document() const;

public slots:
    void setText(const QString &);
    void setHtml(const QString &value);
    void setDocument(QTextDocument *);

protected:
    HRichTextButton(HRichTextButtonPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;

protected:
    QScopedPointer<HRichTextButtonPrivate> d_ptr;

private:
    void init();
    void initStyleOption(QStyleOptionButton *option) const;
    void createInternalDoc(const QString &text);
    void deleteInternalDoc();
};

HE_CONTROL_END_NAMESPACE
