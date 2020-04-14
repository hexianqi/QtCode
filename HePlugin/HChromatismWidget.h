/***************************************************************************************************
**      2019-05-16  HChromatismWidget 色容差窗口部件。
***************************************************************************************************/

#ifndef HCHROMATISMWIDGET_H
#define HCHROMATISMWIDGET_H

#include "HCartesianWidget.h"

class HChromatismWidgetPrivate;

class QDESIGNER_WIDGET_EXPORT HChromatismWidget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HChromatismWidget)
    Q_PROPERTY(QColor colorPointFocus READ colorPointFocus WRITE setColorPointFocus)
    Q_PROPERTY(QColor colorTitle READ colorTitle WRITE setColorTitle)
    Q_PROPERTY(QColor colorBody READ colorBody WRITE setColorBody)
    Q_PROPERTY(QFont fontTitle READ fontTitle WRITE setFontTitle)
    Q_PROPERTY(QFont fontBody READ fontBody WRITE setFontBody)

public:
    explicit HChromatismWidget(QWidget *parent = nullptr);

public:
    void setData(const QVariantMap &);
    void setColorPointFocus(const QColor &);
    void setColorTitle(const QColor &);
    void setColorBody(const QColor &);
    void setFontTitle(const QFont &);
    void setFontBody(const QFont &);

public:
    QColor colorPointFocus();
    QColor colorTitle();
    QColor colorBody();
    QFont fontTitle();
    QFont fontBody();

protected:
    bool drawElse(QPainter *) override;
    bool drawPointFocus(QPainter *);
    bool drawPointCenter(QPainter *);
    bool drawDescription(QPainter *);

private:
    void init();
    void fixCoordinate(QPointF center, QPolygonF poly);
};

#endif // HCHROMATISMWIDGET_H
