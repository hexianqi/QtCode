#include "MainWindow.h"
#include "HTestAlgorithm.h"
#include "HTestChart.h"
#include "HTestPlugin.h"
#include "HTestGsl.h"
#include "HTestWidget.h"
#include "HeExample/HTestTable.h"
#include <QtCore/QDebug>
#include <QtGui/QPolygonF>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableWidget>
#include <QtCharts/QChartView>
#include <functional>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");

//    auto widget = HTestTable::multHeaderTableWidget();
//    widget->show();

//    HTestWidget::multHeaderTableWidget()->show();

//    HTestPlugin::testCIE1931View()->show();

    HTestGsl gsl;
    auto p = gsl.interpEval();
    HTestChart::diffChart(p[0], p[1])->show();
//    HTestChart::vernierChart(p[0], p[1])->showMaximized();

//    QMainWindow window;
//    window.setCentralWidget(gsl.interpEval());
//    window.resize(800, 600);
//    window.grabGesture(Qt::PanGesture);
//    window.grabGesture(Qt::PinchGesture);
//    window.show();

    return a.exec();
}
