/***************************************************************************************************
**      2018-06-19  HCartesianCoordinate 笛卡尔坐标系。
***************************************************************************************************/

#ifndef HCARTESIANCOORDINATE_H
#define HCARTESIANCOORDINATE_H

#include <QtCore/QObject>

class HCartesianCoordinatePrivate;

class HCartesianCoordinate : public QObject
{
    Q_OBJECT

public:
    explicit HCartesianCoordinate(QObject *parent = nullptr);
    ~HCartesianCoordinate() override;

public:
    // 位置转换
    static QPointF map(QPointF data, QRectF target, QRectF source);
    static QPolygonF map(QPolygonF data, QRectF target, QRectF source);
    static QRectF map(QRectF data, QRectF target, QRectF source);
    // 计算合适的坐标轴
    static void adjustAxis(double &min, double &max, int &tick);

public:
    void setAxis(QRectF rect);
    void setAxis(QRectF rect, int tickX, int tickY);
    void setAxis(double minX, double maxX, double minY, double maxY, int tickX = -1, int tickY = -1);

public:
    QRectF axis() const;
    int tickX() const;
    int tickY() const;
    double spanX() const;
    double spanY() const;
    QStringList axisX();
    QStringList axisY();

public:
    QPointF mapToPosition(QPointF value,  QRectF logic);
    QPolygonF mapToPosition(QPolygonF value,  QRectF logic);
    QPointF mapToValue(QPointF position,  QRectF logic);
    QPolygonF mapToValue(QPolygonF position,  QRectF logic);
    QRectF mapToValue(QRectF rect,  QRectF logic);
    QRectF mapToAxis(QRectF data,  QRectF axis);

protected:
    HCartesianCoordinate(HCartesianCoordinatePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HCartesianCoordinatePrivate> d_ptr;
};

#endif // HCARTESIANCOORDINATE_H
