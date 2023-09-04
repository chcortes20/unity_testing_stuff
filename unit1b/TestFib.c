
#include "unity.h"
#include "Fib.h"
#include <limits.h>

#define DIMENSION_OF(a) (sizeof(a)/ sizeof(a[0]))

void test_element0_should_return1(void)
{
    TEST_ASSERT_EQUAL_INT(1, Fibonacci_GetElement(0));
}
void test_element1_should_return1(void)
{
    TEST_ASSERT_EQUAL_INT(1, Fibonacci_GetElement(1));
}

void test_element2_should_return2(void)
{
    TEST_ASSERT_EQUAL_INT(2, Fibonacci_GetElement(2));
}

void test_part_of_the_sequence(void)
{
    TEST_ASSERT_EQUAL_INT(3, Fibonacci_GetElement(3));
    TEST_ASSERT_EQUAL_INT(5, Fibonacci_GetElement(4));
    TEST_ASSERT_EQUAL_INT(8, Fibonacci_GetElement(5));
    TEST_ASSERT_EQUAL_INT(13, Fibonacci_GetElement(6));
    TEST_ASSERT_EQUAL_INT(21, Fibonacci_GetElement(7));
    TEST_ASSERT_EQUAL_INT(34, Fibonacci_GetElement(8));
    TEST_ASSERT_EQUAL_INT(55, Fibonacci_GetElement(9));

}

void test_part_of_the_sequence_as_array(void)
{
    int expected[] = {3, 5, 8, 13, 21, 34, 55};

    int i;
    for ( i = 0; i < DIMENSION_OF(expected); i++)
    {
        TEST_ASSERT_EQUAL_INT(expected[i], Fibonacci_GetElement(i));
    }
}

void test_that_negative_elements_return_0(void)
{
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(-1));
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(-3));
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(-555));
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(INT_MIN));
}

void test_that_overun_values(void)
{
    const int FBI = 46;
    const int LGE = FBI - 1;
    const int LGV = Fibonacci_GetElement(LGE);

    /* Let make sure that an in here is 4 bytes */
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, sizeof(int), "const FBI and FIB_MAX must be changed");

    TEST_ASSERT_MESSAGE(LGV > 1, "This Value should not have been rollover");
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(FBI));
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(INT_MAX));

}

/* now we are going to test the IsInSequence function */

void test_value0_should_not_be_in_sequence(void)
{
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(0) );
}

void test_value1_should_be_in_sequence(void)
{
    TEST_ASSERT_TRUE( Fibonacci_IsInSequence(1) );
}

void test_value2_should_be_in_sequence(void)
{
    TEST_ASSERT_TRUE( Fibonacci_IsInSequence(2) );
}

void test_value3_should_be_in_sequence(void)
{
    TEST_ASSERT_TRUE( Fibonacci_IsInSequence(3) );
}

void test_value4_should_not_be_in_sequence(void)
{
    TEST_ASSERT_FALSE( Fibonacci_IsInSequence(4) );
}

void test_value5_should_be_in_sequence(void)
{
    TEST_ASSERT_TRUE( Fibonacci_IsInSequence(5) );
}



int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_element0_should_return1);
    RUN_TEST(test_element1_should_return1);
    RUN_TEST(test_element2_should_return2);
    RUN_TEST(test_part_of_the_sequence);
    RUN_TEST(test_that_negative_elements_return_0);
    RUN_TEST(test_that_overun_values);

    RUN_TEST(test_value0_should_not_be_in_sequence);
    RUN_TEST(test_value1_should_be_in_sequence);
    RUN_TEST(test_value2_should_be_in_sequence);
    RUN_TEST(test_value3_should_be_in_sequence);
    RUN_TEST(test_value4_should_not_be_in_sequence);
    RUN_TEST(test_value5_should_be_in_sequence);

    return UNITY_END();
}
