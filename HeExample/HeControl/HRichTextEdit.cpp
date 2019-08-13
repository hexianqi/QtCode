#include "HRichTextEdit_p.h"
#include "HColorButton.h"
#include <QtGui/QKeyEvent>
#include <QtGui/QTextList>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QFontComboBox>
#include <QtDebug>

HE_CONTROL_BEGIN_NAMESPACE

HRichTextEdit::HRichTextEdit(QWidget *parent) :
    QTextEdit(parent),
    d_ptr(new HRichTextEditPrivate)
{
    init();
}

HRichTextEdit::HRichTextEdit(HRichTextEditPrivate &p, QWidget *parent) :
    QTextEdit(parent),
    d_ptr(&p)
{
    init();
}

HRichTextEdit::~HRichTextEdit()
{
}

HRichTextEdit::Options HRichTextEdit::options() const
{
    return d_ptr->options;
}

void HRichTextEdit::setFontFocus()
{
    auto f = d_ptr->fontComboBox->currentFont();
    f.setPointSize(d_ptr->sizeComboBox->currentText().toInt());
    setFont(f);
    setFocus();
}

void HRichTextEdit::setFont(const QFont &value)
{
    QTextCharFormat f;
    f.setFontFamily(value.family());
    f.setFontPointSize(value.pointSize());
    setCharFormat(f);
    if (d_ptr->fontComboBox->currentFont().family() != value.family())
        d_ptr->fontComboBox->setCurrentFont(value);
    if (d_ptr->sizeComboBox->currentText().toInt() != value.pointSize())
        d_ptr->sizeComboBox->setCurrentIndex(d_ptr->sizeComboBox->findText(QString::number(value.pointSize())));
}

void HRichTextEdit::setBold(bool b)
{
    QTextCharFormat f;
    f.setFontWeight(b ? QFont::Bold : QFont::Normal);
    setCharFormat(f);
}

void HRichTextEdit::setItalic(bool b)
{
    QTextCharFormat f;
    f.setFontItalic(b);
    setCharFormat(f);
}

void HRichTextEdit::setUnderline(bool b)
{
    QTextCharFormat f;
    f.setFontUnderline(b);
    setCharFormat(f);
}

void HRichTextEdit::setAlignment(QAction *p)
{
    auto c = textCursor();
    QTextBlockFormat f;
    auto v = static_cast<Qt::Alignment>(p->data().toInt());
    f.setAlignment(v);
    c.mergeBlockFormat(f);
    setTextCursor(c);
}

void HRichTextEdit::setList(bool b)
{
    QTextCursor c = textCursor();
    if (b)
    {
      QTextListFormat f;
      f.setStyle(QTextListFormat::ListDisc);
      d_ptr->currentList = c.createList(f);
    }
    else
    {
      c.setBlockFormat(QTextBlockFormat());
      setTextCursor(c);
      d_ptr->currentList = nullptr;
    }
}

void HRichTextEdit::setColor(const QColor &value)
{
    QTextCharFormat f;
    f.setForeground(value);
    setCharFormat(f);
}

void HRichTextEdit::setOptions(Options value)
{
    if (d_ptr->options == value)
        return;

    d_ptr->options = value;
    d_ptr->fontAction->setVisible(value & FontFamily);
    d_ptr->fontSizeAction->setVisible(value & FontSize);
    d_ptr->boldAction->setVisible(value & Style);
    d_ptr->italicAction->setVisible(value & Style);
    d_ptr->underlineAction->setVisible(value & Style);
    d_ptr->alignLeftAction->setVisible(value & Alignment);
    d_ptr->alignCenterAction->setVisible(value & Alignment);
    d_ptr->alignRightAction->setVisible(value & Alignment);
    d_ptr->alignJustifyAction->setVisible(value & Alignment);
    d_ptr->colorAction->setVisible(value & Color);
    d_ptr->separators.at(0)->setVisible(value & (FontFamily | FontSize));
    d_ptr->separators.at(1)->setVisible(value & Style);
    d_ptr->separators.at(2)->setVisible(value & Alignment);
    d_ptr->separators.at(3)->setVisible(value & Color);
}

