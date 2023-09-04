
#include "unity.h"
#include "Buffer.h"
#include "MK20DX256.h"

#define LEN(x) (sizeof(x)/sizeof(x[0]))

void test_buffer_put_and_get_should_WorkTogetherToinsertAndExtractValue(void)
{
    const uint16_t data[] = {0, 1, 0x5A, 0x7FF, 0xFFFF};
    uint16_t fetch;
    for(int i = 0; i <LEN(data); i++)
    {
        TEST_ASSERT_EQUAL(0, buffer_put(data[i]));
        TEST_ASSERT_EQUAL(0, buffer_get(&fetch));
        TEST_ASSERT_EQUAL(data[i], fetch);
    }
}

void test_buffer_get_should_ReturnErrorIfCalledWhenEmpty(void)
{
    uint16_t fetch;
    TEST_ASSERT_NOT_EQUAL(0, buffer_get(&fetch));
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_buffer_put_and_get_should_WorkTogetherToinsertAndExtractValue);
    RUN_TEST(test_buffer_get_should_ReturnErrorIfCalledWhenEmpty);
    return UNITY_END();
}
