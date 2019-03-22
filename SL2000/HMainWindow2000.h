#ifndef HMAINWINDOW2100_H
#define HMAINWINDOW2100_H

#include "HeGui/HAbstractMainWindow.h"

HE_GUI_USE_NAMESPACE

class HMainWindow2000Private;

class HMainWindow2000 : public HAbstractMainWindow
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMainWindow2000)

public:
    explicit HMainWindow2000(QWidget *parent = 0, const HCallorHelper &helper = HCallorHelper());
    ~HMainWindow2000();

protected:
    HMainWindow2000(HMainWindow2000Private &p, const HCallorHelper &helper, QWidget *parent = nullptr);

protected:
    virtual void initImportExport() override;
    virtual void createAction() override;
    virtual void createMenu() override;
    virtual void createConnect() override;
    virtual void initMenu() override;
    virtual bool openCalibrateDlg(QDialog *dlg, bool message = true);

protected slots:
    void openCalibrateSpectrumDialog();
};

#endif // HMAINWINDOW2100_H
