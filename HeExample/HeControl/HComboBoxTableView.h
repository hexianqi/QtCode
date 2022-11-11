/***************************************************************************************************
**      2022-10-31  HComboBoxTableView
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QTableView>

class QComboBox;

HE_BEGIN_NAMESPACE

class HComboBoxTableViewPrivate;

class HComboBoxTableView : public QTableView
{
    Q_OBJECT

public:
    explicit HComboBoxTableView(QComboBox *parent = nullptr);
    ~HComboBoxTableView() override;

protected:
    HComboBoxTableView(HComboBoxTableViewPrivate &p, QComboBox *parent = nullptr);

protected:
    QScopedPointer<HComboBoxTableViewPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE

