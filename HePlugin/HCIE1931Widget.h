/***************************************************************************************************
**      2018-06-19  HCIE1931Widget CIE1931窗口部件。
***************************************************************************************************/

#ifndef HCIE1931WIDGET_H
#define HCIE1931WIDGET_H

#include "HCartesianWidget.h"

class HCIE1931WidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HCIE1931Widget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCIE1931Widget)
    Q_PROPERTY(bool enableTracking READ isEnableTracking WRITE setEnableTracking)
    Q_PROPERTY(bool drawCIE READ isDrawCIE WRITE setDrawCIE)
    Q_PROPERTY(bool drawHorseshoe READ isDrawHorseshoe WRITE setDrawHorseshoe)
    Q_PROPERTY(QColor colorHorseshoe READ colorHorseshoe WRITE setColorHorseshoe)
    Q_PROPERTY(bool drawPlanckian READ isDrawPlanckian WRITE setDrawPlanckian)
    Q_PROPERTY(QColor colorPlanckian READ colorPlanckian WRITE setColorPlanckian)
    Q_PROPERTY(bool drawGrade READ isDrawGrade WRITE setDrawGrade)
    Q_PROPERTY(QColor colorGrade READ colorGrade WRITE setColorGrade)
    Q_PROPERTY(QColor colorGradeFocus READ colorGradeFocus WRITE setColorGradeFocus)
    Q_PROPERTY(bool drawPoint READ isDrawPoint WRITE setDrawPoint)
    Q_PROPERTY(QColor colorPoint READ colorPoint WRITE setColorPoint)
    Q_PROPERTY(QColor colorPointFocus READ colorPointFocus WRITE setColorPointFocus)
    Q_PROPERTY(QFont fontPointFocus READ fontPointFocus WRITE setFontPointFocus)

public:
    explicit HCIE1931Widget(QWidget *parent = nullptr);
    ~HCIE1931Widget();

signals:
    void mouseDoubleClicked(QPointF point);

public:
    void setEnableTracking(bool b);
    void setDrawCIE(bool b);
    void setDrawHorseshoe(bool b);
    void setDrawPlanckian(bool b);
    void setDrawGrade(bool b);
    void setDrawPoint(bool b);
    void setColorHorseshoe(QColor value);
    void setColorPlanckian(QColor value);
    void setColorGrade(QColor value);
    void setColorGradeFocus(QColor value);
    void setColorPoint(QColor value);
    void setColorPointFocus(QColor value);
    void setFontPointFocus(QFont value);

public:
    bool isEnableTracking();
    bool isDrawCIE();
    bool isDrawHorseshoe();
    bool isDrawPlanckian();
    bool isDrawGrade();
    bool isDrawPoint();
    QColor colorHorseshoe();
    QColor colorPlanckian();
    QColor colorGrade();
    QColor colorGradeFocus();
    QColor colorPoint();
    QColor colorPointFocus();
    QFont fontPointFocus();

public:
    void setGradeFocus(QPolygonF value);
    void setGrade(QList<QPolygonF> value);
    void addGrade(QPolygonF value, bool focus = true, bool refresh = true);
    void clearGrade();
    void setPointFocus(QPointF value);
    void setPoint(QList<QPointF> value);
    void addPoint(QPointF value, bool focus = true, bool refresh = true);
    void clearPoint();

protected:
    virtual void mouseMoveEvent(QMouseEvent *) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *) override;
    virtual bool drawElse(QPainter *) override;
    virtual bool drawCIE(QPainter *);
    virtual bool drawHorseshoe(QPainter *);
    virtual bool drawPlanckian(QPainter *);
    virtual bool drawGradeBlock(QPainter *);
    virtual bool drawPoint(QPainter *);

protected slots:
    void handlePositionChanged(QPointF pos);

protected:
    HCIE1931Widget(HCIE1931WidgetPrivate &p, QWidget *parent = nullptr);

private:
    void init();
};

#endif // HCIE1931WIDGET_H
