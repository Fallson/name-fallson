#include "cbook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/***********************************************************************************************/

CBook::CBook()
{
    content = NULL;
    content_len = 0;
    cur_pos = 0;

    b_init = false;
}

CBook::~CBook()
{
}

bool CBook::init()
{
    b_init = true;

    return true;
}

bool CBook::updateContent(const std::string &filepath)
{
    if( !b_init )
        return false;

    int ret = FN_OK;
    FILE* fp = NULL;

    do{
        fp = fopen(filepath.c_str(), "rb");
        if( fp == NULL )
        {
            ret = FN_ERR;
            break;
        }

        int file_sz = filesize(fp);
        if( file_sz <= 1 )
        {
            ret = FN_ERR;
            break;
        }

        FN_FREE(content);
        content = (char*) malloc(file_sz);
        if( content == NULL )
        {
            ret = FN_ERR;
            break;
        }
        content_len = file_sz;
        cur_pos = 0;

        if( fread(content, 1, (size_t)file_sz, fp) != (size_t)file_sz )
        {
            ret = FN_ERR;
            break;
        }
    }while(0);

    if( fp )
        fclose(fp);

    if( ret != FN_OK )
    {
        FN_FREE(content);
        content_len = 0;
        cur_pos = 0;
    }

    return ret == FN_OK?true:false;
}

void CBook::clear()
{
    FN_FREE(content);

    b_init = false;
}

bool CBook::getNextUtf8Char(utf8Char &ch)
{
    if( !b_init )
        return false;

    memset(ch.buf, 0, 6);
    ch.len = 0;

    int next_pos = cur_pos + 1;
    while( (content[next_pos] & 0xc0) == 0x80 && next_pos < content_len)
    {
        next_pos++;
    }

    if( cur_pos != content_len )
    {
        memcpy(ch.buf, content+cur_pos, next_pos-cur_pos);
        ch.len = next_pos-cur_pos;
        cur_pos = next_pos;

        return true;
    }
    else
    {
        return false;
    }
}
