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
*                   09/26/2005.                                         *
*                                                                       *
* Remark: Implemetation of Karp-Rabin-Ren Algorithm for Multi-pattern 	*
* 		  Match.														*
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#ifndef WIN32
#include <ctype.h>
#endif

#include "cmeErrCodeBasic.h"
#include "cmeKRRPatMatch.h"
#include "cmeKeywordMatch.h"


#define	KRR_BASE_RSHIFT	  8
#define	KRR_BASE	      256
#define	KRR_PRIME	      70037

#define	DGATE_tolower(c)	(((unsigned int)c > 64 && (unsigned int)c < 91 ) ? \
    ((unsigned int)c + 32) : ((unsigned int)c))

#define CALC_NEXT_HASH_VALUE_BY_ITERATION0(v0, C0, bp1, Cp, base, prime)	\
    (DGATE_tolower(Cp) + ((v0 + prime - (bp1 * DGATE_tolower(C0)) % prime) << base)) % prime
//(DGATE_tolower(Cp) + base * (v0 + prime - (bp1 * DGATE_tolower(C0)) % prime)) % prime

#define CALC_NEXT_HASH_VALUE_BY_ITERATION1(v0, C0, bp1, Cp, base, prime)	\
    ((unsigned int)(Cp) + ((v0 + prime - (bp1 * (unsigned int)C0) % prime) << base)) % prime
//((unsigned int)Cp + base * (v0 + prime - (bp1 * (unsigned int)C0) % prime)) % prime

#define GET_KEYWORD_INDEX_BY_HASH(v, hash, caseS, text, len, keyword, ptr, wlen, retcode) { \
    retcode = -1; \
    if (hash[v].kwIdx >= 0) { \
    ptr = hash + v; \
    while (ptr != NULL) { \
    int cmp_ret; \
    wlen = keyword[ptr->kwIdx].wordlen; \
    DGATE_STRNCMP(cmp_ret, caseS, keyword[ptr->kwIdx].word, text, wlen); \
    if (wlen <= len && cmp_ret == 0){ \
    retcode = ptr->kwIdx; \
    break; \
    }; \
    ptr = ptr->next; \
    }; \
    }; \
    }

int freeKRRHashChain(DGateKRRHash * hash,
                     unsigned int siz)
{
    unsigned int i;
    DGateKRRHash * ptr1 = NULL;
    DGateKRRHash * ptr2 = NULL;

    if (hash == NULL) {
        return CME_OK;
    }

    for (i = 0; i < siz; ++i) {
        ptr1 = hash[i].next;
        while (ptr1 != NULL) {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            if (ptr2 != NULL) {
                free(ptr2);
            }
        }
    }

    if (hash != NULL) {
        free(hash);
    }
    return CME_OK;
}


int getKeywordIndexByHash(unsigned int v,
                          DGateKRRHash * hash,
                          unsigned short caseS,
                          unsigned char * text,
                          unsigned int len,
                          unsigned int i,
                          DGateKeyword * keyword,
                          unsigned int * m,
                          int * id)
{
    int result = CME_OK;
    DGateKRRHash * ptr = NULL;
    unsigned int wlen = 0;
    int cmp_ret;

    if (hash[v].kwIdx < 0) {
        return CME_OK;
    }

    ptr = hash + v;
    while (ptr != NULL)
    {
        wlen = keyword[ptr->kwIdx].wordlen;
        cmp_ret = dgate_strncmp(caseS, keyword[ptr->kwIdx].word, text, wlen);
        if (wlen <= len && cmp_ret == 0)
        {
            ++(*m);
            *id = (int)keyword[ptr->kwIdx].ID;
            return CME_OK;
        }
        ptr = ptr->next;
    }
    return result;
}


