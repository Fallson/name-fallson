/************************************************************************
*                                                                       *
* Copyright 2005-2005 by DGate Technologies, Inc., all rights reserved. *
*                                                                       *
* Legal statements:                                                     *
*                                                                       *
* THE SOFTWARE PROVIDED BY DGATE IS PROVIDED ON AN "AS IS" BASIS        *
* WITHOUT ANY REPRESENTATIONS, WARRANTIES OR CONDITIONS OF ANY KIND,    *
* WHETHER EXPRESS OR IMPLIED, STATUTORY, OUT OF A COURSE OF DEALING     *
* OR USAGE, TRADE OR OTHERWISE INCLUDING ANY IMPLIED WARRANTIES OR      *
* CONDITIONS OF MERCHANTABILITY, MERCHANTABLE QUALITY, FITNESS          *
* FOR ANY PARTICULAR PURPOSE OR USE OR NON-INFRINGEMENT. DGATE DOES     *
* NOT REPRESENT OR WARRANT THAT THE SOFTWARE WILL BE FREE OF DEFECT,    *
* UNINTERRUPTED, ACCURATE, COMPLETE, CURRENT, STABLE, BUG-FREE,         *
* ERROR-FREE, OR AVAILABLE AT ANY TIME.                                 *
*                                                                       *
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL DGATE       *
* BE LIABLE FOR ANY DIRECT, INDIRECT, CONSEQUENTIAL, INCIDENTAL,        *
* SPECIAL, RELIANCE, PUNITIVE OR OTHER DAMAGES OR EXPENSES OF ANY       *
* KIND, INCLUDING BUT NOT LIMITED TO ANY LOSS OF PROFITS OR REVENUE,    *
* LOST SAVINGS, LOST BUSINESS, LOST BUSINESS OPPORTUNITIES, LOST DATA,  *
* LOST GOODWILL, LOSS FROM WORK STOPPAGE, COSTS OF OVERHEAD, COSTS OF   *
* COVER, LOSS OF ANTICIPATED BENEFITS HEREUNDER, ARISING OUT OF OR      *
* RELATED TO THIS AGREEMENT, HOWEVER CAUSED AND ON ANY THEORY OF        *
* LIABILITY, EVEN IF THE PARTY HAS BEEN ADVISED OF THE POSSIBILITY      *
* OF SUCH DAMAGES, AND NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL     *
* PURPOSE OF ANY LIMITED REMEDY STATED HEREIN.                          *
*                                                                       *
* REVISION/MODIFICATION HISTORY:                                        *
*               (1) Created by Liwei Ren, DGate Technologies, Inc.      *
*                   09/24/2005.                                         *
*                                                                       *
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


#include "cmeErrCodeBasic.h"
#include "cmeKeywordMatch.h"
#include "cmeBMHPatMatch.h"

#define	MAGIC_NUMBER0			38
#define	MAGIC_NUMBER1			40

#define	KEYWORD_REC_INIT_SIZE	1000
#define WHOLE_SEQUENCE_MATCH	0
//#define	SUB_SEQUENCE_MATCH		1

#define DLP_FREE(x) if(x) {free(x);x=NULL;}

#define CASE_INSEN 0
#define CASE_SEN 1

#define	DGATE_tolower(c)	(((unsigned int)c > 64 && (unsigned int)c < 91 ) ? \
    ((unsigned int)c + 32) : ((unsigned int)c))

/************************************************************************/
void clearPara(DLPKeywordPara* para)
{
    if( para == NULL )
        return;

    para-> short_idx = NULL;
    para-> short_num = 0;
    para-> long_idx = NULL;
    para-> long_num = 0;
    para-> long_kwMinLen = 0;
    para-> hash = NULL;
    para-> ht_sz = 0;
    para-> bp = 0;
    memset((void*)para->Char_bp_table, 0, sizeof(unsigned int)* CHARTABLE_SZ );
    para-> trie = NULL;
    para-> trie_sz = 0;
}

int freeKeywordHashChain(DGateKRRHash * hash, 
                         unsigned int sz)
{
    if (hash == NULL || sz == 0)
    {
        return CME_OK;
    }
    return freeKRRHashChain(hash, sz);
}

int freeKeywordTrie(DLPTrieNode** trie,
                    unsigned int trie_sz)
{
    if( trie == NULL )
        return CME_OK;

    freeTire(trie, trie_sz);
    return CME_OK;
}

int freeKeywordPara(DLPKeywordPara* para)
{
    if( para == NULL )
        return CME_OK;

    DLP_FREE(para->short_idx)
            DLP_FREE(para->long_idx);

    freeKeywordHashChain(para->hash, para->ht_sz);
    freeKeywordTrie(para->trie, para->trie_sz);

    clearPara(para);

    return CME_OK;
}

