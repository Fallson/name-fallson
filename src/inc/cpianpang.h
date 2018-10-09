#ifndef CPIANPANG_H
#define CPIANPANG_H

#include <string>
#include <vector>
#include "cmeKeyword.h"
#include "cmeKeywordMatch.h"

class CPianPang
{
public:
    CPianPang();
    ~CPianPang();

    bool init(const std::string& filepath);
    void clear();

    int getGroupIdx(char* text, int len); //return -1 if not found
    int getGroupNum(){ return boundary.size(); }

private:
    bool loadkeywords(const char* filepath);

private:
    bool b_init;

    DLPKeywordPara* insen_para;
    DLPKeywordPara* sen_para;

    DGateKeyword* keywords;
    int num;

    std::vector<int> boundary;//store the bound for each pianpang group, eg. boundary[0]=15, means 0-14 is in idx0 and so on
};

#endif // CPIANPANG_H
