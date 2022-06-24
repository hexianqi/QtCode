#include "HDoubleSpinBoxFactory_p.h"

#include "qteditorfactory.h"
#include <QtWidgets/QDoubleSpinBox>

HDoubleSpinBoxFactory::HDoubleSpinBoxFactory(QObject *parent) :
    QtAbstractEditorFactory<HDoublePropertyManager>(parent),
    d_ptr(new HDoubleSpinBoxFactoryPrivate)
{
    init();
}

HDoubleSpinBoxFactory::HDoubleSpinBoxFactory(HDoubleSpinBoxFactoryPrivate &p, QObject *parent) :
    QtAbstractEditorFactory<HDoublePropertyManager>(parent),
    d_ptr(&p)
{
    init();
}

HDoubleSpinBoxFactory::~HDoubleSpinBoxFactory() = default;

void HDoubleSpinBoxFactory::connectPropertyManager(HDoublePropertyManager *manager)
{
    d_ptr->factory->addPropertyManager(manager);
    connect(manager, &HDoublePropertyManager::prefixChanged, this, &HDoubleSpinBoxFactory::slotPrefixChanged);
    connect(manager, &HDoublePropertyManager::suffixChanged, this, &HDoubleSpinBoxFactory::slotSuffixChanged);
}

void HDoubleSpinBoxFactory::disconnectPropertyManager(HDoublePropertyManager *manager)
{
    d_ptr->factory->removePropertyManager(manager);
    disconnect(manager, &HDoublePropertyManager::prefixChanged, this, &HDoubleSpinBoxFactory::slotPrefixChanged);
    disconnect(manager, &HDoublePropertyManager::suffixChanged, this, &HDoubleSpinBoxFactory::slotSuffixChanged);
}

QWidget *HDoubleSpinBoxFactory::createEditor(HDoublePropertyManager *manager, QtProperty *property, QWidget *parent)
{
    auto base = qobject_cast<QtAbstractEditorFactoryBase *>(d_ptr->factory);
    auto widget = base->createEditor(property, parent);
    auto spinBox = qobject_cast<QDoubleSpinBox *>(widget);
    if (spinBox == nullptr)
        return nullptr;

    spinBox->setPrefix(manager->prefix(property));
    spinBox->setSuffix(manager->suffix(property));

    d_ptr->propertyToEditor[property].append(spinBox);
    d_ptr->editorToProperty[spinBox] = property;
    connect(spinBox, &QDoubleSpinBox::destroyed, this, &HDoubleSpinBoxFactory::slotEditorDestroyed);
    return spinBox;
}

void HDoubleSpinBoxFactory::init()
{
    d_ptr->factory = new QtDoubleSpinBoxFactory(this);
}

void HDoubleSpinBoxFactory::slotPrefixChanged(QtProperty *property, const QString &prefix)
{
    if (!d_ptr->propertyToEditor.contains(property))
        return;

    auto manager = propertyManager(property);
    if (!manager)
        return;

    auto editors = d_ptr->propertyToEditor[property];
    for (auto editor : editors)
        editor->setPrefix(prefix);
}

void HDoubleSpinBoxFactory::slotSuffixChanged(QtProperty *property, const QString &suffix)
{
    if (!d_ptr->propertyToEditor.contains(property))
        return;

    auto manager = propertyManager(property);
    if (!manager)
        return;

    auto editors = d_ptr->propertyToEditor[property];
    for (auto editor : editors)
        editor->setSuffix(suffix);
}

void HDoubleSpinBoxFactory::slotEditorDestroyed(QObject *object)
{
    for (auto it = d_ptr->editorToProperty.constBegin(); it != d_ptr->editorToProperty.constEnd(); it++)
    {
        if (it.key() == object)
        {
            auto editor = it.key();
            auto property = it.value();
            d_ptr->editorToProperty.remove(editor);
            d_ptr->propertyToEditor[property].removeAll(editor);
            if (d_ptr->propertyToEditor[property].isEmpty())
                d_ptr->propertyToEditor.remove(property);
            return;
        }
    }
}



