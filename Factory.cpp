#include "Factory.h"

CStack* FactoryCData0::create(size_t length, char *file, int* container) {
    return new CData0(length, file, container);
}

CStack* FactoryCData1::create(size_t length, char *file, int* container) {
    return new CData1(length, file, container);
}