#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestChart.h"
#include "HTestPlugin.h"
#include "HTestGsl.h"
#include "HTestWidget.h"
#include "HeExample/HTestTable.h"
#include <QtCore/QDebug>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtGui/QPolygonF>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableWidget>
#include <QtCharts/QChartView>
#include <functional>
#include <cxxabi.h>

void testJson()
{
    QVariantMap map;
    map.insert("px", 0.1);
    map.insert("py", 5.1);
    auto json = QJsonObject::fromVariantMap(map);
    auto doc = QJsonDocument(json);
    auto text = QString(doc.toJson());
    auto byte = doc.toBinaryData();
    qDebug() << map;
    qDebug() << json;
    qDebug() << doc;
    qDebug() << text;
    qDebug() << byte;
}

void testVector()
{
    QVector<int> v;
    for (int i = 0; i < 10; i++)
        v << i+1;

    int pos = 0;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
    qDebug() << v[pos++] * 100 + v[pos++] << pos;
}

template <typename T>
class NameTemplate
{
public:
    QString name()
    {
        return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
//        return typeid(T).name();
    }
};

template <typename T>
QString name()
{
    return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}

void testTemplateName()
{
    NameTemplate<int> i;
    NameTemplate<double> d;
    NameTemplate<QString> s;
    NameTemplate<QPoint> p;
    NameTemplate<HTestGsl> c;
    qDebug() << i.name();
    qDebug() << d.name();
    qDebug() << s.name();
    qDebug() << p.name();
    qDebug() << c.name();
    qDebug() << name<int>();
    qDebug() << name<QString>();
    qDebug() << name<HTestGsl>();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");










//    auto widget = HTestTable::multHeaderTableWidget();
//    widget->show();

//    HTestWidget::multHeaderTableWidget()->show();

//    HTestPlugin::testCIE1931View()->show();

//    HTestGsl gsl;
//    auto p = gsl.interpEval();
//    HTestChart::diffChart(p[0], p[1])->show();
//    HTestChart::vernierChart(p[0], p[1])->showMaximized();

//    QMainWindow window;
//    window.setCentralWidget(gsl.interpEval());
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();

    return a.exec();
}
