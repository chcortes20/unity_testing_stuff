
#include "unity.h"
#include "GPIO.h"
#include "MK20DX256.h"

void test_SetPinAsOutput_should_configurePinDirection(void)
{
    PORTC.PDDR = 0;
    TEST_ASSERT_EQUAL(0, GPIO_SetPinAsOutput(0));
    TEST_ASSERT_EQUAL_HEX32((BIT_TO_MASK(0)), PORTC.PDDR);

    TEST_ASSERT_EQUAL(0, GPIO_SetPinAsOutput(22));
    TEST_ASSERT_EQUAL_HEX32((BIT_TO_MASK(0) | BIT_TO_MASK(22)), PORTC.PDDR);

    TEST_ASSERT_EQUAL(0, GPIO_SetPinAsOutput(31));
    TEST_ASSERT_EQUAL_HEX32((BIT_TO_MASK(0) | BIT_TO_MASK(22) | BIT_TO_MASK(31)), PORTC.PDDR);
}

void test_SetPinAsOuput_should_notSetPin_when_PinNotValid(void)
{
    PORTC.PDDR = 0;
    
    TEST_ASSERT_NOT_EQUAL(0, GPIO_SetPinAsOutput(32));
    TEST_ASSERT_EQUAL_HEX32(0x0, PORTC.PDDR);
}


void test_SetPinAsInput_should_configurePinDirection(void)
{
    PORTC.PDDR = 0xFFFFFFFF;
    TEST_ASSERT_EQUAL(0, GPIO_SetPinAsInput(0));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0)), PORTC.PDDR);

    TEST_ASSERT_EQUAL(0, GPIO_SetPinAsInput(16));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(16)), PORTC.PDDR);

    TEST_ASSERT_EQUAL(0, GPIO_SetPinAsInput(31));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(16) | BIT_TO_MASK(31)), PORTC.PDDR);
}

void test_SetPinAsInput_should_notSetPin_when_PinNotValid(void)
{
    PORTC.PDDR = 0xFFFFFFFF;
    
    TEST_ASSERT_NOT_EQUAL(0, GPIO_SetPinAsInput(32));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, PORTC.PDDR);
}


void test_setPin_should_SetOuputHigh(void)
{
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;

    TEST_ASSERT_EQUAL(0, GPIO_SetPin(0));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PSOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR);

    TEST_ASSERT_EQUAL(0, GPIO_SetPin(31));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(31), PORTC.PSOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR);
}

void test_SetPin_should_ForceToOuput_when_ConfiguredAsInput(void)
{
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;
    PORTC.PDDR = 0x50000000;

    TEST_ASSERT_EQUAL(0, GPIO_SetPin(0));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PSOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR );
    TEST_ASSERT_EQUAL_HEX32(0x50000001, PORTC.PDDR );

}

void test_SetPin_should_NotSetOutputs_when_PinIsNotValid(void)
{
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;
    PORTC.PDDR = 0;
                             
    TEST_ASSERT_NOT_EQUAL(0, GPIO_SetPin(32));
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PSOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PDDR );
}


void test_clear_should_SetOuputpinLow(void)
{
    PORTC.PSOR = 0xFFFFFFFF;
    PORTC.PCOR = 0;

    TEST_ASSERT_EQUAL(0, GPIO_Clear(0));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0)), PORTC.PSOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR);

    TEST_ASSERT_EQUAL(0, GPIO_Clear(31));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(31)), PORTC.PSOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR);
}

void test_clear_should_NotSetOutputs_when_PinIsNotValid(void)
{
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;
    PORTC.PDDR = 0;
                             
    TEST_ASSERT_NOT_EQUAL(0, GPIO_Clear(32));
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PSOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR );
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PDDR );
}

void test_ReadPin_should_ReturnPinValue(void)
{
    PORTC.PDIR = 0x845AC3E1;

    TEST_ASSERT_EQUAL(1, GPIO_readPin(0));
    TEST_ASSERT_EQUAL(0, GPIO_readPin(3));
    TEST_ASSERT_EQUAL(0, GPIO_readPin(29));
    TEST_ASSERT_EQUAL(1, GPIO_readPin(31));

    TEST_ASSERT_EQUAL(0x845AC3E1, PORTC.PDIR);
}

void test_ReadPort_should_ReturnEntirePort(void)
{
    PORTC.PDIR = 0x845AC3E1 ^ 0x00000022;

    TEST_ASSERT_EQUAL_HEX32(0x845AC3E1, GPIO_ReadPort());

    PORTC.PDIR = 0 ^ 0x00000022;

    TEST_ASSERT_EQUAL_HEX32(0, GPIO_ReadPort());

    PORTC.PDIR = 0xFFFFFFFF ^ 0x00000022;

    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, GPIO_ReadPort());
}


void test_Init_should_ConfigurePinsToDefaults(void)
{
    PORTC.PDDR = 0;
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;

    GPIO_Init();

    TEST_ASSERT_EQUAL(0x1012A000, PORTC.PDDR);
    TEST_ASSERT_EQUAL(0x10102000, PORTC.PSOR);
    TEST_ASSERT_EQUAL(0x00028000, PORTC.PCOR);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_SetPinAsOutput_should_configurePinDirection);
    RUN_TEST(test_SetPinAsOuput_should_notSetPin_when_PinNotValid);
    RUN_TEST(test_SetPinAsInput_should_configurePinDirection);
    RUN_TEST(test_SetPinAsInput_should_notSetPin_when_PinNotValid);
    RUN_TEST(test_setPin_should_SetOuputHigh);
    RUN_TEST(test_SetPin_should_ForceToOuput_when_ConfiguredAsInput);
    RUN_TEST(test_SetPin_should_NotSetOutputs_when_PinIsNotValid);
    RUN_TEST(test_clear_should_SetOuputpinLow);
    RUN_TEST(test_clear_should_NotSetOutputs_when_PinIsNotValid);
    RUN_TEST(test_ReadPin_should_ReturnPinValue); /* test 10 here*/
    RUN_TEST(test_ReadPort_should_ReturnEntirePort);
    RUN_TEST(test_Init_should_ConfigurePinsToDefaults);
    return UNITY_END();
}
