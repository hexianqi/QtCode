/***************************************************************************************************
**      2018-06-19  HCartesianWidget 笛卡尔坐标系窗口部件。支持缩放。
***************************************************************************************************/

#ifndef HCARTESIANWIDGET_H
#define HCARTESIANWIDGET_H

#include "HDiagramWidget.h"

class HCartesianWidgetPrivate;
class HCartesianZoom;
class HCartesianCoordinate;

class QDESIGNER_WIDGET_EXPORT HCartesianWidget : public HDiagramWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCartesianWidget)
    Q_PROPERTY(bool enableZoom READ isEnableZoom WRITE setEnableZoom)
    Q_PROPERTY(bool unitInRuler READ isUnitInRuler WRITE setUnitInRuler)
    Q_PROPERTY(QString unitX READ unitX WRITE setUnitX)
    Q_PROPERTY(QString unitY READ unitY WRITE setUnitY)

public:
    explicit HCartesianWidget(QWidget *parent = nullptr);
    ~HCartesianWidget() override ;

public:
    void setCoordinate(HCartesianCoordinate *);
    void setEnableZoom(bool b);
    void setUnitInRuler(bool b);
    void setUnitX(QString value);
    void setUnitY(QString value);

public:
    bool isEnableZoom();
    bool isUnitInRuler();
    QString unitX();
    QString unitY();

protected:
    HCartesianWidget(HCartesianWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *) override;
    virtual bool drawRuler(QPainter *painter) override;
    virtual bool drawGrid(QPainter *painter) override;
    virtual bool drawPolygon(QPainter *painter) override;

protected slots:
    virtual void handleCoordinateChanged(HCartesianCoordinate *);

private:
    void init();
};

#endif // HCARTESIANWIDGET_H
