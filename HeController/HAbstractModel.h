#ifndef HABSTRACTMODEL_H
#define HABSTRACTMODEL_H

#include "IModel.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HAbstractModel : public IModel
{
public:
 //   HAbstractModel(QObject *parent = nullptr);

protected:
    virtual void initProtocolStrategy() = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTMODEL_H
