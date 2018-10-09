#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmeErrCodeBasic.h"
#include "cmeKeyword.h"


#define KEYWORD_REC_INCR_SIZE	200

#define	DGATE_tolower(c)	(((unsigned int)c > 64 && (unsigned int)c < 91 ) ? \
    ((unsigned int)c + 32) : ((unsigned int)c))



int resizeKeywordRecord(DGateKeywordRecord ** record,
                        int siz,
                        int * arrSiz)
{
    int i;
    DGateKeywordRecord * newArray;

    *arrSiz += KEYWORD_REC_INCR_SIZE;
    newArray = (DGateKeywordRecord *)malloc(sizeof(DGateKeywordRecord) * (*arrSiz));
    if (newArray == NULL) {
        //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("no mem for newArray"));
        *arrSiz -= KEYWORD_REC_INCR_SIZE;
        return 	CME_MEM_ERR;
    }

    for (i = 0; i < siz; ++i) {
        newArray[i].ID = (*record)[i].ID;
        newArray[i].pos = (*record)[i].pos;
    }

    if (*record != NULL) {
        free(*record);
    }
    *record = newArray;

    return CME_OK;
}

/*
int dgate_strncmp(unsigned short flag,
                                  unsigned char * pat,
                                  unsigned char * text,
                                  unsigned int n)
{
        unsigned int i;

        if (flag) {
                return strncmp(pat, text, n);
        }

        for (i = 0; i < n; ++i) {
                //if(tolower(pat[i])!=tolower(text[i]))
                if (DGATE_tolower(pat[i]) != DGATE_tolower(text[i])) {
                        return 	1;
                }
        }

        return 0;
}
*/

int dgate_strncmp(unsigned short flag,
                  unsigned char * pat,
                  unsigned char * text,
                  unsigned int n)
{
    unsigned int i;
    int cmp_ret = 0;

    if (flag) {
        /*
                for (i = 0; i < n; ++i) {
                        if (pat[i] != text[i]) {
                                cmp_ret = 1;
                                break;
                        }
                }
                */
        cmp_ret = memcmp((void *)pat, (void *)text, n);
        return cmp_ret;
    }

    for (i = 0; i < n; ++i) {
        if (DGATE_tolower(pat[i]) != DGATE_tolower(text[i])) {
            cmp_ret = 1;
            break;
        }
    }

    return cmp_ret;
}
