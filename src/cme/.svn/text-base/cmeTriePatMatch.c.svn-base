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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmeErrCodeBasic.h"
#include "cmeTriePatMatch.h"
#include "cmeKeywordMatch.h"

#ifdef WIN32
#pragma warning(disable:4996)
#endif

#define DLP_FREE(x)         if(x) {free(x);x=NULL;}
#define	DGATE_tolower(c)	(((unsigned int)c > 64 && (unsigned int)c < 91 ) ? \
                            ((unsigned int)c + 32) : ((unsigned int)c))

#define	ALPHABET_SIZE		256	
#define INIT_KWIDX_SIZE     16
#define INCR_KWIDX_SIZE     32

/************************************************************************/
/* */
/************************************************************************/
int resize_idxarr(int ** kwidx,
				  int size,
				  int* capacity)
{
	int i;
	int* new_idx;

	*capacity += INCR_KWIDX_SIZE;
	new_idx = (int*)malloc((*capacity)*sizeof(int));
	if (new_idx == NULL)
	{
                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("no mem for new_idx"));
		*capacity -= INCR_KWIDX_SIZE;
		return CME_MEM_ERR;
	}

	for (i = 0; i < size; ++i) 
	{
		new_idx[i] = (*kwidx)[i];
	}

	if (*kwidx != NULL) 
	{
		DLP_FREE(*kwidx);
	}
	*kwidx = new_idx;

	return CME_OK;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void put_idx2arr(KWIdxArr* arr, int kwidx)
{
	int ret = CME_OK;

	if( arr == NULL )
		return;
	if( arr->kwIdx == NULL )
		return;

	if( arr->size == arr->capacity )
	{
		ret = resize_idxarr( &(arr->kwIdx), arr->size, &(arr->capacity) );
		if( ret != CME_OK )
		{
			return;
		}
	}
	
	arr->kwIdx[arr->size] = kwidx;
	(arr->size)++;
}

/************************************************************************/
/* 
*/
/************************************************************************/
int create_idxarr(KWIdxArr* arr)
{
	if( arr == NULL )
		return CME_PARA_ERR;

	/*it must be an empty arr*/
	arr->kwIdx = (int*)malloc(INIT_KWIDX_SIZE*sizeof(int));
	if( arr->kwIdx == NULL )
	{
                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("malloc memory for kwIdx fail"));
		return CME_MEM_ERR;
	}

	arr->capacity = INIT_KWIDX_SIZE;
	arr->size = 0;

	return CME_OK;
}

/************************************************************************/
/* 
	return the added child node pointer
*/
/************************************************************************/
DLPTrieNode* add_child(DLPTrieNode** childptr,
					   unsigned char ch,
					   int kwIdx,
					   int wordend)
{
	int ret = CME_OK;
	DLPTrieNode* cld = NULL;

	if( childptr == NULL )
		return NULL;

	cld = (DLPTrieNode*)malloc(sizeof(DLPTrieNode));
	if( cld == NULL )
	{
                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("malloc memory for trienode fail"));
		return cld;
	}
	(*childptr) = cld;

	cld->ch = ch;
	cld->sibling = NULL;
	cld->child = NULL;
	if( wordend == 1 )
	{
		ret = create_idxarr(&(cld->kws));
		if( ret != CME_OK )
		{
			DLP_FREE(cld);
			return NULL;
		}
		put_idx2arr(&(cld->kws), kwIdx);
	}
	else
	{
		cld->kws.kwIdx = NULL;
		cld->kws.size = 0;
		cld->kws.capacity = 0;
	}

	return cld;
}

