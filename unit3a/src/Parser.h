#ifndef PARSER_H
#define PARSER_H


typedef enum
{
    LOOKING_FOR_START = 0,
    LOOKING_FOR_CMD,
    LOOKING_FOR_LEN,
    LOOKING_FOR_DATA,
    LOOKING_FOR_END 

}PARSER_STATE_T;


char* parser_AddChar(char newChar);

#endif //PARSER_H
