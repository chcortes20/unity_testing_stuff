#include "Parser.h"
#include "MK20DX256.h"

#ifdef TEST
#define STATIC
#else
#define STATIC static
#endif

#define MAX_BUFF_LENGTH (23)


STATIC PARSER_STATE_T state = LOOKING_FOR_START;
static char buffer[MAX_BUFF_LENGTH];

char* parser_AddChar(char newChar)
{
    switch(state)
    {
        case LOOKING_FOR_START:
            if(newChar == '[')
            {
                state = LOOKING_FOR_CMD;
                buffer[0] = newChar;
            }
            break;
        case LOOKING_FOR_CMD:
            if((newChar >= 'A') && (newChar <= 'Z'))
            {
                state = LOOKING_FOR_LEN;
                buffer[1] = newChar;
            }
            else
            {
                state = LOOKING_FOR_START;
            }
            break;
        case LOOKING_FOR_LEN:
            if(newChar == '0')
            {
                state = LOOKING_FOR_END;
                buffer[2] = newChar;
            }
            else
            {
                state = LOOKING_FOR_START;
            }
            break;
        case LOOKING_FOR_END:
            if(newChar == ']')
            {
                state = LOOKING_FOR_START;
                buffer[3] = newChar;
                buffer[4] = '\0';
                return buffer;
            }
            
            state = LOOKING_FOR_START;
            break;
        default:
            break;
    }
    return 0;
}