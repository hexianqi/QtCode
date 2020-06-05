/***************************************************************************************************
**      2019-10-24  HTestWidget2000DC
***************************************************************************************************/

#ifndef HTESTWIDGET2000DC_H
#define HTESTWIDGET2000DC_H

#include "HTestWidget2000.h"

class HTestWidget2000DCPrivate;

class HTestWidget2000DC : public HTestWidget2000
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget2000DC)

public:
    explicit HTestWidget2000DC(QWidget *parent = nullptr);
    ~HTestWidget2000DC() override;

public:
    QString typeName() override;

protected:
    HTestWidget2000DC(HTestWidget2000DCPrivate &p, QWidget *parent = nullptr);

protected:
    void handleAction(HActionType action) override;
    void createAction() override;
    void createMenu() override;
    void readSettings();
    void writeSettings();
};

#endif // HTESTWIDGET2000DC_H
