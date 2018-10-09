#include "photoframe.h"
#include <QtGui/QApplication>
#include <stdio.h>
#include "cnamefilter.h"

QApplication *g_app = NULL;

#define CONSOLE
//#undef  CONSOLE

void usage(char* cmd)
{
    printf("*****************************************************\n");
    printf("**        Copyright by Fallson                     **\n");
    printf("**             Written by Fallson                  **\n");
    printf("*****************************************************\n");

    printf("print the name\n");
    printf("%s pianpang_file book_file firstname_num [pianpang pianpang pianpang...]\n", cmd);
    printf("\n");
}

static void handleOverlap(const std::vector<int>& pos, const std::vector<int>& len,
                          std::vector<int>& new_pos, std::vector<int>& new_len)
{
    if( pos.size() < 2 )
    {
        new_pos = pos;
        new_len = len;
        return;
    }

    new_pos.clear();
    new_len.clear();
    new_pos.push_back(pos[0]);
    new_len.push_back(len[0]);
    int j = 0;
    for( int i = 1; i < pos.size(); i++)
    {
        int end = new_pos[j] + new_len[j];
        if( end >= pos[i] )
        {
            int d = len[i] - (end - pos[i]);
            if( d > 0 )
                new_len[j] += d;
        }
        else
        {
            new_pos.push_back(pos[i]);
            new_len.push_back(len[i]);
            j++;
        }
    }
}

int main(int argc, char *argv[])
{
#ifdef CONSOLE
    if( argc < 5 )
    {
        usage(argv[0]);
        return 1;
    }

    CNameFilter nf;
    if( !nf.init(argv[1]) )
    {
        printf("CNameFilter init fail\n");
        return 1;
    }

    if( !nf.setBook(argv[2]) )
    {
        printf("CNameFilter setBook fail\n");
        return 1;
    }

    if( !nf.setFirstNameNum(atoi(argv[3])) )
    {
        printf("CNameFilter setFirstNameNum fail\n");
        return 1;
    }

    std::vector<int> pp_idx;
    for( int i = 0; i < atoi(argv[3]); i++ )
        pp_idx.push_back(atoi(argv[i+4]));

    if( !nf.setPianpang(pp_idx) )
    {
        printf("CNameFilter setPianpang fail\n");
        return 1;
    }

    std::vector<int> poses;
    std::vector<int> new_poses;
    std::vector<int> lenes;
    std::vector<int> new_lenes;
    if( !nf.search(poses, lenes) )
    {
        printf("CNameFilter search fail\n");
        return 1;
    }
    else
    {
        printf("Searched poses size is: %d\n", poses.size());
    }
    handleOverlap(poses, lenes, new_poses, new_lenes);


    FILE* fp = fopen("testresult.htm", "w");
    if( fp == NULL )
    {
        printf("fopen file [%s] fail\n", "testresult.htm");
        return 1;
    }

    fprintf(fp, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");

    char* text = nf.getBookContent();
    int   len  = nf.getBookContentLen();
    int pos = 0;
    for( int i = 0; i < new_poses.size(); i++ )
    {
        if( new_poses[i] >= pos )
        {
            fwrite(text + pos, 1, new_poses[i] - pos, fp);
            pos = new_poses[i];
            fprintf(fp, "<font color=red>");
            fwrite(text + pos, 1, new_lenes[i], fp);
            pos = pos + new_lenes[i];
            fprintf(fp, "</font>");
        }
    }
    fwrite(text + pos, 1, len - pos, fp);
    fprintf(fp, "\n");
    fclose(fp);

    nf.clear();

    return 0;

#else

    QApplication a(argc, argv);
    g_app = &a;

    PhotoFrame w;
    w.OnNewProj();

    w.show();
    return a.exec();

#endif
}