int putKeywordIdxIntoHashTab(DGateKRRHash * hash,
                             unsigned int siz,
                             unsigned int v,
                             int i)
{
    DGateKRRHash * ptr1 = &(hash[v]);
    DGateKRRHash * ptr = NULL;

    if (hash[v].kwIdx == -1) {
        hash[v].kwIdx = i;
    }
    else {
        ptr = (DGateKRRHash *)malloc(sizeof(DGateKRRHash));
        if (ptr == NULL) {
            //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("no mem for ptr"));
            return CME_MEM_ERR;
        }

        ptr->kwIdx = i;
        ptr->next = NULL;

        while (ptr1->next != NULL) {
            ptr1 = ptr1->next;
        }
        ptr1->next = ptr;
    }
    return CME_OK;
}

/*
unsigned int calcNextHashValueByIteration(unsigned int v0,
                                                                              unsigned char C0,
                                                                              unsigned int bp1,
                                                                              unsigned char Cp,
                                                                              unsigned short caseS,
                                                                              unsigned int base,
                                                                              unsigned int prime)
{
        unsigned int v = 0;
        unsigned int tmp;

        v = (caseS != 0 ? (unsigned int)Cp : (unsigned int)DGATE_tolower(Cp));
        tmp =
        (bp1 * (caseS != 0 ? (unsigned int)C0 : (unsigned int)DGATE_tolower(C0))) % prime;
//	v += base * (v0 > tmp ? (v0 - tmp) : (v0 + prime - tmp));
        v += (v0 > tmp ? (v0 - tmp) : (v0 + prime - tmp)) << base ;
        v %= prime;
        return v;
}
*/

unsigned int calcNextHashValueByIteration_KRR(unsigned int v0,
                                              unsigned char C0,
                                              unsigned int bp1,
                                              unsigned char Cp,
                                              unsigned short caseS,
                                              unsigned int char_bp_table[],
                                              unsigned int char_bp_table_sz,
                                              unsigned int base,
                                              unsigned int prime)
{
    unsigned int v = 0;
    unsigned int tmp;
    unsigned char ch;

    v = (caseS != 0 ? (unsigned int)Cp : (unsigned int)DGATE_tolower(Cp));
    ch = (caseS != 0 ? (unsigned int)C0 : (unsigned int)DGATE_tolower(C0));
    tmp = char_bp_table[ch];
    v += (v0 >= tmp ? (v0 - tmp) : (v0 + prime - tmp)) << base ;
    v %= prime;
    return v;
}


unsigned int calcHashValueByHornerRule_KRR(unsigned char * word,
                                           unsigned int len,
                                           unsigned short caseS,
                                           unsigned int base,
                                           unsigned int prime)
{
    unsigned int i;
    unsigned int v;

    v = (caseS != 0 ? (unsigned int)word[0] : (unsigned int)DGATE_tolower(word[0]));
    for (i = 1; i < len; ++i) {
        //		v = v * base +
        //			(caseS != 0 ? (unsigned int)word[i] : (unsigned int)DGATE_tolower(word[i]));
        v = (v << base) +
                (caseS != 0 ? (unsigned int)word[i] : (unsigned int)DGATE_tolower(word[i]));
        v = v % prime;
    }
    return v;
}


unsigned int calcBP1Value(unsigned int p,
                          unsigned int base,
                          unsigned int prime,
                          unsigned int char_bp_table[],
                          unsigned int char_bp_table_sz)
{
    unsigned int i;
    unsigned int v = 1;

    for (i = 1; i < p; ++i) {
        //		v = (v * base) % prime;
        v = (v << base) % prime;
    }

    for (i = 0; i < char_bp_table_sz; ++i) {
        char_bp_table[i] = (i * v) % prime;
    }

    return v;
}