/************************************************************************/
/* 
	return the appended sibling node pointer
*/
/************************************************************************/
DLPTrieNode* append_sibling(DLPTrieNode* node,
							unsigned char ch,
							int kwIdx,
							int wordend)
{
	int ret = CME_OK;
	DLPTrieNode* sib = NULL;

	if( node == NULL )
		return NULL;
	if( node->sibling != NULL )
		return node->sibling;

	sib = (DLPTrieNode*)malloc(sizeof(DLPTrieNode));
	if( sib == NULL )
	{
                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("malloc memory for trienode fail"));
		return sib;
	}
	node->sibling = sib;

	sib->ch = ch;
	sib->sibling = NULL;
	sib->child = NULL;
	if( wordend == 1 )
	{
		ret = create_idxarr(&(sib->kws));
		if( ret != CME_OK )
		{
			DLP_FREE(sib);
			return NULL;
		}
		put_idx2arr(&(sib->kws), kwIdx);
	}
	else
	{
		sib->kws.kwIdx = NULL;
		sib->kws.size = 0;
		sib->kws.capacity = 0;
	}

	return sib;
}

static void freeNode(DLPTrieNode* node)
{
	DLPTrieNode * child = NULL;
	DLPTrieNode * sibling = NULL;

	if( node == NULL )
		return;

	child = node->child;
	sibling = node->sibling;

	DLP_FREE(node->kws.kwIdx);
	DLP_FREE(node);

	freeNode(child);
	freeNode(sibling);
}

void freeTire(DLPTrieNode** trie,
			  unsigned int trie_sz)
{
	unsigned int i;

	for( i = 0; i < trie_sz; i++ )
	{
		freeNode(trie[i]);
	}

	DLP_FREE(trie);
}

int constructTrie(DGateKeyword * keyword,
				  unsigned int n,
				  unsigned int * idx,
				  unsigned int idx_num,
				  unsigned short caseSensitive,
				  DLPTrieNode*** trie_out,
				  unsigned int* trie_sz_out)
{
	int result = CME_OK;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned char ch = 0;
	unsigned char last_ch = 0;
	int wordend = 0;
	DLPTrieNode* node = NULL;
	DLPTrieNode** childptr = NULL;
	DLPTrieNode** trie;
	unsigned int trie_sz;

	if( n == 0 || idx_num == 0 )
		return CME_OK;

	trie_sz = ALPHABET_SIZE;
	trie = (DLPTrieNode**) malloc(ALPHABET_SIZE*sizeof(DLPTrieNode*));
	if( trie == NULL )
	{
		return CME_MEM_ERR;
	}

	for( i = 0; i < ALPHABET_SIZE; i++)
	{
		trie[i] = NULL;
	}

	for( i = 0; i < idx_num; i++ )
	{
		if (keyword[idx[i]].word == NULL)
			continue;
		if( keyword[idx[i]].wordlen < MIN_KEYWORD_LEN||keyword[idx[i]].wordlen >= KEYWORD_THRE )
			continue;

		wordend = 0;
		ch = caseSensitive? keyword[idx[i]].word[0] : DGATE_tolower(keyword[idx[i]].word[0]);
		
		node = trie[ch];
		childptr = &trie[ch];

		for( j = 1; j < keyword[idx[i]].wordlen; j++ )
		{
			if( j == keyword[idx[i]].wordlen -1 )
				wordend = 1;

			ch = caseSensitive? keyword[idx[i]].word[j] : DGATE_tolower(keyword[idx[i]].word[j]);

			if( node == NULL )
			{
				add_child(childptr, ch, idx[i], wordend);
				node = (*childptr)->child;
				childptr = &((*childptr)->child);
			}
			else
			{
				for( ; node->ch != ch && node->sibling != NULL; node = node->sibling )
				{
					//do nthing
				}
				if( node->ch == ch ) //got the char
				{
					if( wordend )
					{
						if( node->kws.kwIdx == NULL )
						{
							result = create_idxarr(&(node->kws));
							if( result != CME_OK )
							{
                                                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("create_idxarr fail"));
								break;
							}
						}
						put_idx2arr(&(node->kws), idx[i]);
					}
				}
				else if( node->sibling == NULL )
				{
					node = append_sibling(node, ch, idx[i], wordend);
				}
				childptr = &(node->child);
				node = node->child;
			}
		}

		if( result != CME_OK )
			break;
	}

	if( result != CME_OK )
	{
		freeTire(trie, trie_sz);
		(*trie_out) = NULL;
		(*trie_sz_out) = 0;
	}
	else
	{
		(*trie_out) = trie;
		(*trie_sz_out) = trie_sz;
	}
	return result;
}

