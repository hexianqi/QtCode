#include "HCodeCountWidget_p.h"
#include "ui_HCodeCountWidget.h"
#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QtWidgets/QFileDialog>

HE_CONTROL_BEGIN_NAMESPACE

HCodeCountWidget::HCodeCountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HCodeCountWidget),
    d_ptr(new HCodeCountWidgetPrivate)
{
    ui->setupUi(this);
    init();
    clear();
}

HCodeCountWidget::~HCodeCountWidget()
{
    delete ui;
}

void HCodeCountWidget::on_pushButton_1_clicked()
{
    auto filter = QString("代码文件(%1)").arg(ui->lineEdit_09->text().trimmed());
    auto files = QFileDialog::getOpenFileNames(this, tr("选择文件"), "./", filter);
    if (files.isEmpty())
        return;
    ui->lineEdit_07->setText(files.join("|"));
    countCode(files);
}

void HCodeCountWidget::on_pushButton_2_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this, tr("选择目录"), "./",  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (path.isEmpty())
        return;
    ui->lineEdit_08->setText(path);
    auto files = countCode(path);
    countCode(files);
}

void HCodeCountWidget::on_pushButton_3_clicked()
{
    clear();
}

void HCodeCountWidget::init()
{
    auto head = QStringList() << tr("文件名") << tr("类型") << tr("大小") << tr("总行数") << tr("代码行数") << tr("注释行数") << tr("空白行数") << tr("路径");
    auto columnWidth = QList<int>() << 130 << 50 << 70 << 80 << 70 << 70 << 70 << 150;
    auto columnCount = head.count();

    ui->tableWidget->setColumnCount(columnCount);
    ui->tableWidget->setHorizontalHeaderLabels(head);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(60);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(30);
    ui->tableWidget->verticalHeader()->setHighlightSections(false);
    ui->tableWidget->verticalHeader()->setMinimumSectionSize(30);

    for (int i = 0; i < columnCount; i++)
        ui->tableWidget->setColumnWidth(i, columnWidth.at(i));

    // 设置前景色
    ui->lineEdit_01->setStyleSheet("color:#17A086;");
    ui->lineEdit_02->setStyleSheet("color:#CA5AA6;");
    ui->lineEdit_03->setStyleSheet("color:#CD1B19;");
    ui->lineEdit_04->setStyleSheet("color:#22A3A9;");
    ui->lineEdit_05->setStyleSheet("color:#D64D54;");
    ui->lineEdit_06->setStyleSheet("color:#A279C5;");

    // 设置字体加粗
    auto f = font();
    f.setBold(true);
    if (f.pointSize() > 0)
        f.setPointSize(f.pointSize() + 1);
    else
        f.setPixelSize(f.pixelSize() + 2);

    ui->lineEdit_01->setFont(f);
    ui->lineEdit_02->setFont(f);
    ui->lineEdit_03->setFont(f);
    ui->lineEdit_04->setFont(f);
    ui->lineEdit_05->setFont(f);
    ui->lineEdit_06->setFont(f);
    ui->lineEdit_09->setPlaceholderText(tr("中间空格隔开,例如 *.h *.cpp *.c"));
    setWindowTitle(tr("代码行数统计"));
}

void HCodeCountWidget::clear()
{
    ui->lineEdit_01->setText("0");
    ui->lineEdit_02->setText("0");
    ui->lineEdit_03->setText("0");
    ui->lineEdit_04->setText("0");
    ui->lineEdit_05->setText("0");
    ui->lineEdit_06->setText("0");
    ui->label_11->setText("0%");
    ui->label_12->setText("0%");
    ui->label_13->setText("0%");
    ui->tableWidget->setRowCount(0);
}

bool HCodeCountWidget::checkFile(const QString &file)
{
    if (file.startsWith("moc_") || file.startsWith("ui_") || file.startsWith("qrc_"))
        return false;

    auto info = QFileInfo(file);
    auto suffix = "*." + info.suffix();
    return ui->lineEdit_09->text().trimmed().split(" ").contains(suffix);
}

QStringList HCodeCountWidget::countCode(const QString &path)
{
    QStringList files;
    auto dir = QDir(path);
    for (const auto &info : dir.entryInfoList())
    {
        if (info.isFile())
        {
            auto file = info.fileName();
            if (checkFile(file))
                files << info.filePath();
        }
        else
        {
            if(info.fileName() == "." || info.fileName() == "..")
                continue;
            files << countCode(info.absoluteFilePath());
        }
    }
    return files;
}

