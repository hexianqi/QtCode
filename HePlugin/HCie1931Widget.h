/***************************************************************************************************
**      2018-06-19  HCIE1931Widget CIE1931窗口部件。
***************************************************************************************************/

#pragma once

#include "HCartesianWidget.h"

class HCie1931WidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HCie1931Widget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCie1931Widget)
    Q_PROPERTY(bool enableTracking READ isEnableTracking WRITE setEnableTracking)
    Q_PROPERTY(bool drawCIE READ isDrawCIE WRITE setDrawCIE)
    Q_PROPERTY(bool drawHorseshoe READ isDrawHorseshoe WRITE setDrawHorseshoe)
    Q_PROPERTY(QColor colorHorseshoe READ colorHorseshoe WRITE setColorHorseshoe)
    Q_PROPERTY(bool drawPlanckian READ isDrawPlanckian WRITE setDrawPlanckian)
    Q_PROPERTY(QColor colorPlanckian READ colorPlanckian WRITE setColorPlanckian)
    Q_PROPERTY(bool drawGrade READ isDrawGrade WRITE setDrawGrade)
    Q_PROPERTY(QColor colorGrade READ colorGrade WRITE setColorGrade)
    Q_PROPERTY(QColor colorGradeFocus READ colorGradeFocus WRITE setColorGradeFocus)
    Q_PROPERTY(bool drawGradeName READ isDrawGradeName WRITE setDrawGradeName)
    Q_PROPERTY(bool drawPoint READ isDrawPoint WRITE setDrawPoint)
    Q_PROPERTY(QColor colorPoint READ colorPoint WRITE setColorPoint)
    Q_PROPERTY(QColor colorPointFocus READ colorPointFocus WRITE setColorPointFocus)
    Q_PROPERTY(QFont fontPointFocus READ fontPointFocus WRITE setFontPointFocus)

public:
    explicit HCie1931Widget(QWidget *parent = nullptr);

signals:
    void mouseDoubleClicked(QPointF point);

public:
    void setEnableTracking(bool b);
    void setDrawCIE(bool b);
    void setDrawHorseshoe(bool b);
    void setDrawPlanckian(bool b);
    void setDrawGrade(bool b);
    void setDrawGradeName(bool b);
    void setDrawPoint(bool b);
    void setColorHorseshoe(const QColor &);
    void setColorPlanckian(const QColor &);
    void setColorGrade(const QColor &);
    void setColorGradeFocus(const QColor &);
    void setColorPoint(const QColor &);
    void setColorPointFocus(const QColor &);
    void setFontPointFocus(const QFont &);

public:
    bool isEnableTracking();
    bool isDrawCIE();
    bool isDrawHorseshoe();
    bool isDrawPlanckian();
    bool isDrawGrade();
    bool isDrawGradeName();
    bool isDrawPoint();
    QColor colorHorseshoe();
    QColor colorPlanckian();
    QColor colorGrade();
    QColor colorGradeFocus();
    QColor colorPoint();
    QColor colorPointFocus();
    QFont fontPointFocus();

public:
    void setGradeFocus(const QPolygonF &);
    void setGrade(const QList<QPolygonF> &, bool refresh = true);
    void addGrade(const QPolygonF &value, bool focus = true, bool refresh = true);
    void removeGrade(const QPolygonF &value, bool refresh = true);
    void replaceGrade(int i, const QPolygonF &value, bool refresh = true);
    void clearGrade();
    void setGradeName(const QStringList &, bool refresh = true);
    void replaceGradeName(int i, const QString &value, bool refresh = true);
    void setPointFocus(QPointF value);
    void setPoint(const QList<QPointF> &);
    void addPoint(QPointF value, bool focus = true, bool refresh = true);
    void clearPoint();

protected:
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    bool drawElse(QPainter *) override;
    bool drawCIE(QPainter *);
    bool drawHorseshoe(QPainter *);
    bool drawPlanckian(QPainter *);
    bool drawGradeBlock(QPainter *);
    bool drawPoint(QPainter *);

protected slots:
    void handlePlotAreaChanged(QRectF value);
    void handlePositionChanged(QPointF pos);

private:
    void init();
};
