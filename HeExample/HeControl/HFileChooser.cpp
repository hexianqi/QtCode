#include "HFileChooser_p.h"
#include <QtGui/QPainter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QDirModel>
#include <QtWidgets/QStyleOption>
#include <QtWidgets/QShortcut>

HE_BEGIN_NAMESPACE

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

void HFileChooser::setModel(QAbstractItemModel *p)
{
    Q_D(HFileChooser);
    if (d->completer->model() == p)
        return;
    d->completer->setModel(p == nullptr ? new QDirModel(this) : p);
}

void HFileChooser::setFileMode(QFileDialog::FileMode value)
{
    Q_D(HFileChooser);
    d->fileMode = value;
}

void HFileChooser::setAcceptMode(QFileDialog::AcceptMode value)
{
    Q_D(HFileChooser);
    if (d->acceptMode == value)
        return;

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
    QFileIconProvider provider;
    d->icon = provider.icon(QFileInfo(value));
    update();
}

void HFileChooser::paintEvent(QPaintEvent *event)
{
    Q_D(HFileChooser);
    HButtonLineEdit::paintEvent(event);
    QPainter painter(this);
    QStyleOption option;
    option.initFrom(this);
    int margin = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, &option, this);
    int size = style()->pixelMetric(QStyle::PM_SmallIconSize, &option, this);
    d->icon.paint(&painter, QRect(contentsRect().left() + margin + 1, margin + 1, size, size), Qt::AlignCenter, option.state & QStyle::State_Enabled ? QIcon::Normal : QIcon::Disabled);
}

void HFileChooser::init()
{
    Q_D(HFileChooser);
    QStyleOption option;
    option.initFrom(this);
    auto shortcut = new QShortcut(QKeySequence("Ctrl+Space"), this);
    d->completer = new QCompleter(this);
    setTextMargins(style()->pixelMetric(QStyle::PM_SmallIconSize, &option, this) + 2, 0, 0, 0);
    setCompleter(d->completer);
    setModel(new QDirModel(this));
    setButtonPosition(Position_RightOutside);
    setAutoRaise(true);
    setAcceptMode(QFileDialog::AcceptOpen);
    connect(this, &HFileChooser::buttonClicked, this, &HFileChooser::chooseFile);
    connect(this, &HFileChooser::textChanged, this, &HFileChooser::handleTextChanged);
    connect(shortcut, &QShortcut::activated, this, [=] { d->completer->complete(); });
    setWindowIcon(QIcon(":/image/ww/filechooser.png"));
}

HE_END_NAMESPACE
