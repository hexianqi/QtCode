/***************************************************************************************************
**      2022-06-23  HDoubleSpinBoxFactory
***************************************************************************************************/

#pragma once

#include "qtpropertybrowser.h"
#include "HDoublePropertyManager.h"

class HDoubleSpinBoxFactoryPrivate;

class HDoubleSpinBoxFactory : public QtAbstractEditorFactory<HDoublePropertyManager>
{
    Q_OBJECT

public:
    explicit HDoubleSpinBoxFactory(QObject *parent = nullptr);
    ~HDoubleSpinBoxFactory() override;

protected:
    HDoubleSpinBoxFactory(HDoubleSpinBoxFactoryPrivate &p, QObject *parent = nullptr);

protected:
    void connectPropertyManager(HDoublePropertyManager *manager) override;
    void disconnectPropertyManager(HDoublePropertyManager *manager) override;
    QWidget *createEditor(HDoublePropertyManager *manager, QtProperty *property, QWidget *parent) override;
    void init();

protected slots:
    void slotPrefixChanged(QtProperty *property, const QString &prefix);
    void slotSuffixChanged(QtProperty *property, const QString &suffix);
    void slotEditorDestroyed(QObject *object);

protected:
    QScopedPointer<HDoubleSpinBoxFactoryPrivate> d_ptr;
};