void HCodeCountWidget::countCode(const QStringList &files)
{
    quint32 lineCode = 0;
    quint32 lineBlank = 0;
    quint32 lineNotes = 0;
    quint32 totalLines = 0;
    quint32 totalBytes = 0;
    quint32 totalCodes = 0;
    quint32 totalNotes = 0;
    quint32 totalBlanks = 0;
    auto count = files.count();

    clear();
    ui->tableWidget->setRowCount(count);

    for (int i = 0; i < count; i++)
    {
        auto info = QFileInfo(files.at(i));
        countCode(info.filePath(), lineCode, lineBlank, lineNotes);
        auto lineAll = lineCode + lineBlank + lineNotes;
        auto itemName = new QTableWidgetItem(info.fileName());
        auto itemSuffix = new QTableWidgetItem(info.suffix());
        auto itemSize = new QTableWidgetItem(QString::number(info.size()));
        auto itemLine = new QTableWidgetItem(QString::number(lineAll));
        auto itemCode = new QTableWidgetItem(QString::number(lineCode));
        auto itemNote = new QTableWidgetItem(QString::number(lineNotes));
        auto itemBlank = new QTableWidgetItem(QString::number(lineBlank));
        auto itemPath = new QTableWidgetItem(info.filePath());
        itemSuffix->setTextAlignment(Qt::AlignCenter);
        itemSize->setTextAlignment(Qt::AlignCenter);
        itemLine->setTextAlignment(Qt::AlignCenter);
        itemCode->setTextAlignment(Qt::AlignCenter);
        itemNote->setTextAlignment(Qt::AlignCenter);
        itemBlank->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 0, itemName);
        ui->tableWidget->setItem(i, 1, itemSuffix);
        ui->tableWidget->setItem(i, 2, itemSize);
        ui->tableWidget->setItem(i, 3, itemLine);
        ui->tableWidget->setItem(i, 4, itemCode);
        ui->tableWidget->setItem(i, 5, itemNote);
        ui->tableWidget->setItem(i, 6, itemBlank);
        ui->tableWidget->setItem(i, 7, itemPath);
        totalBytes  += info.size();
        totalLines  += lineAll;
        totalCodes  += lineCode;
        totalNotes  += lineNotes;
        totalBlanks += lineBlank;
        if (i % 100 == 0)
            QApplication::processEvents();
    }

    // 显示统计结果
    ui->lineEdit_01->setText(QString::number(count));
    ui->lineEdit_02->setText(QString::number(totalBytes));
    ui->lineEdit_03->setText(QString::number(totalLines));
    ui->lineEdit_04->setText(QString::number(totalCodes));
    ui->lineEdit_05->setText(QString::number(totalNotes));
    ui->lineEdit_06->setText(QString::number(totalBlanks));
    ui->label_11->setText(QString("%1%").arg(100.0 * totalCodes / totalLines, 5, 'f', 2, QChar(' ')));
    ui->label_12->setText(QString("%1%").arg(100.0 * totalNotes / totalLines, 5, 'f', 2, QChar(' ')));
    ui->label_13->setText(QString("%1%").arg(100.0 * totalBlanks / totalLines, 5, 'f', 2, QChar(' ')));
}

void HCodeCountWidget::countCode(const QString &file, quint32 &lineCode, quint32 &lineBlank, quint32 &lineNotes)
{
    lineCode = lineBlank = lineNotes = 0;
    QFile f(file);
    if (!f.open(QFile::ReadOnly))
        return;

    QTextStream out(&f);
    QString line;
    auto isNote = false;
    while (!out.atEnd())
    {
        line = out.readLine();

        // 移除前面的空行
        if (line.startsWith(" "))
            line.remove(" ");
        // 判断当前行是否是注释
        if (line.startsWith("/*"))
            isNote = true;
        // 注释部分
        if (!isNote)
        {
            // 注释行
            if (line.startsWith("//"))
                lineNotes++;
            // 空白行
            else if (line.isEmpty())
                lineBlank++;
            // 代码行
            else
                lineCode++;
        }
        else
            lineNotes++;

        // 注释结束
        if (line.endsWith("*/"))
            isNote = false;
    }
}

HE_CONTROL_END_NAMESPACE
