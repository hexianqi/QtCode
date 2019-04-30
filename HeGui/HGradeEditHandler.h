/***************************************************************************************************
**      2019-04-25  HGradeEditHandler 分级数据编辑处理者类。
***************************************************************************************************/

#ifndef HGRADEEDITHANDLER_H
#define HGRADEEDITHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HGradeEditHandlerPrivate;

class HGradeEditHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGradeEditHandler)

public:
    explicit HGradeEditHandler(QObject *parent = nullptr);
    ~HGradeEditHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HGRADEEDITHANDLER_H