/*===========================================================
**
** Karp-Rabin-Ren Algorithm
**===========================================================*/
int dgateKRRPatternMatcher(unsigned char * text,
                           unsigned int len,
                           DGateKeyword * keyword,
                           unsigned int n,
                           unsigned int kwMinLen,
                           unsigned int bp,
                           DGateKRRHash * hash,
                           unsigned int ht_sz,
                           unsigned int char_bp_table[],
                           unsigned int char_bp_table_sz,
                           unsigned short caseSensative,
                           unsigned int * m,
                           int * id)
{
    int result = CME_OK;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int end = 0;
    unsigned int hv;

#ifdef	_USE_MICRO_4_HEAVY_FUNC
    DGateKRRHash * ptr = NULL;
    unsigned int wlen = 0;
    unsigned char * txt;
    unsigned int n;
#endif

    if (len < kwMinLen) {
        return CME_OK;
    }

    end = len - kwMinLen;
    i = 0;
    hv = calcHashValueByHornerRule_KRR(text, kwMinLen, caseSensative, KRR_BASE_RSHIFT, KRR_PRIME);
    result = getKeywordIndexByHash(hv, hash, caseSensative, text + i, len - i, i,
                                   keyword, m, id);
    if( result != CME_OK )
        return result;
    if( *m > 0 )
        return CME_OK;

    while (i < end)
    {
#ifdef _USE_MICRO_4_HEAVY_FUNC
        if (caseSensative) {
            hv = CALC_NEXT_HASH_VALUE_BY_ITERATION1(hv, (text[i]), bp,
                                                    (text[i + kwMinLen]), KRR_BASE_RSHIFT, KRR_PRIME);
        }
        else {
            hv = CALC_NEXT_HASH_VALUE_BY_ITERATION0(hv, (text[i]), bp,
                                                    (text[i + kwMinLen]), KRR_BASE_RSHIFT, KRR_PRIME);
        }
#else
        hv = calcNextHashValueByIteration_KRR(hv, text[i], bp, text[i + kwMinLen],
                                              caseSensative, char_bp_table, char_bp_table_sz, KRR_BASE_RSHIFT, KRR_PRIME);
#endif
        ++i;

        result = getKeywordIndexByHash(hv, hash, caseSensative, text + i, len - i, i,
                                       keyword, m, id);
        if( result != CME_OK )
            break;
        if( *m > 0 )
            return CME_OK;
    }

    return result;
}


int preprocess4KRRPatMatcher(DGateKeyword * keyword,
                             unsigned int n,
                             unsigned int *idx,
                             unsigned int idx_num,
                             unsigned int kwMinLen,
                             unsigned short caseSensative,
                             DGateKRRHash ** hash,
                             unsigned int * ht_sz,
                             unsigned int * bp,
                             unsigned int char_bp_table[],
                             unsigned int char_bp_table_sz)
{
    int result;
    unsigned int i;
    unsigned int hv;

    *hash = NULL;
    *ht_sz = 0;
    *bp = 0;

    if(n == 0 || idx_num == 0)
    {
        return CME_OK;
    }

    *bp = calcBP1Value(kwMinLen, KRR_BASE_RSHIFT, KRR_PRIME, char_bp_table, char_bp_table_sz);
    *hash = (DGateKRRHash *)malloc(sizeof(DGateKRRHash) * KRR_PRIME);
    if( *hash == NULL )
    {
        //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("no mem for hash"));
        return CME_MEM_ERR;
    }
    *ht_sz = KRR_PRIME;

    for (i = 0; i < *ht_sz; ++i)
    {
        (*hash)[i].kwIdx = -1;
        (*hash)[i].next = NULL;
    }

    result = CME_OK;

    for (i = 0; i< idx_num; ++i)
    {
        if (keyword[idx[i]].word != NULL &&
                keyword[idx[i]].wordlen >= KEYWORD_THRE &&
                keyword[idx[i]].wordlen <= MAX_KEYWORD_LEN )
        {
            hv = calcHashValueByHornerRule_KRR(keyword[idx[i]].word, kwMinLen, caseSensative,
                                               KRR_BASE_RSHIFT, KRR_PRIME);
            result = putKeywordIdxIntoHashTab(*hash, *ht_sz, hv, idx[i]);
            if (result != CME_OK)
            {
                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("putKeywordIdxIntoHashTab fail (%d) on keyword %d"), result, idx[i]);
                break;
            }
        }
    }

    if (result != CME_OK)
    {
        freeKRRHashChain(*hash, *ht_sz);
    }
    return result;
}
