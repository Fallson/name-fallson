#ifndef CBOOK_H
#define CBOOK_H

#include <string>
#include "util.h"

class CBook
{
public:
    CBook();
    ~CBook();

    bool init();
    bool updateContent(const std::string& filepath);
    void clear();

    bool getNextUtf8Char(utf8Char& ch);

    int  getCurPos(){ return cur_pos; }
    char* getContent(){ return content; }
    int   getContentLen(){ return content_len; }
private:
    bool b_init;

    char* content;
    int   content_len;
    int   cur_pos;
};

#endif // CBOOK_H