int selectKeywordMatchAlg(DGateKeyword * keyword,
                          unsigned int n,
                          DLPKeywordPara* insen_para,
                          DLPKeywordPara* sen_para)
{
    unsigned int i, i0, i1, i2, i3;
    unsigned int * short_idx0 = NULL;
    unsigned int short_num0 = 0;
    unsigned int * long_idx0 = NULL;
    unsigned int long_num0 = 0;
    unsigned int long_kwMinLen0 = MAX_KEYWORD_LEN;

    unsigned int * short_idx1 = NULL;
    unsigned int short_num1 = 0;
    unsigned int * long_idx1 = NULL;
    unsigned int long_num1 = 0;
    unsigned int long_kwMinLen1 = MAX_KEYWORD_LEN;
    int result = CME_OK;

    /*1. get minlen and related number*/
    for (i = 0; i < n; ++i)
    {
        if( keyword[i].caseSensative == CASE_INSEN ) //case insensitive
        {
            if( keyword[i].wordlen >= KEYWORD_THRE )
            {
                long_num0++;
                if( keyword[i].wordlen < long_kwMinLen0 )
                {
                    long_kwMinLen0 = keyword[i].wordlen;
                }
            }
            else
            {
                short_num0++;
            }
        }
        else //case sensitive
        {
            if( keyword[i].wordlen >= KEYWORD_THRE )
            {
                long_num1++;
                if( keyword[i].wordlen < long_kwMinLen1 )
                {
                    long_kwMinLen1 = keyword[i].wordlen;
                }
            }
            else
            {
                short_num1++;
            }
        }
    }

    /*2. malloc space for insensitve and sensitive short and long arrays*/
    do
    {
        short_idx0 = (unsigned int *)malloc(short_num0 * sizeof(unsigned int));
        if( short_idx0 == NULL )
        {
            result = CME_MEM_ERR;
            //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("no mem for short_idx0"));
            break;
        }

        long_idx0 = (unsigned int *)malloc(long_num0 * sizeof(unsigned int));
        if( long_idx0 == NULL )
        {
            result = CME_MEM_ERR;
            //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("no mem for long_idx0"));
            break;
        }

        short_idx1 = (unsigned int *)malloc(short_num1 * sizeof(unsigned int));
        if( short_idx1 == NULL )
        {
            result = CME_MEM_ERR;
            //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("no mem for short_idx1"));
            break;
        }

        long_idx1 = (unsigned int *)malloc(long_num1 * sizeof(unsigned int));
        if( long_idx1 == NULL )
        {
            result = CME_MEM_ERR;
            //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("no mem for long_idx1"));
            break;
        }
    } while (0);

    if( result != CME_OK )
    {
        DLP_FREE(short_idx0);
        DLP_FREE(long_idx0);
        DLP_FREE(short_idx1);
        DLP_FREE(long_idx1);

        return result;
    }


    /*3. set the idx to insensitive and sensitive short and long arrays*/
    i0=i1=i2=i3=0;
    for (i = 0; i < n; ++i)
    {
        if( keyword[i].caseSensative == CASE_INSEN ) //insensitive
        {
            if( keyword[i].wordlen >= KEYWORD_THRE )
            {
                long_idx0[i0++] = i;
            }
            else
            {
                short_idx0[i1++] = i;
            }
        }
        else //sensitive
        {
            if( keyword[i].wordlen >= KEYWORD_THRE )
            {
                long_idx1[i2++] = i;
            }
            else
            {
                short_idx1[i3++] = i;
            }
        }
    }

    assert(i0==long_num0 && i1==short_num0 && i2==long_num1 && i3==short_num1);

    insen_para->short_idx = short_idx0;
    insen_para->short_num = short_num0;
    insen_para->long_idx = long_idx0;
    insen_para->long_num = long_num0;
    insen_para->long_kwMinLen = long_kwMinLen0;

    sen_para->short_idx = short_idx1;
    sen_para->short_num = short_num1;
    sen_para->long_idx = long_idx1;
    sen_para->long_num = long_num1;
    sen_para->long_kwMinLen = long_kwMinLen1;

    return CME_OK;
}

