#ifndef __LINKERLIST_H__
#define __LINKERLIST_H__
#include "header.h"
typedef struct LNode{
        ElemType data;
        struct LNode* next;
    }LNode, *LinkedList;
void InitLinkedList(LinkedList &L)
{
    L = (LinkedList)malloc(sizeof(LNode));
    L->next = NULL;
}
void DestroyLinkedList(LinkedList &L)
{   
    LinkedList p;
    while (L->next)
    {
    p = L->next;
    L->next = p->next;
    free(p);
    }
}
void ClearLinkedList(LinkedList &L)
{
    L->next = NULL;
}
bool InsertLinkedList(LinkedList &L, ElemType e, int i)
{
    LinkedList p = L;
    int j = 0;
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i-1)return false;
    LNode* s;
    s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}
bool DeleteLinkedList(LinkedList &L, int i, ElemType &e)
{
    LinkedList p = L;
    int j = 0;
    while(p&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i-1)return false;
    LNode* q = p->next;
    LNode* temp = q->next;
    e = q->data;
    free(q);
    p->next = temp;
    return true;
}
int LengthLinkedList(LinkedList L)
{
    int length = 0;
    while(L->next)
    {
        length++;
    }
    return length;
}
bool GetElemLinkedList(LinkedList L, int i, ElemType &e)
{
    LinkedList p = L;
    int j = 0;
    while(p&&j<i)
    {
        p=p->next;//p所指的是第j个节点
        j++;
    }
    if(!p||j>i)
    {
        // printf("索引越界");
        return false;
    }
    e = p->data;
    return true;
}
int LocateElemLinkedList(LinkedList L, ElemType e, bool(*comepare)(ElemType, ElemType))
{
    LinkedList p = L;
    int i = 0;
    while(p->next)
    {
        if(comepare(e, p->data))return i;
        i++;
        p=p->next;
    }
    return -1;
}
bool PriorElemLinkedList(LinkedList L, int i, ElemType &pre_e)
{
    LinkedList p = L;
    int j = 0;
    while(p&&j<i-1)
    {
        p=p->next;//p所指的是第j个节点
        j++;
    }
    if(!p||j>i||i==1)
    {
        // printf("索引越界");
        return false;
    }
    pre_e = p->data;
    return true;
}
bool NextElemLinkedList(LinkedList L, int i, ElemType &next_e)
{
    LinkedList p = L;
    int j = 0;
    while(p&&j<i+1)
    {
        p=p->next;//p所指的是第j个节点
        j++;
    }
    if(!p||j>i||i==1)
    {
        // printf("索引越界");
        return false;
    }
    next_e = p->data;
    return true;
}
#endif 