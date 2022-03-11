#include "HDiskSizeTable_p.h"
#include <QtCore/QTimer>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#ifdef Q_OS_WIN
#include <QtCore/QDir>
#include <windows.h>
#else
#include <QtCore/QProcess>
#endif

#define GB (1024 * 1024 * 1024)
#define MB (1024 * 1024)
#define KB (1024)

HE_BEGIN_NAMESPACE

HDiskSizeTable::HDiskSizeTable(QWidget *parent) :
    QTableWidget(parent),
    d_ptr(new HDiskSizeTablePrivate)
{
    init();
}

HDiskSizeTable::HDiskSizeTable(HDiskSizeTablePrivate &p, QWidget *parent) :
    QTableWidget(parent),
    d_ptr(&p)
{
    init();
}

HDiskSizeTable::~HDiskSizeTable() = default;

QSize HDiskSizeTable::sizeHint() const
{
    return {500, 300};
}

QSize HDiskSizeTable::minimumSizeHint() const
{
    return {200, 150};
}

QColor HDiskSizeTable::background() const
{
    return d_ptr->background;
}

QColor HDiskSizeTable::chunkColor1() const
{
    return d_ptr->chunkColor1;
}

QColor HDiskSizeTable::chunkColor2() const
{
    return d_ptr->chunkColor2;
}

QColor HDiskSizeTable::chunkColor3() const
{
    return d_ptr->chunkColor3;
}

QColor HDiskSizeTable::textColor1() const
{
    return d_ptr->textColor1;
}

QColor HDiskSizeTable::textColor2() const
{
    return d_ptr->textColor2;
}

QColor HDiskSizeTable::textColor3() const
{
    return d_ptr->textColor3;
}

void HDiskSizeTable::load()
{
    clearContents();
    setRowCount(0);
#ifdef Q_OS_WIN
    for (const auto &dir : QDir::drives())
    {
        auto dirName = dir.absolutePath();
        auto driver = (LPCWSTR)dirName.utf16();
        ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
        if (GetDiskFreeSpaceEx(driver, &freeBytesAvailable, &totalBytes, &totalFreeBytes))
        {
            auto use = QString("%1G").arg((1.0 * totalBytes.QuadPart - totalFreeBytes.QuadPart) / GB, 0, 'f', 1);
            auto free = QString("%1G").arg(1.0 * totalFreeBytes.QuadPart / GB, 0, 'f', 1);
            auto all = QString("%1G").arg(1.0 * totalBytes.QuadPart / GB, 0, 'f', 1);
            auto percent = 100 - 100.0 * totalFreeBytes.QuadPart / totalBytes.QuadPart;
            insertSize(dirName, use, free, all, percent);
        }
    }
#else
    if (d_ptr->process->state() == QProcess::NotRunning)
        d_ptr->process->start("df -h");
#endif
}

void HDiskSizeTable::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    load();
}

void HDiskSizeTable::setChunkColor1(const QColor &value)
{
    if (d_ptr->chunkColor1 == value)
        return;
    d_ptr->chunkColor1 = value;
    load();
}

void HDiskSizeTable::setChunkColor2(const QColor &value)
{
    if (d_ptr->chunkColor2 == value)
        return;
    d_ptr->chunkColor2 = value;
    load();
}

void HDiskSizeTable::setChunkColor3(const QColor &value)
{
    if (d_ptr->chunkColor3 == value)
        return;
    d_ptr->chunkColor3 = value;
    load();
}

void HDiskSizeTable::setTextColor1(const QColor &value)
{
    if (d_ptr->textColor1 == value)
        return;
    d_ptr->textColor1 = value;
    load();
}

void HDiskSizeTable::setTextColor2(const QColor &value)
{
    if (d_ptr->textColor2 == value)
        return;
    d_ptr->textColor2 = value;
    load();
}

void HDiskSizeTable::setTextColor3(const QColor &value)
{
    if (d_ptr->textColor3 == value)
        return;
    d_ptr->textColor3 = value;
    load();
}

