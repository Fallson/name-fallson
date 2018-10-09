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
*************************************************************************/
#ifndef CME_KRRPATMATCH_H
#define CME_KRRPATMATCH_H

#include "cmeKeyword.h"


typedef struct _DGateKRRHash{
	int kwIdx;
	struct _DGateKRRHash * next;
} DGateKRRHash; 


#ifdef __cplusplus
extern "C" {
#endif

int freeKRRHashChain(DGateKRRHash * hash,
					 unsigned int siz);

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
                           int * id);

int preprocess4KRRPatMatcher(DGateKeyword * keyword,
                             unsigned int n,
                             unsigned int * idx,
                             unsigned int idx_num,
                             unsigned int kwMinLen,
                             unsigned short caseSensative,
                             DGateKRRHash ** hash,
                             unsigned int * ht_sz,
                             unsigned int * bp,
                             unsigned int char_bp_table[],
                             unsigned int char_bp_table_sz);

#ifdef __cplusplus
}
#endif

#endif
