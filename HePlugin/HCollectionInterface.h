#ifndef HCOLLECTIONINTERFACE_H
#define HCOLLECTIONINTERFACE_H

#include <QtDesigner>
#include <qplugin.h>

class HCollectionInterface : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")

public:
    explicit HCollectionInterface(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> _widgets;
};

#endif
