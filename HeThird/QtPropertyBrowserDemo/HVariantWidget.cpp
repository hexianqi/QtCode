#include "HVariantWidget.h"
#include <qtvariantproperty.h>
#include <qttreepropertybrowser.h>
#include <QtCore/QDateTime>
#include <QtCore/QLocale>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLayout>
#include <QtCore/QDebug>

HVariantWidget::HVariantWidget(QWidget *parent) :
    QWidget(parent)
{
    init();
}

HVariantWidget::~HVariantWidget() = default;

void HVariantWidget::init()
{
    auto manager = new QtVariantPropertyManager(this);
    auto topItem = manager->addProperty(QtVariantPropertyManager::groupTypeId(), "Group Property");

    auto item = manager->addProperty(QVariant::Bool, "Bool Property");
    item->setValue(true);
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Int, "Int Property");
    item->setValue(20);
    item->setAttribute("minimum", 0);
    item->setAttribute("maximum", 100);
    item->setAttribute("singleStep", 10);
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Double, "Double Property");
    item->setValue(1.2345);
    item->setAttribute("singleStep", 0.1);
    item->setAttribute("decimals", 3);
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::String, "String Property");
    item->setValue("Value");
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::String, "String Property (Password)");
    item->setAttribute("echoMode", QLineEdit::Password);
    item->setValue("Password");
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Date, "Date Property");
    item->setValue(QDate::currentDate().addDays(2));
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Time, "Time Property");
    item->setValue(QTime::currentTime());
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::DateTime, "DateTime Property");
    item->setValue(QDateTime::currentDateTime());
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::KeySequence, "KeySequence Property");
    item->setValue(QKeySequence(Qt::ControlModifier | Qt::Key_Q));
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Char, "Char Property");
    item->setValue(QChar(386));
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Locale, "Locale Property");
    item->setValue(QLocale(QLocale::Polish, QLocale::Poland));
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Point, "Point Property");
    item->setValue(QPoint(10, 10));
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::PointF, "PointF Property");
    item->setValue(QPointF(1.2345, -1.23451));
    item->setAttribute("decimals", 3);
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Size, "Size Property");
    item->setValue(QSize(20, 20));
    item->setAttribute("minimum", QSize(10, 10));
    item->setAttribute("maximum", QSize(30, 30));
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::SizeF, "SizeF Property");
    item->setValue(QSizeF(1.2345, 1.2345));
    item->setAttribute("decimals", 3);
    item->setAttribute("minimum", QSizeF(0.12, 0.34));
    item->setAttribute("maximum", QSizeF(20.56, 20.78));
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Rect, "Rect Property");
    item->setValue(QRect(10, 10, 20, 20));
    topItem->addSubProperty(item);
    item->setAttribute("constraint", QRect(0, 0, 50, 50));

    item = manager->addProperty(QVariant::RectF, "RectF Property");
    item->setValue(QRectF(1.2345, 1.2345, 1.2345, 1.2345));
    topItem->addSubProperty(item);
    item->setAttribute("constraint", QRectF(0, 0, 50, 50));
    item->setAttribute("decimals", 3);

    item = manager->addProperty(QtVariantPropertyManager::enumTypeId(), "Enum Property");
    item->setAttribute("enumNames", QStringList() << "Enum0" << "Enum1" << "Enum2");
    item->setValue(1);
    topItem->addSubProperty(item);

    item = manager->addProperty(QtVariantPropertyManager::flagTypeId(), "Flag Property");
    item->setAttribute("flagNames", QStringList() << "Flag0" << "Flag1" << "Flag2");
    item->setValue(5);
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::SizePolicy, "SizePolicy Property");
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Font, "Font Property");
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Cursor, "Cursor Property");
    topItem->addSubProperty(item);

    item = manager->addProperty(QVariant::Color, "Color Property");
    topItem->addSubProperty(item);

    auto factory = new QtVariantEditorFactory(this);
    auto browser = new QtTreePropertyBrowser(this);
    browser->setFactoryForManager(manager, factory);
    browser->addProperty(topItem);
    browser->setPropertiesWithoutValueMarked(true);
    browser->setRootIsDecorated(false);
    auto layout = new QHBoxLayout(this);
    layout->addWidget(browser);

    for (auto p : topItem->subProperties())
        qDebug() << p->propertyName() << " = " << manager->value(p);
}
