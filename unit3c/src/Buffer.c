#include "Buffer.h"
#include "MK20DX256.h"

#define BUFF_SIZE 3

uint16_t buffer[BUFF_SIZE];
uint16_t buff_read = 0, buff_write = 0;
int buffer_put(uint16_t val)
{
    buffer[buff_write] = val;
    buff_write = (buff_write + 1) % BUFF_SIZE;
    return 0;
}

int buffer_get(uint16_t *val)
{
    if(buff_read == buff_write)
    {
        return  1;
    }
    *val = buffer[buff_read];
    buff_read = (buff_read + 1) % BUFF_SIZE;
    return 0;
}

