#ifndef CME_KEYWORD_H
#define CME_KEYWORD_H

#include "cmeInt64Def.h"


#define MIN_KEYWORD_LEN			3
#define MAX_KEYWORD_LEN			256


typedef	longlong	DGateKeywordID;
typedef unsigned char	DGateKeywordStr[MAX_KEYWORD_LEN];


typedef struct	{
	DGateKeywordID   ID;
	unsigned short   caseSensative;
	DGateKeywordStr  word;
	unsigned int     wordlen;
        unsigned char*   pat;
        unsigned int*    delta;
} DGateKeyword;

typedef struct {
	DGateKeywordID	ID;
	unsigned int    pos;
} DGateKeywordRecord; 


#ifdef __cplusplus
extern "C" {
#endif

int resizeKeywordRecord(DGateKeywordRecord ** record,
						int siz,
						int * arrSiz);
int dgate_strncmp(unsigned short flag,
				  unsigned char * pat,
				  unsigned char * text,
				  unsigned int n);

#ifdef __cplusplus
}
#endif


#define DGATE_STRNCMP(cmp_ret, flag, pat, text, n) \
	do { \
		unsigned int DGATE_STRNCMP_i; \
		(cmp_ret) = 0; \
		\
		if ((flag)) { \
			(cmp_ret) = memcmp((void *)(pat), (void *)(text), (n)); \
		} \
		else { \
			for (DGATE_STRNCMP_i = 0; DGATE_STRNCMP_i < (n); ++DGATE_STRNCMP_i) { \
				if (DGATE_tolower((pat)[DGATE_STRNCMP_i]) != \
                    DGATE_tolower((text)[DGATE_STRNCMP_i])) { \
					(cmp_ret) = 1; \
					break; \
				} \
			} \
		} \
	} while(0);

#endif