static void add_result(DGateKeywordID id,
				unsigned int pos,
				DGateKeywordRecord ** record, 
				unsigned int * m,
				unsigned int * recArrSize)
{
	int result;

	if (*m == *recArrSize)
	{
		result = resizeKeywordRecord(record, *m, recArrSize);
		if (result != CME_OK) 
		{
                        //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("resizeKeywordRecord fail"));
			return;					
		}
	}

	(*record)[*m].ID = id;
	(*record)[*m].pos = pos;
	++(*m);
}

int DLPTrieMatcher(unsigned char * text,
				   unsigned int len,
				   DGateKeyword * keyword,
				   unsigned int n,
				   unsigned short caseSensitive,
				   DLPTrieNode** trie,
				   unsigned int trie_sz,
                                   unsigned int * m,
                                   int * id)
{
	int result = CME_OK;
	unsigned char ch = 0;
	unsigned int i,j;
	int k;
	unsigned int state_sz = KEYWORD_THRE - 1;
	unsigned int cur_bucket = 0;
	DLPTrieNode * states[KEYWORD_THRE - 1];

	//match
	for( i = 0; i < state_sz; i++ )
	{
		states[i] = NULL;
	}

	for( i = 0; i < len; i++ )
	{
		ch = caseSensitive? text[i] : DGATE_tolower(text[i]);

		//process the states first
		//and got the empty bucket
		for( j = 0; j < state_sz; j++ )
		{
			if( states[j] == NULL )
			{
				cur_bucket = j;
			}
			else
			{
				for( ; states[j]->ch != ch && states[j]->sibling != NULL; states[j] = states[j]->sibling)
				{
				}
				if( states[j]->ch == ch )//we get match the ch
				{
					if( states[j]->kws.kwIdx != NULL ) //the whole word matched
					{
						for( k = 0; k < states[j]->kws.size; k++ )
						{
                                                        ++(*m);
                                                        *id = (int)keyword[states[j]->kws.kwIdx[k]].ID;
                                                        return CME_OK;
						}

						if( states[j]->child == NULL )
						{
							states[j] = NULL;
							cur_bucket = j;
						}
						else
						{
							states[j] = states[j]->child;
						}
					}
					else
					{
						//do nothing and waiting for the next char.
						states[j] = states[j]->child;
					}
				}
				else if( states[j]->sibling == NULL ) //we get no match of ch
				{
					states[j] = NULL;
					cur_bucket = j;
				}
			}
		}
		
		//add new state into states
		if( ch < trie_sz && trie[ch] != NULL )
		{
			states[cur_bucket] = trie[ch];
		}
	}
	
	return result;
}


