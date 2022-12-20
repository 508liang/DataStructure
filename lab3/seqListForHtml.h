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
bool getTag(SqList l, int numStart, char* str);
bool typeSingle(char* s);
void InitSqList(SqList &L);
bool InsertSqList(SqList &L, ElemType e, int i);
void inputFromFile(SqList &l, char *file);

//匹配到<和字母一起出现 字母位作为numStart 在这个函数中判断tag究竟是什么
bool getTag(SqList l, int numStart, char* str)
{
    char s[10]="";
    for(int i=numStart;i<l.length&&l.elem[i]!='>'&&l.elem[i]!=' ';i++)  //思路是把>或者' '之前的都连接到一个字符串中 
    {
        strncat(s, l.elem+i, 1);
    }
    strcat(str, s);
    return true;
}
bool getClass(char* startPtr, char* endPtr, char* &str)
{
    char s[10]="";
    for(char* p=startPtr;p<endPtr;p++)  
    {
        if(*p=='c')
        {
            if(*(p+1)=='l')
            {
                if(*(p+2)=='a')
                {
                    if(*(p+3)=='s')
                    {
                        if(*(p+4)=='s')
                        {
                            if(*(p+5)=='=')
                            {
                                // for(int k=p+7-l.elem;k < l.length &&l.elem[k]!='\"';k++)
                                // {
                                //     // strncat(s, l.elem+k,1);
                                //     s[strlen(s)]=l.elem[k];
                                //     s[strlen(s)+1]='\0';
                                    // q+=1;
                                // }
                                if(p+7-startPtr>100)return false;
                                str=p+7;
                                return true;
                            }

                        }
                    }
                }
            }
        }
    }
    // strcat(str, s);
    return true;
}
bool hasClass(char* str, const char* subStr)
{
    // 检查 class 属性值是否包含指定的字符串
    if(str==0x0)return false;
    while (*str != '\0' && *str != '\"') 
    {
        // 检查当前的字符是否为空格
        if (*str == ' ') 
        {
            str++;
        }
        // 检查下一个非空格字符是否匹配指定的字符串的第一个字符
        if (*str == *subStr) 
        {
            
            bool found = true;// 如果匹配到了第一个字符，检查剩下的字符是否都匹配
            if(*(str-1)!='"'&&*(str-1)!=' ')
            {
                found = false;
            }
            int i = 1;
            for (i; subStr[i] != '\0'; i++) 
            {
                if (str[i] != subStr[i]) 
                {
                    found = false;
                    break;
                }
            }
            if(subStr[i] == '\0')
            {
                if(str[i]!='"'&&str[i]!=' ')
                {
                    found = false;
                }
            }
            if (found) 
            {
                return true;// 如果所有字符都匹配，返回 true
            }
        }
        str++;
    }
    return false;// 如果没有找到匹配的字符串，返回 false
}

bool getID(char* startPtr, char* endPtr, char* &str)
{
    char s[10]="";
    for(char* p=startPtr;p<endPtr;p++)  
    {
        if(*p=='i')
        {
            if(*(p+1)=='d')
            {
                if(*(p+2)=='=')
                {
                    // for(int k=p+7-l.elem;k < l.length &&l.elem[k]!='\"';k++)
                    // {
                    //     // strncat(s, l.elem+k,1);
                    //     s[strlen(s)]=l.elem[k];
                    //     s[strlen(s)+1]='\0';
                        // q+=1;
                    // }
                    if(p+4-startPtr>100)return false;
                    str=p+4;
                    return true;
                }

            }
        }
    }
    // strcat(str, s);
    return true;
}
bool getHref(char* startPtr, char* endPtr, char* &str)
{
    char s[10]="";
    for(char* p=startPtr;p<endPtr;p++)  
    {
        if(*p=='h')
        {
            if(*(p+1)=='r')
            {
                if(*(p+2)=='e')
                {
                    if(*(p+3)=='f')
                    {
                        if(*(p+4)=='=')
                        {
                            // if(*(p+5)=='=')
                            // {
                                // for(int k=p+7-l.elem;k < l.length &&l.elem[k]!='\"';k++)
                                // {
                                //     // strncat(s, l.elem+k,1);
                                //     s[strlen(s)]=l.elem[k];
                                //     s[strlen(s)+1]='\0';
                                    // q+=1;
                                // }
                                if(p+6-startPtr>100)return false;
                                str=p+6;
                                return true;
                            // }

                        }
                    }
                }
            }
        }
    }
    // strcat(str, s);
    return true;
}
bool typeSingle(char* s)
{
    if(!strcmp(s, "br")||
    (!strcmp(s, "hr"))||
    (!strcmp(s, "area"))||
    (!strcmp(s, "base"))||
    (!strcmp(s, "img"))||
    (!strcmp(s, "input"))||
    (!strcmp(s, "link"))||
    (!strcmp(s, "meta"))||
    (!strcmp(s, "col"))||
    (!strcmp(s, "frame"))||
    (!strcmp(s, "embed"))||
    (!strcmp(s, "keygen"))||
    (!strcmp(s, "!DOCTYPE")))return true;
    return false;
}
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