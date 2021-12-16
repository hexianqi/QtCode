#include "HSeekStyle.h"
#include <QtGui/QPainter>
#include <QtWidgets/QStyleFactory>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

HSeekStyle::HSeekStyle() :
    QProxyStyle(QStyleFactory::create("Windows"))
{
}

int HSeekStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    if (widget)
    {
        auto slider = qstyleoption_cast<const QStyleOptionSlider *>(option);
        if (slider)
        {
            if (metric == QStyle::PM_SliderThickness || metric == QStyle::PM_SliderThickness)
                return widget->minimumSize().height();
        }
    }
    return QProxyStyle::pixelMetric(metric, option, widget);
}

void HSeekStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    if (control != CC_Slider)
    {
        qWarning() << "SeekStyle: Drawing an unmanaged control";
        return QProxyStyle::drawComplexControl(control, option, painter, widget);
    }

    auto options = qstyleoption_cast<const HSeekStyleOption *>(option);
    if (options == nullptr)
        return;

    auto radius = 3;
    auto chapterSpotSize = 3;
    auto sliderPos = -1;
    // Get the needed subcontrols to draw the slider
    auto groove = subControlRect(CC_Slider, options, SC_SliderGroove, widget);
    auto handle = subControlRect(CC_Slider, options, SC_SliderHandle, widget);
    // Adjust the size of the groove so the handle stays centered
    groove.adjust(handle.width() / 2, 0, -handle.width() / 2, 0);
    // Reduce the height of the groove
    // Note: in the original 2.0.0 code, the groove had a height of 9px and to
    // comply with the original style (but still allow the widget to expand) I
    // had to remove 1 from the rect bottom.
    groove.adjust(0, groove.height() / 3.7, 0, -groove.height() / 3.7 - 1);

    painter->setRenderHints(QPainter::Antialiasing);
    if (options->subControls & SC_SliderGroove && groove.isValid())
    {
        sliderPos = 1.0 * groove.width() * options->sliderPosition / options->maximum;
        // set the background color and gradient
        auto background = options->palette.window().color();
        auto backgroundGradient = QLinearGradient(0, 0, 0, options->rect.height());
        backgroundGradient.setColorAt(0.0, background.darker(140));
        backgroundGradient.setColorAt(1.0, background);

        // set the foreground color and gradient
        auto foreground = QColor(50, 156, 255);
        auto foregroundGradient = QLinearGradient(0, 0, 0, groove.height());
        foregroundGradient.setColorAt(0.0, foreground);
        foregroundGradient.setColorAt(1.0, foreground.darker(125));

        // draw a slight 3d effect on the bottom
        painter->setPen(QColor(230, 230, 230));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(groove.adjusted(0, 2, 0, 0), radius, radius);
        // draw background
        painter->setPen(Qt::NoPen);
        painter->setBrush(backgroundGradient);
        painter->drawRoundedRect(groove, radius, radius);
        // draw foreground
        if (options->sliderPosition > options->minimum && options->sliderPosition <= options->maximum)
        {
            // adjusted foreground rectangle
            auto rect = groove.adjusted(1, 1, -1, 0);
            rect.setWidth(sliderPos);
            painter->setPen(Qt::NoPen);
            painter->setBrush(foregroundGradient);
            painter->drawRoundedRect(rect, radius, radius);
        }

        // draw buffering overlay
        if (options->buffering == 0.0 && options->loading > 0.0)
        {
            auto width = groove.width() * 5 / 6;
            auto rect = groove.adjusted(options->loading * width + 1, 1, (options->loading - 1) * width - 1, 0);
            painter->setBrush(QColor(255, 165, 0, 128));
            painter->drawRoundedRect(rect, radius, radius);
        }
        if (options->buffering > 0.0 && options->buffering < 1.0 )
        {
            auto rect = groove.adjusted(1, 1, (options->buffering - 1) * groove.width() - 1, 0);
            painter->setBrush(QColor(255, 165, 0, 128));
            painter->drawRoundedRect(rect, radius, radius);
        }
    }

    if (options->subControls & SC_SliderTickmarks )
    {
        auto temp = *options;
        temp.subControls = SC_SliderTickmarks;
        QProxyStyle::drawComplexControl(control, &temp, painter, widget);
    }

    if (options->subControls & SC_SliderHandle && handle.isValid())
    {
        if (options->state & QStyle::State_MouseOver || options->animate)
        {
            auto palette = options->palette;
            // draw chapters tickpoints
            if (options->points.size() && options->length && groove.width())
            {
                auto background = palette.color(QPalette::Active, QPalette::Window);
                auto foreground = palette.color(QPalette::Active, QPalette::WindowText);
                foreground.setHsv(foreground.hue(), (background.saturation() + foreground.saturation()) / 2, (background.value() + foreground.value()) / 2);
                if (options->orientation == Qt::Horizontal ) // TODO: vertical
                {
                    for (auto time : options->points)
                    {
                        auto x = groove.x() + groove.width() * time / 1000000.0 / options->length;
                        painter->setPen(foreground);
                        painter->setBrush(Qt::NoBrush);
                        painter->drawLine(x, options->rect.height(), x, options->rect.height() - chapterSpotSize);
                    }
                }
            }
            // draw handle
            if (options->state & QStyle::State_Enabled && sliderPos != -1)
            {
                auto hSize = QSize(handle.height(), handle.height()) - QSize(6, 6);
                auto sSize = QSize(handle.height(), handle.height()) - QSize(2, 2);
                auto pos = handle.center() - QPoint(hSize.width() / 2, hSize.height() / 2);
                auto shadowPos = pos - QPoint(2, 2);

                // prepare the handle's gradient */
                auto handleGradient = QLinearGradient(0, 0, 0, hSize.height());
                handleGradient.setColorAt(0.0, palette.window().color().lighter(120));
                handleGradient.setColorAt(0.9, palette.window().color().darker(120));

                // prepare the handle's shadow gradient
                QColor shadowColor = palette.shadow().color();
                if (shadowColor.lightness() > 100)       // Palette's shadow is too bright
                    shadowColor = QColor(60, 60, 60);
                QColor shadowDark(shadowColor.darker(150));
                QColor shadowLight(shadowColor.lighter(180 ));
                shadowLight.setAlpha(50);

                auto shadowGradient = QRadialGradient(shadowPos + QPoint(sSize.width() / 2, sSize.height() / 2), qMax(sSize.width(), sSize.height()) / 2);
                shadowGradient.setColorAt(0.4, shadowDark);
                shadowGradient.setColorAt(1.0, shadowLight);

                painter->setPen( Qt::NoPen );
                painter->setOpacity(options->opacity);
                // draw the handle's shadow
                painter->setBrush(shadowGradient);
                painter->drawEllipse(shadowPos.x(), shadowPos.y() + 1, sSize.width(), sSize.height());
                // draw the handle
                painter->setBrush(handleGradient);
                painter->drawEllipse(pos.x(), pos.y(), hSize.width(), hSize.height());
            }
        }
    }
}

HE_END_NAMESPACE


