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
*               (1) Created by Fallson Xu, TrendMicro, Inc.             *
*                   04/24/2010.                                         *
*                                                                       *
*************************************************************************/
#ifndef CME_TRIEPATMATCH_H
#define CME_TRIEPATMATCH_H

#include "cmeKeyword.h"

typedef struct _KWIdxArr
{
	int* kwIdx;
	int size;
	int capacity;
}KWIdxArr;

typedef struct _DLPTrieNode
{
	unsigned char ch;
	KWIdxArr kws;
	struct _DLPTrieNode* sibling;
	struct _DLPTrieNode* child;
}DLPTrieNode;

#ifdef __cplusplus
extern "C" {
#endif

void freeTire(DLPTrieNode** trie,
	          unsigned int trie_sz);

int constructTrie(DGateKeyword * keyword,
				  unsigned int n,
				  unsigned int * idx,
				  unsigned int idx_num,
				  unsigned short caseSensitive,
				  DLPTrieNode*** trie_out,
				  unsigned int* trie_sz_out);

int DLPTrieMatcher(unsigned char * text,
				   unsigned int len,
				   DGateKeyword * keyword,
				   unsigned int n,
				   unsigned short caseSensitive,
				   DLPTrieNode** trie,
				   unsigned int trie_sz,
                                   unsigned int * m,
                                   int * id);

#if 0
int dgateTriePatternMatcher(unsigned char * text,
							unsigned int len,
						    DGateKeyword * keyword,
							unsigned int n,
							int mode,
						    DGateKeywordRecord ** record, 
							unsigned int * m,
						    unsigned int * recArrSize);
#endif

#ifdef __cplusplus
}
#endif

#endif