int preprocessMultiPatternMatcher(DGateKeyword * keyword,
                                  unsigned int n,
                                  /*insensitive-case*/
                                  DLPKeywordPara* insen_para,
                                  /*sensitive-case*/
                                  DLPKeywordPara* sen_para)
{
    unsigned int result = CME_OK;

    if( insen_para == NULL || sen_para == NULL )
        return CME_PARA_ERR;

    clearPara(insen_para);
    clearPara(sen_para);

    do
    {
        result = selectKeywordMatchAlg(keyword, n, insen_para, sen_para);
        if (result != CME_OK)
        {
            //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("selectKeywordMatchAlg error"));
            break;
        }
        else
        {
            /* handle insensitive one*/
            if(insen_para->short_num >= MAGIC_NUMBER0)//using the trie
            {
                result = constructTrie( keyword, n, insen_para->short_idx, insen_para->short_num, CASE_INSEN,
                                        &(insen_para->trie), &(insen_para->trie_sz));
                if( result != CME_OK )
                {
                    //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("constructTrie error"));
                    break;
                }
            }

            if(insen_para->long_num >= MAGIC_NUMBER0)//using KRR
            {
                result = preprocess4KRRPatMatcher( keyword, n, insen_para->long_idx, insen_para->long_num, insen_para->long_kwMinLen, CASE_INSEN,
                                                   &(insen_para->hash), &(insen_para->ht_sz), &(insen_para->bp), insen_para->Char_bp_table, CHARTABLE_SZ);
                if( result != CME_OK )
                {
                    //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("preprocess4KRRPatMatcher error"));
                    break;
                }
            }

            /* handle sensitive one*/
            if(sen_para->short_num >= MAGIC_NUMBER1)//using the trie
            {
                result = constructTrie( keyword, n, sen_para->short_idx, sen_para->short_num, CASE_SEN,
                                        &(sen_para->trie), &(sen_para->trie_sz));
                if( result != CME_OK )
                {
                    //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("constructTrie error"));
                    break;
                }
            }

            if(sen_para->long_num >= MAGIC_NUMBER1)//using KRR
            {
                result = preprocess4KRRPatMatcher( keyword, n, sen_para->long_idx, sen_para->long_num, sen_para->long_kwMinLen, CASE_SEN,
                                                   &(sen_para->hash), &(sen_para->ht_sz), &(sen_para->bp), sen_para->Char_bp_table, CHARTABLE_SZ);
                if( result != CME_OK )
                {
                    //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("preprocess4KRRPatMatcher error"));
                    break;
                }
            }
        }
    } while(0);

    if( result != CME_OK )
    {
        clearPara(insen_para);
        clearPara(sen_para);
    }

    return result;
}


int dgateMultiKeywordMatcher(unsigned char * text,
                             unsigned int len,
                             DGateKeyword * keyword,
                             unsigned int n,
                             DLPKeywordPara* insen_para,
                             DLPKeywordPara* sen_para,
                             unsigned int * m,
                             int * id)
{
    int result;
    unsigned int i = 0;

    *m = 0;
    *id = 0;
    do
    {
        result = CME_OK;

        /*1. insensitive one*/
        if(insen_para->trie)//Trie to handle short-keywords
        {
            result = DLPTrieMatcher(text, len, keyword, n, CASE_INSEN,
                                    insen_para->trie,insen_para->trie_sz, m, id);
            if( result != CME_OK )
                break;
            if( *m > 0 )
                break;
        }
        else//BMH to handle short-keywords
        {
            for(i = 0; i < insen_para->short_num; i++)
            {
                result = dgateBMHRPatternMatcher(text, len, keyword + insen_para->short_idx[i], m, id);
                if( result != CME_OK )
                    break;
                if( *m > 0 )
                    break;
            }
            if( result != CME_OK )
                break;
            if( *m > 0 )
                break;
        }
        if(insen_para->hash)//KRR to handle long-keywords
        {
            result = dgateKRRPatternMatcher(text, len, keyword, n,
                                            insen_para->long_kwMinLen, insen_para->bp,
                                            insen_para->hash, insen_para->ht_sz,
                                            insen_para->Char_bp_table, CHARTABLE_SZ, CASE_INSEN,
                                            m,id);
            if( result != CME_OK )
                break;
            if( *m > 0 )
                break;
        }
        else//BMH to handle long-keywords
        {
            for(i = 0; i < insen_para->long_num; i++)
            {
                result = dgateBMHRPatternMatcher(text, len, keyword + insen_para->long_idx[i], m, id);
                if( result != CME_OK )
                    break;
                if( *m > 0 )
                    break;
            }
            if( result != CME_OK )
                break;
            if( *m > 0 )
                break;
        }

        /*2. sensitive one*/
        if(sen_para->trie)
        {
            result = DLPTrieMatcher(text, len, keyword, n, CASE_SEN,
                                    sen_para->trie,sen_para->trie_sz,
                                    m, id);
            if( result != CME_OK )
                break;
            if( *m > 0 )
                break;
        }
        else
        {
            for(i = 0; i < sen_para->short_num; i++)
            {
                result = dgateBMHRPatternMatcher(text, len, keyword + sen_para->short_idx[i], m, id);
                if( result != CME_OK )
                    break;
                if( *m > 0 )
                    break;
            }
            if( result != CME_OK )
                break;
            if( *m > 0 )
                break;
        }
        if(sen_para->hash)
        {
            result = dgateKRRPatternMatcher(text, len, keyword, n,
                                            sen_para->long_kwMinLen, sen_para->bp,
                                            sen_para->hash, sen_para->ht_sz,
                                            sen_para->Char_bp_table, CHARTABLE_SZ, CASE_SEN,
                                            m, id);
            if( result != CME_OK )
                break;
            if( *m > 0 )
                break;
        }
        else
        {
            for(i = 0; i < sen_para->long_num; i++)
            {
                result = dgateBMHRPatternMatcher(text, len, keyword + sen_para->long_idx[i], m, id);
                if( result != CME_OK )
                    break;
                if( *m > 0 )
                    break;
            }
            if( result != CME_OK )
                break;
            if( *m > 0 )
                break;
        }
    } while (0);

    if( result != CME_OK )
    {
        *m = 0;
    }

    return result;
}
