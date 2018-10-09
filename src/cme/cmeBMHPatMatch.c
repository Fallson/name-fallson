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
* Remark: Implemetation of Boyer-Moore-Horspool Algorithm for 1-pattern *
* 		  match.														*
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmeErrCodeBasic.h"
#include "cmeBMHPatMatch.h"


#define	ALPHABET_SIZE		256	

#define	DGATE_tolower(c)	(((unsigned int)c > 64 && (unsigned int)c < 91 ) ? \
    ((unsigned int)c + 32) : ((unsigned int)c))


/*===========================================================
**
** Boyer-Moore-Horspool-Raita(BMHR) Algorithm
**===========================================================*/
int dgateBMHRPatternMatcher(unsigned char * text,
                            unsigned int len,
                            DGateKeyword * keyword,
                            unsigned int * m,
                            int * id)
{
    int result = CME_OK;
    unsigned int patlen = keyword->wordlen;
    unsigned int patlen1 = patlen - 1;
    unsigned int i = 0;
    unsigned char lastch = 0;
    unsigned char firstch = 0;
    unsigned char ch = 0;
    unsigned char ch0 = 0;
    unsigned int pos;
    int cmp_ret;

    if (patlen < MIN_KEYWORD_LEN || patlen > len) {
        return CME_OK;
    }

    if( keyword->pat == NULL || keyword->delta == NULL )
    {
        keyword->pat = (unsigned char *)malloc(patlen + 1);
        if( keyword->pat == NULL )
            return CME_MEM_ERR;

        keyword->pat[patlen] = 0;
        strncpy(keyword->pat, keyword->word, patlen);

        if (!keyword->caseSensative) {
            for (i = 0; i < patlen; ++i) {
                keyword->pat[i] = DGATE_tolower((keyword->pat[i]));
            }
        }

        keyword->delta = (unsigned int *)malloc(sizeof(unsigned int) * ALPHABET_SIZE);
        if (keyword->delta == NULL) {
            if (keyword->pat != NULL) free(keyword->pat);
            return CME_MEM_ERR;
        }

        for (i = 0; i < ALPHABET_SIZE; ++i) {
            keyword->delta[i] = patlen;
        }
        for (i = 0; i < patlen1; ++i) {
            keyword->delta[(unsigned int)keyword->pat[i]] = patlen1 - i;
        }
    }

    lastch = keyword->pat[patlen1];
    firstch = keyword->pat[0];
    i = patlen1;

    while (i < len) {
        if (!keyword->caseSensative) {
            ch = DGATE_tolower((text[i]));
        }
        else {
            ch = text[i];
        }

        pos = i - patlen1;
        if (ch == lastch){
            if (!keyword->caseSensative) {
                ch0 = DGATE_tolower((text[i - patlen1]));
            }
            else {
                ch0 = text[i - patlen1];
            }

            if (ch0 == firstch) {
#ifdef	_USE_MICRO_4_HEAVY_FUNC
                DGATE_STRNCMP(cmp_ret, keyword->caseSensative, pat, text + pos, patlen1);
#else
                cmp_ret = dgate_strncmp(keyword->caseSensative, keyword->pat, text + pos, patlen1);
#endif
                if (cmp_ret == 0) {
                    ++(*m);
                    *id = (int)keyword->ID;
                    break;
                }
            }
        }

        i += keyword->delta[ch];
    }

    return result;
}
