/***************************************************************************************************
**      2018-06-19  HSpecDiagramWidget 光谱图表窗口部件。
***************************************************************************************************/

#ifndef HSPECDIAGRAMWIDGET_H
#define HSPECDIAGRAMWIDGET_H

#include "HCartesianWidget.h"

class HSpecDiagramWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HSpecDiagramWidget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecDiagramWidget)
    Q_PROPERTY(bool drawCenter READ isDrawCenter WRITE setDrawCenter)
    Q_PROPERTY(QString textCenter READ textCenter WRITE setTextCenter)
    Q_PROPERTY(QColor colorCenter READ colorCenter WRITE setColorCenter)
    Q_PROPERTY(QFont fontCenter READ fontCenter WRITE setFontCenter)
    Q_PROPERTY(QBrush brushCenter READ brushCenter WRITE setBrushCenter)
    Q_PROPERTY(bool drawTopLeft READ isDrawTopLeft WRITE setDrawTopLeft)
    Q_PROPERTY(QString textTopLeft READ textTopLeft WRITE setTextTopLeft)
    Q_PROPERTY(QColor colorTopLeft READ colorTopLeft WRITE setColorTopLeft)
    Q_PROPERTY(QFont fontTopLeft READ fontTopLeft WRITE setFontTopLeft)

public:
    explicit HSpecDiagramWidget(QWidget *parent = nullptr);
    ~HSpecDiagramWidget();

public:
    void setDrawCenter(bool b);
    void setDrawTopLeft(bool b);
    void setTextCenter(QString text, bool show = true, bool refresh = true);
    void setTextTopLeft(QString text, bool refresh = true);
    void setColorCenter(QColor value);
    void setColorTopLeft(QColor value);
    void setFontCenter(QFont value);
    void setFontTopLeft(QFont value);
    void setBrushCenter(QBrush value);
    void setCenter(QString text, QColor color, QColor brush);

public:
    bool isDrawCenter();
    bool isDrawTopLeft();
    QString textCenter();
    QString textTopLeft();
    QColor colorCenter();
    QColor colorTopLeft();
    QFont fontCenter();
    QFont fontTopLeft();
    QBrush brushCenter();

public:
    virtual void setPolygon(int id, QPolygonF value, bool refresh = true) override;

protected:
    HSpecDiagramWidget(HSpecDiagramWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void refreshPixmap(bool refresh = true) override;
    virtual bool drawCenter(QPainter *);
    virtual bool drawLeftTop(QPainter *);
};

#endif // HSPECDIAGRAMWIDGET_H
