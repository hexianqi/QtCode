/***************************************************************************************************
**      2018-06-19  HDataFactory 数据工厂类。
***************************************************************************************************/

#ifndef HDATAFACTORY_H
#define HDATAFACTORY_H

#include "IDataFactory.h"

HE_DATA_BEGIN_NAMESPACE

class HDataFactoryPrivate;

class HE_DATA_EXPORT HDataFactory : public QObject, public IDataFactory
{
    Q_OBJECT

public:
    explicit HDataFactory(QObject *parent = nullptr);
    ~HDataFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    IFileStream *createFileStream(QString type, QVariantMap param = QVariantMap()) override;
    IExcelStream *createExcelStream(QString type, QVariantMap param = QVariantMap()) override;
    IConfigManage *createConfigManage(QString type, QVariantMap param = QVariantMap()) override;
    ISpecCalibrateCollection *createSpecCalibrateCollection(QString type, QVariantMap param = QVariantMap()) override;
    ISpecCalibrate *createSpecCalibrate(QString type, QVariantMap param = QVariantMap()) override;
    IGradeCollection *createGradeCollection(QString type, QVariantMap param = QVariantMap()) override;
    IGrade *createGrade(QString type, QVariantMap param = QVariantMap()) override;
    IGradeItem *createGradeItem(QString type, QVariantMap param = QVariantMap()) override;
    IAdjustCollection *createAdjustCollection(QString type, QVariantMap param = QVariantMap()) override;
    IAdjust *createAdjust(QString type, QVariantMap param = QVariantMap()) override;
    IAdjustItem *createAdjustItem(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HDataFactory(HDataFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HDataFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_DATA_END_NAMESPACE

#endif // HDATAFACTORY_H
