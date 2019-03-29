#include "HProgressBar_p.h"

HProgressBar::HProgressBar(QWidget *parent)
    : QProgressBar(parent), d_ptr(new HProgressBarPrivate)
{
    refreshStyleSheet();
}

HProgressBar::HProgressBar(HProgressBarPrivate &p, QWidget *parent)
    :  QProgressBar(parent), d_ptr(&p)
{
    refreshStyleSheet();
}

HProgressBar::~HProgressBar()
{
}

void HProgressBar::setOrientation(Qt::Orientation value)
{
    QProgressBar::setOrientation(value);
    refreshStyleSheet();
}

void HProgressBar::setColorProgress(QColor value)
{
    d_ptr->colorProgress = value;
    refreshStyleSheet();
}

QColor HProgressBar::colorProgress() const
{
    return d_ptr->colorProgress;
}

void HProgressBar::refreshStyleSheet()
{
    QString text;

    text = QString("QProgressBar {\n") +
            "background-color: rgb(240, 240, 240);\n" +
            "border: 1px solid grey;\n" +
            "border-radius: 5px;\n" +
            "text-align: center;\n}\n\n" +
            "QProgressBar::chunk {\n" +
            "width: 20px;\n" +
            "height: 20px;\n" +
            "margin: 0.5px;\n" +
            "background-color: qlineargradient(spread:reflect, x1:0, y1:0, ";
    text += orientation() == Qt::Horizontal ? "x2:0, y2:0.5, " : "x2:0.5, y2:0, ";
    text += QString("stop:0 rgba(%1, %2, %3, 0), stop:0.2 rgba(%1, %2, %3, 128), stop:1 rgba(%1, %2, %3, 255));\n}\n").arg(d_ptr->colorProgress.red()).arg(d_ptr->colorProgress.green()).arg(d_ptr->colorProgress.blue());
    setStyleSheet(text);
}
