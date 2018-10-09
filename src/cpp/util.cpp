#include "util.h"

int filesize(FILE* fp)
{
    long old_pos;
    long file_s;

    old_pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    file_s = ftell(fp);
    fseek(fp, old_pos, SEEK_SET);

    return (int)file_s;
}

bool checkUtf8Char(char* content, int len)
{
    if(len > 6 || len < 1)
        return false;

    if( (content[0] & 0xfe) == 0xfc ) //6 bytes leading char
    {
        if( len != 6 )
            return false;

        for(int i = 1; i < len; i++)
        {
            if( (content[i] & 0xc0) != 0x80 )
                return false;
        }
    }
    else if( (content[0] & 0xfc) == 0xf8 )//5 bytes leading char
    {
        if( len != 5 )
            return false;

        for(int i = 1; i < len; i++)
        {
            if( (content[i] & 0xc0) != 0x80 )
                return false;
        }
    }
    else if( (content[0] & 0xf8) == 0xf0 )//4 bytes leading char
    {
        if( len != 4 )
            return false;

        for(int i = 1; i < len; i++)
        {
            if( (content[i] & 0xc0) != 0x80 )
                return false;
        }
    }
    else if( (content[0] & 0xf0) == 0xe0 )//3 bytes leading char
    {
        if( len != 3 )
            return false;

        for(int i = 1; i < len; i++)
        {
            if( (content[i] & 0xc0) != 0x80 )
                return false;
        }
    }
    else if( (content[0] & 0xe0) == 0xc0 )//2 bytes leading char
    {
        if( len != 2 )
            return false;

        for(int i = 1; i < len; i++)
        {
            if( (content[i] & 0xc0) != 0x80 )
                return false;
        }
    }
    else if( (content[0] & 0x80) == 0x00 )//1 bytes leading char
    {
        if( len != 1 )
            return false;
    }
    else
        return false;

    return true;
}

int utf8CharNum(char* content, int len)
{
    int num = 0;

    for(int i = 0; i < len; i++)
    {
        if( (content[i] & 0xc0) != 0x80 )
            num++;
    }

    return num;
}
