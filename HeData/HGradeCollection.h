/***************************************************************************************************
**      2019-04-16  HGradeCollection 分级数据集合类。
***************************************************************************************************/

#ifndef HGRADECOLLECTION_H
#define HGRADECOLLECTION_H

#include "IGradeCollection.h"
#include "HeCore/HCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;
class HGradeCollectionPrivate;

class HGradeCollection : public HCollection<IGrade>, public IGradeCollection
{
    Q_DECLARE_PRIVATE(HGradeCollection)

public:
    explicit HGradeCollection(IDataFactory *);
    virtual ~HGradeCollection();

public:
    QString typeName() override;

public:
    IFileStream *fileStream() override;

protected:
    HGradeCollection(HGradeCollectionPrivate &);

protected:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);

protected:
    QScopedPointer<HGradeCollectionPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HGRADECOLLECTION_H
