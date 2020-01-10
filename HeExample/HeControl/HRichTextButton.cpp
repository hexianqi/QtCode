#include "HRichTextButton_p.h"
#include <QtGui/QTextDocument>
#include <QtGui/QAbstractTextDocumentLayout>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStylePainter>
#include <QtWidgets/QStyleOptionButton>

HE_CONTROL_BEGIN_NAMESPACE

HRichTextButton::HRichTextButton(QWidget *parent) :
    QAbstractButton(parent),
    d_ptr(new HRichTextButtonPrivate)
{
    init();
}

HRichTextButton::HRichTextButton(HRichTextButtonPrivate &p, QWidget *parent) :
    QAbstractButton(parent),
    d_ptr(&p)
{
    init();
}

HRichTextButton::~HRichTextButton()
{
    deleteInternalDoc();
}

QSize HRichTextButton::sizeHint() const
{
    if (document() == nullptr)
        return QSize(80, 25);
    QStyleOptionButton option;
    initStyleOption(&option);
    auto m = (style()->pixelMetric(QStyle::PM_ButtonMargin, &option, this) + style()->pixelMetric(QStyle::PM_DefaultFrameWidth, nullptr, this)) * 2;
    return QSize(80, 25).expandedTo(QApplication::globalStrut()).expandedTo(document()->size().toSize() + QSize(m, m));
}

QSize HRichTextButton::minimumSizeHint() const
{
    return QSize(80, 25).expandedTo(QApplication::globalStrut());
}

int HRichTextButton::heightForWidth(int w) const
{
    if (document() == nullptr)
        return -1;
    QStyleOptionButton option;
    initStyleOption(&option);
    auto m = style()->pixelMetric(QStyle::PM_ButtonMargin, &option, this) + style()->pixelMetric(QStyle::PM_DefaultFrameWidth, nullptr, this);
    document()->setTextWidth(w - m);
    return document()->size().toSize().height() + m;
}

QString HRichTextButton::text() const
{
    return html();
}

QString HRichTextButton::html() const
{
    return (document() != nullptr ? document()->toHtml() : "");
}

QTextDocument *HRichTextButton::document() const
{
    return d_ptr->doc;
}

void HRichTextButton::setText(QString value)
{
    setHtml(value);
}

void HRichTextButton::setHtml(QString value)
{
    if (document() != nullptr && d_ptr->internalDoc)
        d_ptr->doc->setHtml(value);
    else
        createInternalDoc(value);
    document()->adjustSize();
    updateGeometry();
    update();
}

void HRichTextButton::setDocument(QTextDocument *p)
{
    if (document())
        document()->disconnect(this);
    deleteInternalDoc();
    d_ptr->doc = p;
    if (p == nullptr)
        return;

    d_ptr->doc->adjustSize();
    updateGeometry();
    connect(d_ptr->doc, &QTextDocument::contentsChanged, this, [=] { update(); });
    connect(d_ptr->doc, &QTextDocument::destroyed, this, [=] { if (!d_ptr->internalDoc) createInternalDoc(""); });
    d_ptr->internalDoc = false;
}

void HRichTextButton::paintEvent(QPaintEvent *)
{
    QStyleOptionButton option;
    initStyleOption(&option);

    QStylePainter painter(this);
    painter.drawControl(QStyle::CE_PushButtonBevel, option);
    if (document() == nullptr)
        return;

    QAbstractTextDocumentLayout::PaintContext ctx;
    ctx.palette = palette();
    auto h = qRound(document()->documentLayout()->documentSize().height());
    auto r = style()->subElementRect(QStyle::SE_PushButtonContents, &option, this);

    painter.translate(r.topLeft() - rect().topLeft());
    if(r.height() > h)
        painter.translate(0, (r.height() - h) / 2);
    if (isDown() || isChecked())
    {
        auto size = QSize(style()->pixelMetric(QStyle::PM_ButtonShiftHorizontal, &option, this), style()->pixelMetric(QStyle::PM_ButtonShiftVertical, &option, this));
        painter.translate(size.width(), size.height());
    }
    auto old = document()->textWidth();
    document()->setTextWidth(r.width());
    painter.save();
    painter.setClipRect(0, 0, r.width(), r.height());
    painter.setClipping(true);
    document()->documentLayout()->draw(&painter, ctx);
    document()->setTextWidth(old);
    painter.restore();
}

void HRichTextButton::init()
{
    createInternalDoc("Rich text button");
    auto policy = QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
    setAttribute(Qt::WA_Hover);
}

void HRichTextButton::initStyleOption(QStyleOptionButton *option) const
{
    if (option == nullptr)
        return;
    option->initFrom(this);
    if (isDown())
        option->state |= QStyle::State_Sunken;
    else
        option->state |= QStyle::State_Raised;
    if (isChecked())
        option->state |= QStyle::State_On;
}

void HRichTextButton::createInternalDoc(const QString &text)
{
    auto doc = new QTextDocument(this);
    doc->setHtml(text);
    setDocument(doc);
    d_ptr->internalDoc = true;
}

void HRichTextButton::deleteInternalDoc()
{
    if (d_ptr->internalDoc)
        delete d_ptr->doc;
}

HE_CONTROL_END_NAMESPACE
