/***************************************************************************************************
**      2019-07-31  HButtonLineEdit
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtGui/QIcon>
#include <QtWidgets/QLineEdit>

HE_CONTROL_BEGIN_NAMESPACE

class HButtonLineEditPrivate;

class HButtonLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(bool autoRaise READ isAutoRaise WRITE setAutoRaise)
    Q_PROPERTY(Position buttonPosition READ buttonPosition WRITE setButtonPosition)
    Q_PROPERTY(bool buttonVisible READ isButtonVisible WRITE setButtonVisible)
    Q_PROPERTY(QString regularExpression READ regularExpression WRITE setRegularExpression)
    Q_PROPERTY(Qt::FocusPolicy buttonFocusPolicy READ buttonFocusPolicy WRITE setButtonFocusPolicy)

public:
    enum Position
    {
        Position_None = 0,
        Position_RightOutside = 1,
        Position_RightInside = 2,
        Position_LeftOutside = 3,
        Position_LeftInside = 4
    };
    Q_ENUM(Position)

public:
    explicit HButtonLineEdit(QWidget *parent = nullptr);
    ~HButtonLineEdit() override;

signals:
    void buttonClicked();
    void validatorChanged(const QString &);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QIcon icon() const;
    bool isAutoRaise() const;
    Position buttonPosition() const;
    bool isButtonVisible() const;
    QString regularExpression() const;
    Qt::FocusPolicy buttonFocusPolicy() const;

public slots:
    virtual void setIcon(const QIcon &);
    virtual void setAutoRaise(bool b);
    virtual void setButtonPosition(Position value);
    virtual void setButtonVisible(bool b);
    virtual void setRegularExpression(const QString &);
    virtual void setRegularExpression(const QRegularExpression &);
    virtual void setButtonFocusPolicy(Qt::FocusPolicy value);

protected:
    HButtonLineEdit(HButtonLineEditPrivate &p, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;
    void actionEvent(QActionEvent *) override;
    void updateButtonPosition(int w);

protected:
    QScopedPointer<HButtonLineEditPrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
