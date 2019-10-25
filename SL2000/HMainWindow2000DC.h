/***************************************************************************************************
**      2019-10-23  HMainWindow2000DC
***************************************************************************************************/

#ifndef HMAINWINDOW2000DC_H
#define HMAINWINDOW2000DC_H

#include "HeGui/HAbstractMainWindow.h"

HE_GUI_USE_NAMESPACE

class HMainWindow2000DCPrivate;

class HMainWindow2000DC : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow2000DC)

public:
    explicit HMainWindow2000DC(QWidget *parent = nullptr, const HCallorHelper &helper = HCallorHelper());
    ~HMainWindow2000DC() override;

protected:
    void initImportExport() override;
    void initBuilder() override;
};

#endif // HMAINWINDOW2000DC_H
