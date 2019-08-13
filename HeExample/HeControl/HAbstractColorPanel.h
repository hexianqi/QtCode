/***************************************************************************************************
**      2019-07-15  HAbstractColorPanel 抽象颜色面板
***************************************************************************************************/

#ifndef HABSTRACTCOLORPANEL_H
#define HABSTRACTCOLORPANEL_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractColorPanelPrivate;

class HAbstractColorPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor)

public:
    explicit HAbstractColorPanel(QWidget *parent = nullptr);
    ~HAbstractColorPanel() override;

signals:
    void currentColorChanged(const QColor &value);

public:
    QColor currentColor() const;

public slots:
    void setCurrentColor(const QColor &value);

protected:
    HAbstractColorPanel(HAbstractColorPanelPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HAbstractColorPanelPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTCOLORPANEL_H
