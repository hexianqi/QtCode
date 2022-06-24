#include "HDemoWidget.h"
#include "HPointFPropertyManager.h"
#include "HDoubleSpinBoxFactory.h"
#include <qteditorfactory.h>
#include <qtpropertymanager.h>
#include <qtbuttonpropertybrowser.h>
#include <qtgroupboxpropertybrowser.h>
#include <qttreepropertybrowser.h>
#include <QtCore/QMap>
#include <QtGui/QIcon>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>

HDemoWidget::HDemoWidget(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void HDemoWidget::init()
{
    auto groupManager = new QtGroupPropertyManager(this);
    auto stringManager = new QtStringPropertyManager(this);
    auto boolManager = new QtBoolPropertyManager(this);
    auto rectManager = new QtRectPropertyManager(this);
    auto sizePolicyManager = new QtSizePolicyPropertyManager(this);
    auto sizeManager = new QtSizePropertyManager(this);
    auto enumManager = new QtEnumPropertyManager(this);
    auto intManager = new QtIntPropertyManager(this);
    auto doubleManager = new QtDoublePropertyManager(this);
    auto pointManager = new HPointFPropertyManager(this);
    auto variantManager = qobject_cast<QtVariantPropertyManager *>(pointManager);
    auto doubleManager2 = new HDoublePropertyManager(this);

    auto item0 = groupManager->addProperty("QObject");
    auto item1 = stringManager->addProperty("objectName");
    item0->addSubProperty(item1);
    auto item2 = boolManager->addProperty("enabled");
    item0->addSubProperty(item2);
    auto item3 = boolManager->addProperty("mouseTracking");
    item0->addSubProperty(item3);
    auto item4 = rectManager->addProperty("geometry");
    item0->addSubProperty(item4);
    auto item5 = sizePolicyManager->addProperty("sizePolicy");
    item0->addSubProperty(item5);
    auto item6 = sizeManager->addProperty("sizeIncrement");
    item0->addSubProperty(item6);
    auto item7 = intManager->addProperty("intValue");
    intManager->setRange(item7, -100, 100);
    item0->addSubProperty(item7);
    auto item8 = enumManager->addProperty("direction");
    enumManager->setEnumNames(item8, QStringList() << "Up" << "Right" << "Down" << "Left");
    QMap<int, QIcon> enumIcons;
    enumIcons[0] = QIcon(":/images/up.png");
    enumIcons[1] = QIcon(":/images/right.png");
    enumIcons[2] = QIcon(":/images/down.png");
    enumIcons[3] = QIcon(":/images/left.png");
    enumManager->setEnumIcons(item8, enumIcons);
    item0->addSubProperty(item8);
    auto item9 = doubleManager->addProperty("doubleValue");
    doubleManager->setValue(item9, 123.45);
    item0->addSubProperty(item9);

    auto item11 = pointManager->addProperty(QVariant::PointF, "PointF Property");
    item11->setValue(QPointF(2.5, 13.13));
    item0->addSubProperty(item11);
    auto item12 = doubleManager2->addProperty("doubleValue2");
    doubleManager2->setPrefix(item12, "speed: ");
    doubleManager2->setSuffix(item12, " km/h");
    doubleManager2->setValue(item12, 123.45);
    item0->addSubProperty(item12);

    auto checkBoxFactory = new QtCheckBoxFactory(this);
    auto spinBoxFactory = new QtSpinBoxFactory(this);
    auto sliderFactory = new QtSliderFactory(this);
    auto scrollBarFactory = new QtScrollBarFactory(this);
    auto lineEditFactory = new QtLineEditFactory(this);
    auto comboBoxFactory = new QtEnumEditorFactory(this);
    auto variantFactory = new QtVariantEditorFactory(this);
    auto doubleFactory = new QtDoubleSpinBoxFactory(this);
    auto doubleFactory2 = new HDoubleSpinBoxFactory(this);

    auto editor1 = new QtTreePropertyBrowser();
    editor1->setFactoryForManager(boolManager, checkBoxFactory);
    editor1->setFactoryForManager(intManager, spinBoxFactory);
    editor1->setFactoryForManager(stringManager, lineEditFactory);
    editor1->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    editor1->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    editor1->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
    editor1->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    editor1->setFactoryForManager(enumManager, comboBoxFactory);
    editor1->setFactoryForManager(variantManager, variantFactory);
    editor1->setFactoryForManager(doubleManager, doubleFactory);
    editor1->setFactoryForManager(doubleManager2, doubleFactory2);
    editor1->addProperty(item0);

    auto editor2 = new QtTreePropertyBrowser();
    editor2->addProperty(item0);

    auto editor3 = new QtGroupBoxPropertyBrowser();
    editor3->setFactoryForManager(boolManager, checkBoxFactory);
    editor3->setFactoryForManager(intManager, spinBoxFactory);
    editor3->setFactoryForManager(stringManager, lineEditFactory);
    editor3->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    editor3->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    editor3->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
    editor3->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    editor3->setFactoryForManager(enumManager, comboBoxFactory);
    editor3->addProperty(item0);
    auto scroll3 = new QScrollArea();
    scroll3->setWidgetResizable(true);
    scroll3->setWidget(editor3);

    auto editor4 = new QtGroupBoxPropertyBrowser();
    editor4->addProperty(item0);
    auto scroll4 = new QScrollArea();
    scroll4->setWidgetResizable(true);
    scroll4->setWidget(editor4);

    auto editor5 = new QtButtonPropertyBrowser();
    editor5->setFactoryForManager(boolManager, checkBoxFactory);
    editor5->setFactoryForManager(intManager, scrollBarFactory);
    editor5->setFactoryForManager(stringManager, lineEditFactory);
    editor5->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    editor5->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    editor5->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), sliderFactory);
    editor5->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    editor5->setFactoryForManager(enumManager, comboBoxFactory);
    editor5->addProperty(item0);
    auto scroll5 = new QScrollArea();
    scroll5->setWidgetResizable(true);
    scroll5->setWidget(editor5);

    auto list = QStringList() << "Editable Tree Property Browser"
                              << "Read Only Tree Property Browser, editor factories are not set"
                              << "Group Box Property Browser"
                              << "Group Box Property Browser with different editor factories"
                              << "Button Property Browser";
    auto layout = new QGridLayout(this);
    for (int i = 0; i < list.size(); i++)
    {
        auto label = new QLabel(list.at(i));
        label->setWordWrap(true);
        label->setFrameShadow(QFrame::Sunken);
        label->setFrameShape(QFrame::Panel);
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label, 0, i);
    }
    layout->addWidget(editor1, 1, 0);
    layout->addWidget(editor2, 1, 1);
    layout->addWidget(scroll3, 1, 2);
    layout->addWidget(scroll4, 1, 3);
    layout->addWidget(scroll5, 1, 4);
}
