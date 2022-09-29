#include "header.h"
#include "SeqList.h"

void constructL(char* s, SqList &l)
{
    word w;
    for(int i =0; s[i]!='\0'; i++)
    {
        if(s[i]=='.' || s[i]==',' || s[i]==' ' || s[i]=='\n')
        {
            if(i!=0 & s[i-1]!='.' & s[i-1]!=',' & s[i-1]!=' ')
            {
                InsertSqList(l,w,l.length+1);
                w.w[0]='\0';
            }
            
        }
        else
        {
            strncat(w.w, s+i, 1);
        }
    }
}
void inputFromStdin(SqList &l)
{
    char s[maxInput] = "";  
    // fgets(s, maxInput, stdin);
    // if(fgets(s, maxInput, stdin)==NULL)
    //     getchar();

    if(*fgets(s, maxInput, stdin)=='\n')
    {
        fgets(s, maxInput, stdin);
    }
    constructL(s, l);
    return ;
}
void inputFromFile(SqList &l, char *file)
{
    FILE *fp;
    fp = fopen(file , "r");
    char s[maxInput] = "";
    if(fp == NULL) {
      perror("Opening fails");
      return;
   }
    fgets(s, maxInput, fp);
    // getchar();
    fclose(fp);
    constructL(s, l);
    return;
}

void print_word(ElemType word)
{
    cout<<word.w<<' ';
    return;
}
void print(SqList L)
{
    SqListTraverse(L, print_word);
    return;
}

void insertWord(char* add, SqList &l, int i)
{
    word w;
    strcat(w.w, add);
    InsertSqList(l, w, i);
    return;
}
// void inserMulWord(char* add, SqList &l, int i, int n)
// {
//     for(int j=0;j<n;j++)
//     {
//         insertWord(add, l, n);
//     }
//     return;
// }

ElemType deleteWord(SqList &l, int i)
{
    word w;
    DeleteSqList(l, i, w);
    return w;
}

// void deleteMulWord(SqList &l, int i, int n)
// {
//     for(int j=0;j<n;j++)
//     {
//         deleteWord(l, i);
//     }
//     return;
// }

bool compare_word(word a, word b)
{
    if(!strcmp(a.w, b.w))
    {
        return true;
    }
    return false;
}
void reverse(SqList &L)
{
    int len = L.length;
    for(int i=0;i<len/2;i++)
    {
        ElemType temp = L.elem[i];
        L.elem[i] = L.elem[len-1-i];
        L.elem[len-1-i] = temp;
    }
    return;
}

bool palindrome(SqList L,bool(*comepare)(ElemType, ElemType))
{
    int len = L.length;
    for(int i=0;i<len/2;i++)
    {
        if(!comepare(L.elem[i], L.elem[len-1-i]))
        {
            printf("String isn't palindrome.\n");
            return false;
        }
    }
    printf("String is palindrome.\n");
    return true;
}

void destroy(SqList &L)
{   
    free(L.elem);
    L.length = 0;
}

int len(SqList L)
{
    return L.length;
}
bool searchStr(SqList L)
{
    SqList str;
    InitSqList(str);
    printf("please input the string you want to search:\n");
    inputFromStdin(str);
    // print(str);
    int str_l = str.length;
    bool done = true;
    for(int i=0;i<=L.length-str_l;i++)
    {
        done = true;
        if(i==str_l)done = false;
        for(int j=i;j<str_l+i;j++)
        {
            
            if(!compare_word(L.elem[j], str.elem[j-i]))
            {
                done = false;
                break;
            }
            
        }
        if(done)
            {
                destroy(str);
                printf("String exists!\n");
                return true;
            }
    }
    destroy(str);
    printf("String doesn't exist!\n");
    return false;
}

void count(SqList L)
{
    int count[L.length]={0};
    for(int i=0;i<L.length;i++)
    {
        int exist = 0;
        for(int j=0;j<i;j++)
        {
           
            if(compare_word(L.elem[i],L.elem[j]))
            {
                exist = 1;
                count[j]+=1;
                break;
            }
        }
        if(exist==0)
        {
        count[i]=1;
        }
        
    }
    printf("counting result:\n");
    for(int i=0;i<L.length;i++)
    {
        if(count[i])
        {
            printf("%-15s%2d\n",L.elem[i].w,count[i]);
        }
    }
    return;
}

void merge(SqList &l, SqList g)
{
    for(int i=0;i<g.length;i++)
    {
        insertWord(g.elem[i].w, l, l.length+1);
    }
    return;
}
