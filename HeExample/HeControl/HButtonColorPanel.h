/***************************************************************************************************
**      2019-07-15  HButtonColorPanel 颜色按钮面板
**                  http://www.qtcn.org/bbs/read-htm-tid-85975-ds-1.html#tpc
**                  1:可设置颜色集合
**                  2:可设置按钮圆角角度
**                  3:可设置列数
**                  4:可设置按钮边框宽度和边框颜色
***************************************************************************************************/

#ifndef HBUTTONCOLORPANEL_H
#define HBUTTONCOLORPANEL_H

#include "HAbstractColorPanel.h"

HE_CONTROL_BEGIN_NAMESPACE

class HButtonColorPanelPrivate;

class HButtonColorPanel : public HAbstractColorPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HButtonColorPanel)
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)

public:
    explicit HButtonColorPanel(QWidget *parent = nullptr);
    ~HButtonColorPanel() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int space() const;
    int columnCount() const;
    int borderRadius() const;
    int borderWidth() const;
    QColor borderColor() const;
    QStringList colors() const;

public slots:
    void setSpace(int value);
    void setColumnCount(int value);
    void setBorderRadius(int value);
    void setBorderWidth(int value);
    void setBorderColor(const QColor &value);
    void setColors(const QStringList &value);

protected:
    HButtonColorPanel(HButtonColorPanelPrivate &p, QWidget *parent = nullptr);

private:
    void init();
    void initButton();
    void initStyle();
    void handleButtonPressed();
};

HE_CONTROL_END_NAMESPACE

#endif // HBUTTONCOLORPANEL_H
