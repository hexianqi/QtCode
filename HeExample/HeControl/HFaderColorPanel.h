/***************************************************************************************************
**      2019-07-16  HFaderColorPanel 颜色滑块面板
**                  http://www.qtcn.org/bbs/read-htm-tid-85976-ds-1.html#tpc
**                  1:可设置滑块条之间的间隔
**                  2:可设置滑块组之间的间隔
**                  3:可设置背景颜色
***************************************************************************************************/

#pragma once

#include "HAbstractColorPanel.h"

HE_CONTROL_BEGIN_NAMESPACE

// 代码不全 缺少ColorPanelBar控件
class HFaderColorPanelPrivate;

class HFaderColorPanel : public HAbstractColorPanel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HFaderColorPanel)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(int barSpace READ barSpace WRITE setBarSpace)
    Q_PROPERTY(int groupSpace READ groupSpace WRITE setGroupSpace)

public:
    explicit HFaderColorPanel(QWidget *parent = nullptr);
    ~HFaderColorPanel() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QColor background() const;
    int barSpace() const;
    int groupSpace() const;

public slots:
    void setBackground(const QColor &value);
    void setBarSpace(int barSpace);
    void setGroupSpace(int barSpace);

protected:
    HFaderColorPanel(HFaderColorPanelPrivate &p, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *, QEvent *) override;
    void paintEvent(QPaintEvent *) override;

private:
};

HE_CONTROL_END_NAMESPACE
