#ifndef __STACK_H__
#define __STACK_H__
#include "header.h"
#define stack_init_size 100
#define stack_step_size 10
typedef struct
{
    sElemType* base;
    sElemType* top;
    int stacksize;
}sqStack;

void initStack(sqStack &s)
{
    s.base = (sElemType*)malloc(stack_init_size*sizeof(sElemType));
    if(!s.base)
    {
        printf("fail to initialize");
        exit(0);
    }
    s.top = s.base;
    s.stacksize = stack_init_size;
    return;
}
bool stackEmpty(sqStack s)
{
    if(s.base==s.top)return true;
    return false;
}
void push(sqStack &s, sElemType e)
{
    if(s.top-s.base>=s.stacksize)
    {
        s.base = (sElemType*)realloc(s.base, (s.stacksize+stack_step_size)*sizeof(sElemType));
        s.top = s.base + s.stacksize;
        s.stacksize = s.stacksize + stack_step_size;
    }
    *s.top++ = e;//*before++
    return;
}
bool pop(sqStack &s, sElemType &e)
{
    if(s.base==s.top)return false;
    e = *--s.top;
    return true;
}
bool getTop(sqStack s, sElemType &e)
{
    if(s.base==s.top)return false;
    e = *--s.top;//--before*
    return true;
}
void destroyStack(sqStack &s)
{
    free(s.base);
    return;
}
void clearStack(sqStack &s)
{
    s.top = s.base;
    return;
}
int stackLength(sqStack s)
{
    return s.top - s.base;
}
void stackTraverse(sqStack s, void(*visit)(sElemType))
{
    if(s.top==s.base)return;
    for(int i=0;i<s.stacksize;i++)
    {
        visit(s.base[i]);
    }
    return;
}
#endif 