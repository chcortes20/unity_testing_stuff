
#include "unity.h"
#include "Filter.h"
#include "MK20DX256.h"

void test_filter_AddValue_should_OuputPrevVal_if_PreValAndNewValMAtch(void)
{
    TEST_ASSERT_EQUAL_HEX16(0, filter_AddValue(0, 0));
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, filter_AddValue(0xFFFF, 0xFFFF));
    TEST_ASSERT_EQUAL_HEX16(0x8000, filter_AddValue(0x8000, 0x8000));
    TEST_ASSERT_EQUAL_HEX16(0x7FFF, filter_AddValue(0x7FFF, 0x7FFF));
}

void test_filter_AddVal_should_HandleSimpleMiddleRangeCalculations(void)
{
    TEST_ASSERT_EQUAL_HEX16(775, filter_AddValue(1000, 100));
    TEST_ASSERT_EQUAL_HEX16(325, filter_AddValue(100, 1000));
}

void test_Filter_AddVal_should_HandleCalculationsNearBottomOfRange(void)
{
    TEST_ASSERT_EQUAL_HEX16( 3, filter_AddValue(4, 0) );
    TEST_ASSERT_EQUAL_HEX16( 1, filter_AddValue(0, 4) );
}

void test_Filter_AddVal_should_HandleCalculationsNearTopOfRange(void)
{
    TEST_ASSERT_EQUAL_HEX16( 0xFFFE, filter_AddValue(0xFFFF, 0xFFFE) );
    TEST_ASSERT_EQUAL_HEX16( 0xFFF9, filter_AddValue(0xFFF8, 0xFFFF) );
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_filter_AddValue_should_OuputPrevVal_if_PreValAndNewValMAtch);
    RUN_TEST(test_filter_AddVal_should_HandleSimpleMiddleRangeCalculations);
    RUN_TEST(test_Filter_AddVal_should_HandleCalculationsNearBottomOfRange);
    RUN_TEST(test_Filter_AddVal_should_HandleCalculationsNearTopOfRange);
    return UNITY_END();
}
