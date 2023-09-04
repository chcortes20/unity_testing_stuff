#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define ASSERT_PIN(p) if((p) >= 32) { return 1; }


void GPIO_Init(void);
int GPIO_SetPinAsOuput(uint8_t pin);
int GPIO_SetPinAsInput(uint8_t pin);
int GPIO_SetPin(uint8_t pin);
int GPIO_Clear(uint8_t pin);
int GPIO_readPin(uint8_t pin);
uint32_t GPIO_ReadPort();

#endif //GPIO_H
