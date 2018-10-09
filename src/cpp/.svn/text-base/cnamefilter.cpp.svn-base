#include "cnamefilter.h"
#include "cpianpang.h"
#include "cbook.h"
#include <assert.h>
#include <string.h>
#include <QDebug>
#include "util.h"


#define INVALID            -99999
/***********************************************************************************************/
CNameFilter::CNameFilter()
{
    pBook = NULL;
    pPianpang = NULL;
    firstname_num = 0;

    b_init = false;
}

CNameFilter::~CNameFilter()
{
}

bool CNameFilter::init(const std::string &pp_fp)
{
    int ret = FN_OK;
    do{
        /*0. init book object*/
        pBook = new CBook;
        if( pBook == NULL )
        {
            ret = FN_ERR;
            break;
        }

        if( !pBook->init() )
        {
            ret = FN_ERR;
            break;
        }

        /*1. firstname*/
        firstname_num = 0;

        /*2 init pianpang*/
        pianpang_filepath = pp_fp;
        pPianpang = new CPianPang;
        if( pPianpang == NULL )
        {
            ret = FN_ERR;
            break;
        }

        if( !pPianpang->init(pianpang_filepath) )
        {
            ret = FN_ERR;
            break;
        }
        pianpang_idx.clear();
    }while(0);

    if( ret != FN_OK )
    {
       clear();
       b_init = false;
    }
    else
    {
        b_init = true;
    }

    return (ret == FN_OK)?true:false;
}

static bool matchCnt(const std::vector<int>& pp_cnt, const std::vector<int>& pp_match_cnt)
{
    //assert(pp_cnt.size() == pp_match_cnt.size())

    for( int i = 0; i < pp_cnt.size(); i++ )
    {
        if( pp_cnt[i] < pp_match_cnt[i] )
            return false;
    }

    return true;
}

bool CNameFilter::search(std::vector<int> &pos, std::vector<int>& len)
{
    if( !b_init )
        return false;

    if( this->firstname_num != pianpang_idx.size() ) //we set the pianpang is equal to the number of first name
        return false;

    pos.clear();
    len.clear();

    //pp_cnt[i]: Invalid means this pianpang is not in the calculation
    //           Elsewise it contains the matched pianpang char count
    std::vector<int> pp_cnt;
    std::vector<int> pp_match_cnt;
    pp_cnt.resize(pPianpang->getGroupNum());
    pp_match_cnt.resize(pPianpang->getGroupNum());
    for( int i = 0; i < pp_cnt.size(); i++ )
    {
        pp_cnt[i] = INVALID;
        pp_match_cnt[i] = INVALID;
    }

    for( int i = 0; i < pianpang_idx.size(); i++ )
    {
        if( pianpang_idx[i] < 0 ) //it means any pianpang is ok
            continue;
        else if( pianpang_idx[i] < pp_cnt.size() )
        {
            if( pp_cnt[pianpang_idx[i]] == INVALID )
            {
                pp_cnt[pianpang_idx[i]] = 0;
            }

            if( pp_match_cnt[pianpang_idx[i]] == INVALID )
            {
                pp_match_cnt[pianpang_idx[i]] = 1;
            }
            else
            {
                pp_match_cnt[pianpang_idx[i]]++;
            }
        }
        else
        {
            qDebug() << "pianpang idx is out of boundary";
            return false;
        }
    }

    //0. calculate the first firstname_num's pianpang
    std::vector<utf8Char> chs;
    chs.resize(firstname_num);
    std::vector<int> idxes;
    idxes.resize(firstname_num);
    int i = 0;
    for( ;i < firstname_num; )
    {
        if( !pBook->getNextUtf8Char(chs[i]) ) //fk, the book is too short
        {
            printf("fk, the book is too short\n");
            return false;
        }

        if( !checkUtf8Char(chs[i].buf, chs[i].len) )
        {
            qDebug() << "invalid utf char (" << chs[i].buf <<") - (" << chs[i].len << ")@"<<pBook->getCurPos();

            i = 0; //reset to fill the content;
            continue;
        }

        if( chs[i].len == 1 ) //ascii char not support
        {
            i = 0; //reset to fill the content;
            continue;
        }

        idxes[i] = pPianpang->getGroupIdx(chs[i].buf,chs[i].len);
        if( idxes[i] >= 0 )
        {
            assert( idxes[i] < pp_cnt.size() );

            if( pp_cnt[idxes[i]] != INVALID )
                pp_cnt[idxes[i]]++;
        }
        i++;
    }

    if( matchCnt(pp_cnt, pp_match_cnt) )//we got one
    {
        int l = 0;
        for( int i = 0; i < firstname_num; i++ )
        {
            l += chs[i].len;
        }
        pos.push_back(pBook->getCurPos() - l);
        len.push_back(l);
    }

    //1. iterate the book
    int last = 0;
    int cur = firstname_num-1;
    do{
        if( idxes[last] >= 0 ) //remove last index first
        {
            if( pp_cnt[idxes[last]] != INVALID )
                pp_cnt[idxes[last]]--;
        }
        last = (last+1)%firstname_num;

        cur = (cur+1)%firstname_num;
        if( !pBook->getNextUtf8Char(chs[cur]) ) //the end of the content
            break;

        if( !checkUtf8Char(chs[cur].buf, chs[cur].len) )
        {
            qDebug() << "invalid utf char (" << chs[cur].buf <<") - (" << chs[cur].len << ")@"<<pBook->getCurPos();

            idxes[cur] = -1;
            continue;
        }

        if( chs[cur].len == 1 ) //ascii char not support
        {
            idxes[cur] = -1;
            continue;
        }

        idxes[cur] = pPianpang->getGroupIdx(chs[cur].buf,chs[cur].len);
        if( idxes[cur] >= 0 )
        {
            assert( idxes[cur] < pp_cnt.size() );

            if( pp_cnt[idxes[cur]] != INVALID )
                pp_cnt[idxes[cur]]++;
        }

        if( matchCnt(pp_cnt, pp_match_cnt) )//we got one
        {
            int l = 0;
            for( int i = 0; i < firstname_num; i++ )
            {
                l += chs[i].len;
            }
            pos.push_back(pBook->getCurPos() - l);
            len.push_back(l);
        }
    }while(1);

    return true;
}

void CNameFilter::clear()
{
    pBook->clear();
    FN_DELETE(pBook);
    pPianpang->clear();
    FN_DELETE(pPianpang);

    b_init = false;
}

bool CNameFilter::setBook(const std::string& book_fp)
{
    if( !b_init )
        return false;

    if( this->book_filepath == book_fp )
        return true;

    this->book_filepath = book_fp;

    //update the content in the pBook
    return pBook->updateContent(book_filepath);
}

bool CNameFilter::setFirstNameNum(int fn_num)
{
    if( !b_init )
        return false;

    if( fn_num < 1 )
        return false;

    this->firstname_num = fn_num;

    return true;
}

bool CNameFilter::setPianpang(const std::vector<int>& pp_idx)
{
    if( !b_init )
        return false;

    this->pianpang_idx = pp_idx;

    return true;
}

char* CNameFilter::getBookContent()
{
    return pBook->getContent();
}

int CNameFilter::getBookContentLen()
{
    return pBook->getContentLen();
}
