/***************************************************************************************************
**      2019-10-24  HTestWidget2000DC
***************************************************************************************************/

#pragma once

#include "HeGui/HSpecTestWidget.h"

HE_USE_NAMESPACE

class HTestWidget2000DCPrivate;

class HTestWidget2000DC : public HSpecTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget2000DC)

public:
    explicit HTestWidget2000DC(QWidget *parent = nullptr);
    ~HTestWidget2000DC() override;

public:
    QString typeName() override;

protected:
    void init() override;
    void createAction() override;
    void createWidget() override;
    void createMenu() override;
    void readSettings() override;
    void writeSettings() override;
    void setProbe(bool b);
};
