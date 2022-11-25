#include "HProcessDisplayWidget_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HProcessDisplayWidget::HProcessDisplayWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HProcessDisplayWidgetPrivate)
{
    setPalette(Qt::white);
}

HProcessDisplayWidget::~HProcessDisplayWidget()
{
}

void HProcessDisplayWidget::setProcess(const QStringList &value)
{
    if (d_ptr->processs == value)
        return;
    d_ptr->processs = value;
    update();
}

void HProcessDisplayWidget::setCurrentStep(int value)
{
    if (d_ptr->currentStep == value)
        return;
    d_ptr->currentStep = value;
    update();
}

void HProcessDisplayWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QColor *color;
    auto font = painter.font();
    font.setPixelSize(20);
    font.setBold(true);

    int lineY = static_cast<int>(height() * 0.3) ;
    int startX = 80;
    int radius = 20;
    int size = d_ptr->processs.size();
    int spacer = (width() - 2 * startX - (radius * 2 * size)) / (size - 1);
    QRect textRect = QRect(0, 0, spacer + radius * 2, height() - lineY - radius * 2);

    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(font);

    for (int i = 0; i < size; i++)
    {
        int x = startX + radius + spacer * i + radius * 2 * i;
        int y = radius + (height() + lineY) / 2;
        if (i == 0 || i == size - 1)
            textRect.setWidth(2 * (startX - 20 + radius));
        else
            textRect.setWidth(spacer + radius * 2);
        textRect.moveCenter(QPoint(x, y));

        if (i < size - 1)
        {
            if (i < d_ptr->currentStep)
                color = &d_ptr->completedStepsColor;
            else
                color = &d_ptr->lineColor;
            painter.setPen(QPen(*color,3));
            painter.drawLine(x + radius, lineY, x + radius + spacer, lineY);
        }

        if (i < d_ptr->currentStep)
            color = &d_ptr->completedStepsColor;
        else if(i == d_ptr->currentStep)
            color = &d_ptr->currentStepColor;
        else
            color = &d_ptr->uncompleteStepColor;

        drawSmallCircle(&painter, x, lineY + 1, radius, *color, QString::number(i + 1));

        painter.setPen(*color);
        painter.drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, d_ptr->processs[i]);
    }
    painter.restore();
}

void HProcessDisplayWidget::drawSmallCircle(QPainter *painter, int x, int y, int radius, const QColor &color, const QString &text)
{
    auto rect = QRect(-radius, -radius, radius * 2, radius * 2);
    QLinearGradient linearGradient(rect.topLeft(), rect.bottomRight());
    linearGradient.setColorAt(0.0, color);
    linearGradient.setColorAt(1.0, color.lighter());

    painter->save();
    painter->translate(x,y);
    painter->setBrush(linearGradient);
    painter->setPen(QPen(QBrush(linearGradient), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));//渐变线
    painter->drawEllipse(rect);
    painter->setBrush(Qt::white);
    painter->drawEllipse(rect.adjusted(1, 1, -1, -1));
    painter->setPen(color);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

HE_END_NAMESPACE
