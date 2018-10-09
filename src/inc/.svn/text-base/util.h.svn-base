#ifndef UTIL_H
#define UTIL_H

/*******************************************************************/
#include <stdio.h>
/*******************************************************************/
#define FN_OK 0
#define FN_ERR 1
#define FN_FREE(p)       { if(p) { free(p); (p)=NULL; } }
#define FN_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define FN_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
/*******************************************************************/
struct utf8Char
{
    char buf[6];
    int len;
};

/*******************************************************************/
int filesize(FILE* fp);

bool checkUtf8Char(char* content, int len);

int utf8CharNum(char* content, int len);

#endif // UTIL_H
