
#include "unity.h"
#include "Parser.h"
#include "MK20DX256.h"

/* define global variables that we want to use here */
extern PARSER_STATE_T state;


/*
* HELPER FUNCTIONS (IF ANY) GO HERE
*/
void insert_valid_minimal_packet(char cmd, const char* full_message)
{
    TEST_ASSERT_NULL(parser_AddChar('['));
    TEST_ASSERT_NULL(parser_AddChar(cmd));
    TEST_ASSERT_NULL(parser_AddChar('0'));
    TEST_ASSERT_EQUAL_STRING(full_message, parser_AddChar(']'));
}


// end of helper functions

void test_TheFirst(void)
{
    TEST_IGNORE_MESSAGE("Implement Me");
}
void test_Parser_AddChar_should_StartLookingForCmdOnLeftBracket(void)
{
    state = LOOKING_FOR_START;
    TEST_ASSERT_NULL(parser_AddChar('['));
    TEST_ASSERT_EQUAL(LOOKING_FOR_CMD, state);


}

void test_Parser_AddChar_should_RejectNonBracketCharactersWhileSeekingStart(void)
{
    state = LOOKING_FOR_START;
    TEST_ASSERT_NULL(parser_AddChar('|'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_START, state);

    TEST_ASSERT_NULL(parser_AddChar('9'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_START, state);

    TEST_ASSERT_NULL(parser_AddChar('A'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_START, state);

}

void test_Parser_AddChar_should_AcceptValidCommandCharacter(void)
{
    state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(parser_AddChar('A'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_LEN, state);

    state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(parser_AddChar('M'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_LEN, state);

    state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(parser_AddChar('Z'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_LEN, state);
}


void test_Parser_AddChar_should_RejectValidCommandCharacter(void)
{
    state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(parser_AddChar('@'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_START, state);

    state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(parser_AddChar('\\'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_START, state);

    state = LOOKING_FOR_CMD;
    TEST_ASSERT_NULL(parser_AddChar('a'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_START, state);
}


void test_Parser_AddChar_should_AcceptALengthOfZero(void)
{
    state = LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(parser_AddChar('0'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_END, state);
}

void test_Parser_AddChar_should_RejectInvalidLengths(void)
{
    state = LOOKING_FOR_LEN;
    TEST_ASSERT_NULL(parser_AddChar(':'));
    TEST_ASSERT_EQUAL(LOOKING_FOR_START, state);
}

/*test for validating the design (black box)*/
void test_Parser_AddChar_should_HandleValidPacketWithNoData(void)
{
    insert_valid_minimal_packet('A', "[A0]");
    insert_valid_minimal_packet('Z', "[Z0]");
    insert_valid_minimal_packet('C', "[C0]");

}

void test_Parser_AddChar_should_IgnoreBadStartCharacters(void)
{
     TEST_ASSERT_NULL(parser_AddChar(':'));
     insert_valid_minimal_packet('D', "[D0]");

     TEST_ASSERT_NULL(parser_AddChar('a'));
     TEST_ASSERT_NULL(parser_AddChar(']'));
     insert_valid_minimal_packet('X', "[X0]");
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_TheFirst);
    RUN_TEST(test_Parser_AddChar_should_StartLookingForCmdOnLeftBracket);
    RUN_TEST(test_Parser_AddChar_should_RejectNonBracketCharactersWhileSeekingStart);
    RUN_TEST(test_Parser_AddChar_should_AcceptValidCommandCharacter);
    RUN_TEST(test_Parser_AddChar_should_RejectValidCommandCharacter);
    RUN_TEST(test_Parser_AddChar_should_AcceptALengthOfZero);
    RUN_TEST(test_Parser_AddChar_should_RejectInvalidLengths);
    RUN_TEST(test_Parser_AddChar_should_HandleValidPacketWithNoData);
    RUN_TEST(test_Parser_AddChar_should_IgnoreBadStartCharacters);
    return UNITY_END();
}
