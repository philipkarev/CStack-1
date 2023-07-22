//#ifndef CSTACK_FACTORY_H
//#define CSTACK_FACTORY_H

#include "CStack.h"

struct Factory {

    virtual CStack* create(size_t, char*, int*) = 0;
    virtual ~Factory() {}
};


struct FactoryCData0 : public Factory{

    CStack* create(size_t, char*, int*) override;
};


struct FactoryCData1 : public Factory{

    CStack* create(size_t, char*, int*) override;
};

//#endif //CSTACK_FACTORY_H
