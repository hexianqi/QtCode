/***************************************************************************************************
**      2019-08-01  HColorPopup
***************************************************************************************************/

#ifndef HCOLORPOPUP_H
#define HCOLORPOPUP_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

class QListView;

HE_CONTROL_BEGIN_NAMESPACE

class HColorModel;
class HColorPopupPrivate;

class HColorPopup : public QWidget
{
    Q_OBJECT

public:
    explicit HColorPopup(HColorModel *model, QWidget *parent = nullptr);
    ~HColorPopup() override;

signals:
    void selectIndex(const QModelIndex &);
    void selectColor(const QColor &);

public:
    QListView *colorView() const;

public:
    void setCurrentIndex(const QModelIndex &);
    void popupDialog();

protected:
    QScopedPointer<HColorPopupPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HCOLORPOPUP_H
