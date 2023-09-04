#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>
/* building a low pass filter
*  accepts a new value and a previously filtered value
*  Returns a filtered value
*  Works with uint16_t values
*/

uint16_t filter_AddValue(uint16_t prevVal, uint16_t newVal);


#endif //FILTER_H
