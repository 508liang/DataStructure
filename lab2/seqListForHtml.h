#ifndef __SEQLISTFORHTML_H__
#define __SEQLISTFORHTML_H__
#include "header.h"

typedef struct SqList{
        ElemType* elem;
        int length;
        int listsize;
    }SqList;

#define list_init_size 8000
#define list_step_size 3000
#define maxInput 50000

void InitSqList(SqList &L);
bool InsertSqList(SqList &L, ElemType e, int i);
void inputFromFile(SqList &l, char *file);



void InitSqList(SqList &L)
{
    L.elem = (ElemType*)malloc(list_init_size*sizeof(ElemType));//
    // L.elem = new(ElemType);
    if(!L.elem)
    {
        printf("fail to initialize");
        exit(0);
    }
    L.length = 0;
    L.listsize = list_init_size;
} 

bool InsertSqList(SqList &L, ElemType e, int i)
{
    if(i<1||i>L.length+1)return false;
    if(L.length>=L.listsize)
    {
        ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize+list_step_size)*sizeof(ElemType));
        if(!newbase)exit(0);
        L.elem = newbase;
        L.listsize += list_step_size;
    }
    ElemType* p;
    ElemType* q = &(L.elem[i-1]);
    for(p=&L.elem[L.length-1];p>=q;p--)
    {
        *(p+1) = *p;
    }
    *q = e;
    L.length++;
    return true;
}

void inputFromFile(SqList &l, char *file, bool first)
{
    FILE *fp;
    fp = fopen(file , "r");
    // char s[maxInput] = "";
    if(fp == NULL) {
      perror("Opening fails");
      exit(0);
   }
    char ch;
    while(1)
    {
        
        ch = fgetc(fp);
        if(ch == EOF)break;
        InsertSqList(l, ch, l.length+1);
    }
    fclose(fp);
    if(first)
    cout<<"Load successfully."<<endl;
    return;
}

void SqListTraverse(SqList L, void(*visit)(ElemType))
{
    for(int i=0;i<L.length;i++)
    {
        visit(L.elem[i]);
    }
    return;
}

void print_char(ElemType c)
{
    cout<<c;
    return;
}
void print(SqList L)
{
    SqListTraverse(L, print_char);
    return;
}


void DestroySqList(SqList &L)
{   
    free(L.elem);
    L.length = 0;
}
void ClearSqList(SqList &L)
{
    L.length = 0;
}
int LengthSqList(SqList L)
{
    return L.length;
}
bool GetElemSqList(SqList L, int i, ElemType &e)
{
    if(i<1||i>L.length)
    {
        printf("over index");
        return false;
    }
    e = L.elem[i-1];
    return true;
}
int LocateElemSqList(SqList L, ElemType e, bool(*comepare)(ElemType, ElemType))
{
    ElemType* p = L.elem;
    int i = 1;
    while(i<=L.length)
    {
        if(comepare(e, *p))return i;
        i++;
        p++;
    }
    return -1;
}

bool DeleteSqList(SqList &L, int i, ElemType &e)
{
    if(i<1||i>L.length+1)return false;
    ElemType* p = &(L.elem[i-1]);
    ElemType* q = &(L.elem[L.length-1]);
    e = *p;
    for(;p<q;p++)
    {
        *p = *(p+1);
    }
    L.length--;
    return true;
}
bool PriorElemSqList(SqList L, int i, ElemType &pre_e)
{
    if(i<=1||i>L.length+1)return false;
    pre_e = L.elem[i-2];
    return true;
}
bool NextElemSqList(SqList L, int i, ElemType &next_e)
{
    if(i<1||i>=L.length)return false;
    next_e = L.elem[i];
    return true;
}


#endif