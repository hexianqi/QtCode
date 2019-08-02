#include "HFileChooser_p.h"
#include <QtGui/QPainter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QDirModel>
#include <QtWidgets/QStyleOption>
#include <QtWidgets/QShortcut>

HE_CONTROL_BEGIN_NAMESPACE

HFileChooser::HFileChooser(QWidget *parent) :
    HButtonLineEdit(*new HFileChooserPrivate, parent)
{
    init();
}

HFileChooser::HFileChooser(HFileChooserPrivate &p, QWidget *parent) :
    HButtonLineEdit(p, parent)
{
    init();
}

HFileChooser::~HFileChooser()
{
}

QFileDialog::FileMode HFileChooser::fileMode() const
{
    Q_D(const HFileChooser);
    return d->fileMode;
}

QFileDialog::AcceptMode HFileChooser::acceptMode() const
{
    Q_D(const HFileChooser);
    return d->acceptMode;
}

bool HFileChooser::isUseNativeFileDialog() const
{
    Q_D(const HFileChooser);
    return d->native;
}

QString HFileChooser::filter() const
{
    Q_D(const HFileChooser);
    return d->filter;
}

QCompleter::CompletionMode HFileChooser::completionMode() const
{
    Q_D(const HFileChooser);
    return d->completer->completionMode();
}

QSize HFileChooser::sizeHint() const
{
    Q_D(const HFileChooser);
    return QLineEdit::sizeHint() + QSize(d->button->sizeHint().width(), 0);
}

QSize HFileChooser::minimumSizeHint() const
{
    Q_D(const HFileChooser);
    return QLineEdit::minimumSizeHint() + QSize(d->button->sizeHint().width(), 0);
}

void HFileChooser::setModel(QAbstractItemModel *p)
{
    Q_D(HFileChooser);
    if (d->model == p)
        return;
    d->model = p == nullptr ? new QDirModel(this) : p;
    d->completer->setModel(d->model);
}

void HFileChooser::setFileMode(QFileDialog::FileMode value)
{
    Q_D(HFileChooser);
    d->fileMode = value;
}

void HFileChooser::setAcceptMode(QFileDialog::AcceptMode value)
{
    Q_D(HFileChooser);
    d->acceptMode = value;
    if (d->acceptMode == QFileDialog::AcceptOpen)
        setIcon(QIcon::fromTheme("document-open", QIcon(":/image/ww/fileopen.png")));
    else
        setIcon(QIcon::fromTheme("document-save", QIcon(":/image/ww/filesave.png")));
}

void HFileChooser::setUseNativeFileDialog(bool b)
{
    Q_D(HFileChooser);
    d->native = b;
}

void HFileChooser::setFilter(const QString &value)
{
    Q_D(HFileChooser);
    d->filter = value;
}

void HFileChooser::setCompletionMode(QCompleter::CompletionMode value)
{
    Q_D(HFileChooser);
    d->completer->setCompletionMode(value);
}

void HFileChooser::chooseFile()
{
    Q_D(HFileChooser);
    if (isReadOnly())
        return;

    QString path;
    if (d->native)
    {
        switch (d->fileMode)
        {
        case QFileDialog::AnyFile:
            if (d->acceptMode == QFileDialog::AcceptOpen)
                path = QFileDialog::getOpenFileName(this, tr("选择文件"), text(), filter());
            else
                path = QFileDialog::getSaveFileName(this, tr("选择文件"), text(), filter());
            break;
        case QFileDialog::ExistingFile:
            if (d->acceptMode == QFileDialog::AcceptOpen)
                path = QFileDialog::getOpenFileName(this, tr("选择文件"), text(), filter());
            break;
        case QFileDialog::Directory:
            path = QFileDialog::getExistingDirectory(this, tr("选择目录"), text());
            break;
        case QFileDialog::DirectoryOnly:
            path = QFileDialog::getExistingDirectory(this, tr("选择目录"), text());
            break;
        case QFileDialog::ExistingFiles:
            QStringList s = QFileDialog::getOpenFileNames(this, tr("选择文件"), text(), filter());
            if (!s.isEmpty())
                path = s.at(0);
            break;
        }
    }
    else
    {
        QFileDialog dlg(this);
        dlg.setAcceptMode(d->acceptMode);
        dlg.setFileMode(d->fileMode);
        dlg.setDirectory(text());
        dlg.setNameFilter(filter());
        if (dlg.exec())
        {
            QStringList s = dlg.selectedFiles();
            if (!s.isEmpty())
                path = s.at(0);
        }
    }
    if (!path.isNull())
    {
        setText(path);
        d->completer->setCompletionPrefix(path);
    }
}

void HFileChooser::handleTextChanged(const QString &value)
{
    Q_D(HFileChooser);
    QFileIconProvider prov;
    d->icon = prov.icon(QFileInfo(value));
    update();
}

void HFileChooser::paintEvent(QPaintEvent *e)
{
    Q_D(HFileChooser);
    HButtonLineEdit::paintEvent(e);
    QPainter p(this);
    QStyleOption option;
    option.initFrom(this);
    int margin = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, &option, this);
    int size = style()->pixelMetric(QStyle::PM_SmallIconSize, &option, this);
    d->icon.paint(&p, QRect(contentsRect().left() + margin + 1, margin + 1, size, size), Qt::AlignCenter, option.state & QStyle::State_Enabled ? QIcon::Normal : QIcon::Disabled);
}

void HFileChooser::init()
{
    Q_D(HFileChooser);
    QStyleOption option;
    option.initFrom(this);
    auto sc = new QShortcut(QKeySequence("Ctrl+Space"), this);
    d->completer = new QCompleter(this);
    setTextMargins(style()->pixelMetric(QStyle::PM_SmallIconSize, &option, this) + 2, 0, 0, 0);
    setCompleter(d->completer);
    setModel(new QDirModel(this));
    setButtonPosition(RightOutside);
    setAutoRaise(true);
    setAcceptMode(QFileDialog::AcceptOpen);
    connect(this, &HFileChooser::buttonClicked, this, &HFileChooser::chooseFile);
    connect(this, &HFileChooser::textChanged, this, &HFileChooser::handleTextChanged);
    connect(sc, &QShortcut::activated, this, [=] { d->completer->complete(); });
}

HE_CONTROL_END_NAMESPACE
