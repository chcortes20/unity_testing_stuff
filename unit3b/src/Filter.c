#include "Filter.h"
#include "MK20DX256.h"




uint16_t filter_AddValue(uint16_t prevVal, uint16_t newVal)
{
    uint32_t product = (uint32_t)prevVal * 3;
    return (uint16_t)((product + newVal)/4);
}