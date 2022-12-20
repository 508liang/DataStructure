#include "header.h"
#include "stack.h"
#include "seqListForHtml.h"
#include "tree.h"
#include "selector.h"
int main()
{
    SqList L;
    InitSqList(L);
 
    char name[20]="lab3_news.html";
    // scanf("%s",name);
    inputFromFile(L, name, true);

    tree t;
    buildNodes(L,t);
    buildChilden(L,t);


    char s[50]="";
    while (true) 
    {
        cout<<"请输入您的检索语句（输入exit退出）："<<endl;
        cin.getline(s, 50);
        if (strcmp(s, "exit") == 0)
        break;

        inArray l;
        l.n=0;

        selector(t,l,s);

        // 清空缓冲区
        // cin.ignore(numeric_limits<streamsize>::max(),'\n');
        getchar();
    }
    return 0;
}