void HRichTextEdit::updateActions()
{
    auto cursor = textCursor();
    auto selection = cursor.hasSelection();
    auto charFormat = cursor.charFormat();
    auto font = charFormat.font();
    auto size = font.pointSize();
    auto color = textColor();

    if (d_ptr->fontComboBox->currentFont().family() != font.family())
        d_ptr->fontComboBox->setCurrentFont(font);
    auto index = d_ptr->sizeComboBox->findText(QString::number(size));
    if (index != -1)
        d_ptr->sizeComboBox->setCurrentIndex(index);

    d_ptr->boldAction->setChecked(font.bold());
    d_ptr->italicAction->setChecked(font.italic());
    d_ptr->underlineAction->setChecked(font.underline());

    if (alignment() & Qt::AlignLeft)
        d_ptr->alignLeftAction->setChecked(true);
    else if (alignment() & Qt::AlignRight)
        d_ptr->alignRightAction->setChecked(true);
    else if (alignment() & Qt::AlignHCenter)
        d_ptr->alignCenterAction->setChecked(true);
    else
        d_ptr->alignJustifyAction->setChecked(true);

    if (!selection)
    {
        d_ptr->colorButton->setCurrentColor(color);
        d_ptr->listAtion->setChecked(cursor.currentList() != nullptr);
    }
}

void HRichTextEdit::setCharFormat(QTextCharFormat value)
{
    auto c = textCursor();
    c.mergeCharFormat(value);
    setTextCursor(c);
}

void HRichTextEdit::keyPressEvent(QKeyEvent *e)
{
    auto c = textCursor();
    d_ptr->currentList = c.currentList();
    if (d_ptr->currentList != nullptr && (e->key() == Qt::Key_Tab || e->key() == Qt::Key_Backtab))
    {
        auto f = d_ptr->currentList->format();
        f.setIndent(d_ptr->currentList->format().indent() + (e->key() == Qt::Key_Tab ? 1 : -1));
        d_ptr->currentList = c.createList(f);
        return;
    }
    QTextEdit::keyPressEvent(e);
}

void HRichTextEdit::resizeEvent(QResizeEvent *e)
{
    auto s = verticalScrollBar();
    d_ptr->toolBar->setGeometry(1, 1, width() - s->sizeHint().width() - 1, d_ptr->toolBar->sizeHint().height());
    QTextEdit::resizeEvent(e);
    auto r = s->geometry();
    r.setTop(d_ptr->toolBar->geometry().bottom() + 2);
    s->setGeometry(r);
}

void HRichTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    auto style = new QMenu(tr("样式"));
    style->addAction(d_ptr->boldAction);
    style->addAction(d_ptr->italicAction);
    style->addAction(d_ptr->underlineAction);
    auto align = new QMenu(tr("对齐"));
    align->addAction(d_ptr->alignLeftAction);
    align->addAction(d_ptr->alignCenterAction);
    align->addAction(d_ptr->alignRightAction);
    align->addAction(d_ptr->alignJustifyAction);

    auto menu = createStandardContextMenu();
    menu->addMenu(style);
    menu->addMenu(align);
    menu->exec(e->globalPos());
    delete menu;
}

