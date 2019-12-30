/***************************************************************************************************
**      2018-06-19  HDiagramWidget 图表窗口部件。
***************************************************************************************************/

#ifndef HDIAGRAMWIDGET_H
#define HDIAGRAMWIDGET_H

#include <QtWidgets/QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class HDiagramWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HDiagramWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QMargins margins READ margins WRITE setMargins)
    Q_PROPERTY(QBrush brushBackground READ brushBackground WRITE setBrushBackground)
    Q_PROPERTY(QBrush brushPlotArea READ brushPlotArea WRITE setBrushPlotArea)
    Q_PROPERTY(bool square READ isSquare WRITE setSquare)
    Q_PROPERTY(bool halfSide READ isHalfSide WRITE setHalfSide)
    Q_PROPERTY(bool drawFrame READ isDrawFrame WRITE setDrawFrame)
    Q_PROPERTY(QColor colorFrame READ colorFrame WRITE setColorFrame)
    Q_PROPERTY(bool drawRuler READ isDrawRuler WRITE setDrawRuler)
    Q_PROPERTY(QColor colorRuler READ colorRuler WRITE setColorRuler)
    Q_PROPERTY(bool drawGrid READ isDrawGrid WRITE setDrawGrid)
    Q_PROPERTY(QColor colorGrid READ colorGrid WRITE setColorGrid)

public:
    explicit HDiagramWidget(QWidget *parent = nullptr);
    ~HDiagramWidget() override;

signals:
    void marginChanged(QMargins value);
    void plotAreaChanged(QRectF value);

public:
    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;

public:
    void setMargins(QMargins value);
    void setMargins(int left, int top, int right, int bottom);
    void setBrushBackground(QBrush value);
    void setBrushPlotArea(QBrush value);
    void setSquare(bool b);
    void setHalfSide(bool b);
    void setDrawFrame(bool b);
    void setDrawRuler(bool b);
    void setDrawGrid(bool b);
    void setColorFrame(QColor value);
    void setColorRuler(QColor value);
    void setColorGrid(QColor value);

public:
    QMargins margins() const;
    QBrush brushBackground() const;
    QBrush brushPlotArea() const;
    bool isSquare() const;
    bool isHalfSide() const;
    bool isDrawFrame() const;
    bool isDrawRuler() const;
    bool isDrawGrid() const;
    QColor colorFrame() const;
    QColor colorRuler() const;
    QColor colorGrid() const;

public:
    virtual void addPolygon(int id, QPolygonF value, bool refresh = true);
    virtual void removePolygon(int id);
    virtual void clearPolygon();
    virtual void setPolygonColor(int id, QColor color);

protected:
    HDiagramWidget(HDiagramWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *) override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void setPlotArea(QRectF value);
    virtual void refreshPixmap(bool refresh = true);
    virtual void initPixmap(QPainter *);
    virtual bool drawFrame(QPainter *);
    virtual bool drawRuler(QPainter *);
    virtual bool drawTick(QPainter *);
    virtual bool drawGrid(QPainter *);
    virtual bool drawPolygon(QPainter *);
    virtual bool drawElse(QPainter *);
    virtual bool isValid();

protected:
    QScopedPointer<HDiagramWidgetPrivate> d_ptr;

private:
    void init();
};

#endif // HDIAGRAMWIDGET_H
