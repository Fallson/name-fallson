#ifndef CNAMEFILTER_H
#define CNAMEFILTER_H

#include <string>
#include <vector>

class CBook;
class CPianPang;
class CNameFilter
{
public:
    CNameFilter();
    ~CNameFilter();

    bool init(const std::string& pp_fp);
    bool search(std::vector<int>& pos, std::vector<int>& len);
    void clear();

    bool setBook(const std::string& book_fp);
    bool setFirstNameNum(int fn_num);
    bool setPianpang(const std::vector<int>& pp_idx);

    char* getBookContent();
    int   getBookContentLen();
private:
    bool b_init;

    std::string book_filepath;
    CBook*      pBook;

    int firstname_num;

    std::string pianpang_filepath;
    std::vector<int> pianpang_idx;
    CPianPang*  pPianpang;
};

#endif // CNAMEFILTER_H
