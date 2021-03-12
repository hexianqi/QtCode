/***************************************************************************************************
**      2019-08-12  HTwoColorIndicator
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HTwoColorIndicatorPrivate;

class HTwoColorIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(bool active READ isActive WRITE setActive)
    Q_PROPERTY(bool dragEnabled READ isDragEnabled WRITE setDragEnabled)

public:
    explicit HTwoColorIndicator(QWidget *parent = nullptr);
    ~HTwoColorIndicator() override;

signals:
    void foregroundChanged(const QColor &);
    void backgroundChanged(const QColor &);
    void foregroundClicked();
    void backgroundClicked();
    void foregroundPressed();
    void backgroundPressed();

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QColor foreground() const;
    QColor background() const;
    bool isActive() const;
    bool isDragEnabled() const;

public slots:
    void setForeground(const QColor &value);
    void setBackground(const QColor &value);
    void setActive(bool b);
    void setDragEnabled(bool b);
    void switchColors();

protected:
    HTwoColorIndicator(HTwoColorIndicatorPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void dragEnterEvent(QDragEnterEvent *) override;
    void dragMoveEvent(QDragMoveEvent *) override;
    void dropEvent(QDropEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void paintSection(QPainter *painter, const QRect &rect, const QColor &color);
    QRect foregroundRect() const;
    QRect backgroundRect() const;
    QRect switchButtonRect() const;

protected:
    QScopedPointer<HTwoColorIndicatorPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