/************************************************************************/
/* 
	Trie search
*/
/************************************************************************/
#if 0
int dgateTriePatternMatcher(unsigned char * text,
							unsigned int len,
							DGateKeyword * keyword,
							unsigned int n,
							int mode, //mode 0: non-caseSensitive | mode 1: caseSensitive | mode 2: both case
							DGateKeywordRecord ** record,
							unsigned int * m,
							unsigned int * recArrSize)
{
	int result = CME_OK;
	unsigned int i;
	unsigned char* lower_text = NULL;
	DGateKeywordID * nocase_keywords = NULL;
	unsigned int   nocase_num = 0;
	DGateKeywordID * case_keywords = NULL;
	unsigned int   case_num = 0;

	do 
	{
		if( mode == 0 )
		{
			//process the lower_text
			lower_text = (unsigned char*)malloc(sizeof(unsigned char) * len);
			if( lower_text == NULL )
			{
				result = CME_MEM_ERR;
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("dgateSADBPatternMatcher: memory allocation problem (no mem for lower_text)"));
				break;
			}
			for(i = 0; i < len; i++)
			{
				lower_text[i] = DGATE_tolower(text[i]);
			}

			//process the nocase_keyword
			nocase_keywords = (DGateKeywordID *)malloc(n * sizeof(DGateKeywordID));
			if( nocase_keywords == NULL )
			{
				result = CME_MEM_ERR;
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("dgateSADBPatternMatcher: memory allocation problem (no mem for nocase_keywords)"));
				break;
			}

			nocase_num = 0;
			for(i = 0; i < n; i++)
			{
				if( keyword[i].wordlen < KEYWORD_THRE && keyword[i].caseSensative == 0 )
				{
					nocase_keywords[nocase_num++] = keyword[i].ID;
				}
			}

			if( nocase_num == 0 )
			{
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("nocase_num == 0"));
				break;
			}

			result = DLPTrieMatcher(lower_text, len, keyword, n, 
				nocase_keywords, nocase_num, 0, record, m, recArrSize);
		}
		else if( mode == 1 )
		{
			case_keywords = (DGateKeywordID *)malloc(n * sizeof(DGateKeywordID));
			if( case_keywords == NULL )
			{
				result = CME_MEM_ERR;
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("dgateSADBPatternMatcher: memory allocation problem (no mem for case_keywords)"));
				break;
			}

			case_num = 0;
			for(i = 0; i < n; i++)
			{
				if( keyword[i].wordlen < KEYWORD_THRE && keyword[i].caseSensative == 1 )
				{
					case_keywords[case_num++] = keyword[i].ID;
				}
			}

			if( case_num == 0 )
			{
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("case_num == 0"));
				break;
			}

			result = DLPTrieMatcher(text, len, keyword, n,
				case_keywords, case_num, 1, record, m, recArrSize);
		}
		else
		{
			//process the lower_text
			lower_text = (unsigned char*)malloc(sizeof(unsigned char) * len);
			if( lower_text == NULL )
			{
				result = CME_MEM_ERR;
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("dgateSADBPatternMatcher: memory allocation problem (no mem for lower_text)"));
				break;
			}
			for(i = 0; i < len; i++)
			{
				lower_text[i] = DGATE_tolower(text[i]);
			}

			//process the nocase_keyword and case_keyword
			nocase_keywords = (DGateKeywordID *)malloc(n * sizeof(DGateKeywordID));
			if( nocase_keywords == NULL )
			{
				result = CME_MEM_ERR;
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("dgateSADBPatternMatcher: memory allocation problem (no mem for nocase_keywords)"));
				break;
			}

			case_keywords = (DGateKeywordID *)malloc(n * sizeof(DGateKeywordID));
			if( case_keywords == NULL )
			{
				result = CME_MEM_ERR;
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("dgateSADBPatternMatcher: memory allocation problem (no mem for case_keywords)"));
				break;
			}

			nocase_num = 0;
			case_num = 0;
			for(i = 0; i < n; i++)
			{
				if( keyword[i].wordlen < KEYWORD_THRE )
				{
					if( keyword[i].caseSensative == 0 )
					{
						nocase_keywords[nocase_num++] = keyword[i].ID;
					}
					else if(keyword[i].caseSensative == 1)
					{
						case_keywords[case_num++] = keyword[i].ID;
					}
				}
			}

			if( case_num == 0 )
			{
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("case_num == 0"));
				break;
			}
			result = DLPTrieMatcher(text, len, keyword, n, 
				case_keywords, case_num, 1, record, m, recArrSize);
			if( result != CME_OK )
				break;

			if( nocase_num == 0 )
			{
                                //LogMsg(LOG_LEVEL_NORMAL, DLP_LOG_ERR("nocase_num == 0"));
				break;
			}

			result = DLPTrieMatcher(lower_text, len, keyword, n,
				nocase_keywords, nocase_num, 0, record, m, recArrSize);
		}

	} while (0);
	
	DLP_FREE(lower_text);
	DLP_FREE(nocase_keywords);
	DLP_FREE(case_keywords);

	return result;
}

#endif