void HDiskSizeTable::insertSize(const QString &name, const QString &use, const QString &free, const QString &all, double percent)
{
    auto row = this->rowCount();
    this->insertRow(row);

    auto *item0 = new QTableWidgetItem(name);
    auto *item1 = new QTableWidgetItem(use);
    item1->setTextAlignment(Qt::AlignCenter);
    auto *item2 = new QTableWidgetItem(free);
    item2->setTextAlignment(Qt::AlignCenter);
    auto *item3 = new QTableWidgetItem(all);
    item3->setTextAlignment(Qt::AlignCenter);

    this->setItem(row, 0, item0);
    this->setItem(row, 1, item1);
    this->setItem(row, 2, item2);
    this->setItem(row, 3, item3);

    QString textColor, chunkColor;
    if (percent < 50)
    {
        textColor = d_ptr->textColor1.name();
        chunkColor = d_ptr->chunkColor1.name();
    }
    else if (percent < 90)
    {
        textColor = d_ptr->textColor2.name();
        chunkColor = d_ptr->chunkColor2.name();
    }
    else
    {
        textColor = d_ptr->textColor3.name();
        chunkColor = d_ptr->chunkColor3.name();
    }
    auto qss = QStringList() << QString("QProgressBar { background:%1; color:%2; border-width:0px; border-radius:0px; text-align:center; }").arg(d_ptr->background.name(), textColor)
                             << QString("QProgressBar::chunk { background:%1; border-radius:0px; }").arg(chunkColor);

    auto bar = new QProgressBar(this);
    bar->setRange(0, 100);
    bar->setValue(percent);
    bar->setStyleSheet(qss.join("\n"));
    this->setCellWidget(row, 4, bar);
}

void HDiskSizeTable::init()
{
#ifndef Q_OS_WIN
    d_ptr->process = new QProcess(this);
    connect(d_ptr->process, &QProcess::readyRead, this, &HDiskSizeTable::readData);
#endif
    // 设置列数和列宽
    setColumnCount(5);
    setColumnWidth(0, 100);
    setColumnWidth(1, 120);
    setColumnWidth(2, 120);
    setColumnWidth(3, 120);
    setColumnWidth(4, 120);
    setStyleSheet("QTableWidget::item { padding:0px; }");
    setHorizontalHeaderLabels(QStringList() << tr("盘符") << tr("已用空间") << tr("可用空间") << tr("总大小") << tr("已用百分比"));
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    verticalHeader()->setVisible(true);
    horizontalHeader()->setStretchLastSection(true);
    QMetaObject::invokeMethod(this, "load", Qt::QueuedConnection);
}

#ifndef Q_OS_WIN
void HDiskSizeTable::readData()
{
    while (!d_ptr->process->atEnd())
    {
        QString result = QLatin1String(d_ptr->process->readLine());
#ifdef __arm__
        if (result.startsWith("/dev/root"))
            checkSize(result, "本地存储");
        else if (result.startsWith("/dev/mmcblk"))
            checkSize(result, "本地存储");
        else if (result.startsWith("/dev/mmcblk1p"))
        {
            checkSize(result, "SD卡");
            emit sdcardReceive(result.split(" ").at(0));
        }
        else if (result.startsWith("/dev/sd"))
        {
            checkSize(result, "U盘");
            emit udiskReceive(result.split(" ").at(0));
        }
#else
        if (result.startsWith("/dev/sd"))
        {
            checkSize(result, "");
            emit udiskReceive(result.split(" ").at(0));
        }
#endif
    }
}

void HDiskSizeTable::checkSize(const QString &result, const QString &name)
{
    QString dev, use, free, all;
    int percent = 0;
    int index = 0;
    for (auto t : result.split(" "))
    {
        auto s = t.trimmed();
        if (s == "")
            continue;

        index++;
        if (index == 1)
            dev = s;
        else if (index == 2)
            all = s;
        else if (index == 3)
            use = s;
        else if (index == 4)
            free = s;
        else if (index == 5)
        {
            percent = s.left(s.length() - 1).toInt();
            break;
        }
    }
    if (name.length() > 0)
        dev = name;
    insertSize(dev, use, free, all, percent);
}
#endif

HE_END_NAMESPACE
