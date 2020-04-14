#include "HProgressBar_p.h"

HProgressBar::HProgressBar(QWidget *parent) :
    QProgressBar(parent),
    d_ptr(new HProgressBarPrivate)
{
    updateStyleSheet();
}

HProgressBar::HProgressBar(HProgressBarPrivate &p, QWidget *parent) :
    QProgressBar(parent),
    d_ptr(&p)
{
    updateStyleSheet();
}

HProgressBar::~HProgressBar() = default;

void HProgressBar::setOrientation(Qt::Orientation value)
{
    QProgressBar::setOrientation(value);
    updateStyleSheet();
}

void HProgressBar::setColorProgress(const QColor &value)
{
    d_ptr->color = value;
    updateStyleSheet();
}

QColor HProgressBar::colorProgress() const
{
    return d_ptr->color;
}

void HProgressBar::updateStyleSheet()
{
    QString text;
    text  = QString("QProgressBar { background-color:rgb(240, 240, 240); border:1px solid grey; border-radius:5px; text-align:center; }\n");
    text += QString("QProgressBar::chunk { width:20px; height:20px; margin:0.5px; background-color: qlineargradient(spread:reflect, x1:0, y1:0, ");
    text += orientation() == Qt::Horizontal ? "x2:0, y2:0.5, " : "x2:0.5, y2:0, ";
    text += QString("stop:0 rgba(%1, %2, %3, 0), stop:0.2 rgba(%1, %2, %3, 128), stop:1 rgba(%1, %2, %3, 255)); }\n").arg(d_ptr->color.red()).arg(d_ptr->color.green()).arg(d_ptr->color.blue());
    setStyleSheet(text);
}
