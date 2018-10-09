#include "cpianpang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "util.h"

/***********************************************************************************************/
CPianPang::CPianPang()
{
    b_init = false;

    insen_para = NULL;
    sen_para = NULL;

    keywords = NULL;
    num = 0;
}

CPianPang::~CPianPang()
{
}

bool CPianPang::loadkeywords(const char* filepath)
{
    int ret = FN_OK;

    /*0. open the file*/
    FILE* fep = fopen(filepath, "rb");
    if( fep == NULL )
    {
        return false;
    }

    char* content = NULL;
    int num_tmp = 0;
    int num_newline = 0;
    int id = 0;
    DGateKeyword* keywords_tmp = NULL;
    do{
        /*0. load the content*/
        int fsz = filesize(fep);
        if( fsz <= 0 )
        {
            ret = FN_OK;
            break;
        }

        content = (char*)malloc(fsz);
        if( content == NULL )
        {
            ret = FN_ERR;
            break;
        }

        if( fread(content, 1, (size_t)fsz, fep) != (size_t)fsz )
        {
            ret = FN_ERR;
            break;
        }

        /*1. calculate the utf8 char number */
        num_tmp = utf8CharNum(content, fsz);
        if( num_tmp <= 0 )
        {
            ret = FN_OK;
            break;
        }

        /*2. load keywords */
        keywords_tmp = (DGateKeyword*)malloc(num_tmp * sizeof(DGateKeyword));
        if( keywords_tmp == NULL )
        {
            ret = FN_ERR;
            break;
        }

        int p1 = 0;
        int p2 = p1 + 1;
        while( p1 < fsz )
        {
            char buf[12] = {'\0'};
            if( (content[p2] & 0xc0) == 0x80 ) //no leading char
            {
                p2++;
            }
            else
            {
                if( !checkUtf8Char(content+p1, p2-p1) )
                {
                    ret = FN_ERR;
                    break;
                }

                if( content[p1] == '\r' || content[p1] == '\n' )
                {
                    boundary.push_back(id);
                    num_newline++;
                    p1 = p2;
                    p2 = p1 + 1;
                }
                else
                {
                    //store the keyword
                    memcpy(buf, content+p1, p2-p1);
                    p1 = p2;
                    p2 = p1 + 1;

                    keywords_tmp[id].ID = id;
                    keywords_tmp[id].caseSensative = 0;
                    strcpy((char*)keywords_tmp[id].word, buf);
                    keywords_tmp[id].wordlen = strlen((char*)keywords_tmp[id].word);
                    keywords_tmp[id].pat = NULL;
                    keywords_tmp[id].delta = NULL;
                    id++;
                }
            }
        }

    }while(0);

    FN_FREE(content);
    if(fep)
        fclose(fep);

    if( ret != FN_OK )
    {
        FN_FREE(keywords_tmp);
    }
    else
    {
        keywords = keywords_tmp;
        assert(id == num_tmp-num_newline);
        num = num_tmp-num_newline ;
    }

    return ret == FN_OK?true:false;
}

bool CPianPang::init(const std::string& filepath)
{
    int ret = FN_OK;

    do{
        //load the kws from filepath and set the boundary
        if( !loadkeywords(filepath.c_str()) )
        {
            ret = FN_ERR;
            break;
        }

        if( num == 0 )
            break;

        insen_para = (DLPKeywordPara*)malloc(sizeof(DLPKeywordPara));
        if( insen_para == NULL )
        {
            ret = FN_ERR;
            break;
        }

        sen_para = (DLPKeywordPara*)malloc(sizeof(DLPKeywordPara));
        if( sen_para == NULL )
        {
            ret = FN_ERR;
            break;
        }

        ret = preprocessMultiPatternMatcher(keywords, num, insen_para, sen_para);
        if( ret != 0 )
        {
            ret = FN_ERR;
            break;
        }
    }while(0);

    if( ret == FN_OK )
    {
        b_init = true;
    }
    else
    {
        clear();
        b_init = false;
    }

    return ret == FN_OK?true:false;
}

void CPianPang::clear()
{
    boundary.clear();

    if( insen_para )
    {
        freeKeywordPara(insen_para);
        FN_FREE(insen_para);
    }

    if( sen_para )
    {
        freeKeywordPara(sen_para);
        FN_FREE(sen_para);
    }

    for(int i = 0; i < num; i++)
    {
        FN_FREE(keywords[i].pat);
        FN_FREE(keywords[i].delta);
    }
    FN_FREE(keywords);
    num = 0;

    b_init = false;
}

int CPianPang::getGroupIdx(char *text, int len)
{
    if( !b_init )
    {
        return -1;
    }

    if( num == 0 )
        return -1;

    unsigned int rn = 0;
    int id = 0;
    int ret = dgateMultiKeywordMatcher((unsigned char*)text, len,
                                         keywords, num,
                                         insen_para, sen_para,
                                         &rn, &id);
    if( ret == 0 && rn > 0 )
    {
        for( int i = 0; i < (int)boundary.size(); i++ )
        {
            if( id < boundary[i] )
                return i;
        }
    }

    return -1;
}
