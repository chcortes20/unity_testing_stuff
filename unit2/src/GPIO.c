#include "GPIO.h"
#include "MK20DX256.h"

static const uint32_t reservedMask = 0x00000022;

void GPIO_Init(void)
{
    PORTC.PDDR = 0x1012A000;
    PORTC.PSOR = 0x10102000;
    PORTC.PCOR = 0x00028000;
}

int GPIO_SetPinAsInput(uint8_t pin)
{
    if(pin >= 32)
    {
        return 1;
    }
    PORTC.PDDR &= ~BIT_TO_MASK(pin);
    return 0;
}

int GPIO_SetPinAsOutput(uint8_t pin)
{
    if(pin >= 32)
    {
        return 1;
    }
     PORTC.PDDR |= BIT_TO_MASK(pin);
     return 0;
}


int GPIO_SetPin(uint8_t pin)
{
    ASSERT_PIN(pin);
    uint32_t mask = BIT_TO_MASK(pin);

    PORTC.PSOR = mask;

    if(!(PORTC.PDDR & mask))
    {
        PORTC.PDDR |= mask;
    }
    return 0;
}
int GPIO_Clear(uint8_t pin)
{
    ASSERT_PIN(pin);

    uint32_t mask = BIT_TO_MASK(pin);
    PORTC.PSOR &= ~BIT_TO_MASK(pin);


    return 0;
}

int GPIO_readPin(uint8_t pin)
{
    ASSERT_PIN(pin);

    return ((BIT_TO_MASK(pin) & PORTC.PDIR) >> pin);
}


uint32_t GPIO_ReadPort(void) 
{

    return (PORTC.PDIR ^ reservedMask);
}