void HRichTextEdit::init()
{
    d_ptr->toolBar = new QToolBar(this);
    d_ptr->toolBar->setIconSize(QSize(24, 24));
    d_ptr->fontComboBox = new QFontComboBox(this);
    d_ptr->sizeComboBox = new QComboBox(this);
    for (auto s : QFontDatabase::standardSizes())
        d_ptr->sizeComboBox->addItem(QString::number(s));
    d_ptr->boldAction = new QAction(QIcon::fromTheme("format-text-bold", QIcon(":/image/ww/textbold.png")), tr("粗体"), this);
    d_ptr->boldAction->setCheckable(true);
    d_ptr->italicAction = new QAction(QIcon::fromTheme("format-text-italic", QIcon(":/image/ww/textitalic.png")), tr("斜体"), this);
    d_ptr->italicAction->setCheckable(true);
    d_ptr->underlineAction = new QAction(QIcon::fromTheme("format-text-underline", QIcon(":/image/ww/textunder.png")), tr("下划线"), this);
    d_ptr->underlineAction->setCheckable(true);
    d_ptr->alignLeftAction = new QAction(QIcon::fromTheme("format-justify-left", QIcon(":/image/ww/textleft.png")), tr("左对齐"), this);
    d_ptr->alignLeftAction->setCheckable(true);
    d_ptr->alignLeftAction->setData(Qt::AlignLeft);
    d_ptr->alignCenterAction = new QAction(QIcon::fromTheme("format-justify-center", QIcon(":/image/ww/textcenter.png")), tr("中央对齐"), this);
    d_ptr->alignCenterAction->setCheckable(true);
    d_ptr->alignCenterAction->setData(Qt::AlignCenter);
    d_ptr->alignRightAction = new QAction(QIcon::fromTheme("format-justify-right", QIcon(":/image/ww/textright.png")), tr("右对齐"), this);
    d_ptr->alignRightAction->setCheckable(true);
    d_ptr->alignRightAction->setData(Qt::AlignRight);
    d_ptr->alignJustifyAction = new QAction(QIcon::fromTheme("format-justify-fill", QIcon(":/image/ww/textjustify.png")), tr("自动调整"), this);
    d_ptr->alignJustifyAction->setCheckable(true);
    d_ptr->alignJustifyAction->setData(Qt::AlignJustify);
    auto group = new QActionGroup(this);
    group->addAction(d_ptr->alignLeftAction);
    group->addAction(d_ptr->alignCenterAction);
    group->addAction(d_ptr->alignRightAction);
    group->addAction(d_ptr->alignJustifyAction);
    d_ptr->colorButton = new HColorButton(this);
    d_ptr->colorButton->setShowName(false);
    d_ptr->colorButton->setFlat(true);
    d_ptr->colorButton->setFocusPolicy(Qt::NoFocus);
    d_ptr->listAtion = new QAction(QIcon::fromTheme("format-list-unordered", QIcon(":/image/ww/simplifyrichtext.png")), tr("列表"), this);
    d_ptr->listAtion->setCheckable(true);

    d_ptr->fontAction = d_ptr->toolBar->addWidget(d_ptr->fontComboBox);
    d_ptr->fontSizeAction = d_ptr->toolBar->addWidget(d_ptr->sizeComboBox);
    d_ptr->separators << d_ptr->toolBar->addSeparator();
    d_ptr->toolBar->addAction(d_ptr->boldAction);
    d_ptr->toolBar->addAction(d_ptr->italicAction);
    d_ptr->toolBar->addAction(d_ptr->underlineAction);
    d_ptr->separators << d_ptr->toolBar->addSeparator();
    d_ptr->toolBar->addAction(d_ptr->alignLeftAction);
    d_ptr->toolBar->addAction(d_ptr->alignCenterAction);
    d_ptr->toolBar->addAction(d_ptr->alignRightAction);
    d_ptr->toolBar->addAction(d_ptr->alignJustifyAction);
    d_ptr->separators << d_ptr->toolBar->addSeparator();
    d_ptr->colorAction = d_ptr->toolBar->addWidget(d_ptr->colorButton);
    d_ptr->separators << d_ptr->toolBar->addSeparator();
    d_ptr->toolBar->addAction(d_ptr->listAtion);

    setViewportMargins(0, d_ptr->toolBar->sizeHint().height() + 1, 0, 0);
    setContentsMargins(0, d_ptr->toolBar->sizeHint().height(), 0, 0);
    connect(this, &HRichTextEdit::currentCharFormatChanged, this, &HRichTextEdit::updateActions);
    connect(this, &HRichTextEdit::cursorPositionChanged, this, &HRichTextEdit::updateActions);
    connect(this , &HRichTextEdit::textChanged, this, &HRichTextEdit::updateActions);
    connect(d_ptr->fontComboBox, QOverload<int>::of(&QFontComboBox::activated), this, &HRichTextEdit::setFontFocus);
    connect(d_ptr->sizeComboBox, QOverload<int>::of(&QComboBox::activated), this, &HRichTextEdit::setFontFocus);
    connect(d_ptr->boldAction, &QAction::triggered, this, &HRichTextEdit::setBold);
    connect(d_ptr->italicAction, &QAction::triggered, this, &HRichTextEdit::setItalic);
    connect(d_ptr->underlineAction, &QAction::triggered, this, &HRichTextEdit::setUnderline);
    connect(group, &QActionGroup::triggered, this, &HRichTextEdit::setAlignment);    
    connect(d_ptr->colorButton, &HColorButton::colorPicked, this, &HRichTextEdit::setColor);
    connect(d_ptr->listAtion, &QAction::triggered, this, &HRichTextEdit::setList);
    updateActions();
}

HE_CONTROL_END_NAMESPACE
