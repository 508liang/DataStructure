#ifndef __TREE_H__
#define __TREE_H__
#include "seqListForHtml.h"
#include "stack.h"
#include "header.h"
#define MAX_TREE_SIZE 3000
typedef struct cNode{
    int tNum=0;
    struct cNode *next=NULL;
}*cPtr;
typedef struct tNode{
    char tag[30]="";
    char* startPtr=NULL;
    char* endPtr=NULL;
    cPtr firstchild=NULL;
}tNode;
typedef struct{
    tNode nodes[MAX_TREE_SIZE];
    int n=0;
    int r=0;
}tree;
bool compare(tNode a, tNode b)
{
    return (a.startPtr<b.startPtr);
}
void buildNodes(SqList l, tree &t)
{
    sqStack s;
    initStack(s);
    for(int i=0;i<l.length;i++)
    {
        char c = l.elem[i];

        if(c=='<')
        {
            i++;
            char cc = l.elem[i];
            if(cc!='/')
            {
                char strL[30]="";
                getTag(l, i, strL);
                if(typeSingle(strL))
                {
                    t.nodes[t.n].startPtr=l.elem+i-1;
                    strcat(t.nodes[t.n].tag,strL);
                    while(l.elem[i]!='>')i++;
                    t.nodes[t.n].endPtr=l.elem+i;
                    t.n++;
                    // i++;
                    continue;
                }
                if(strL[0]=='!'&&strL[1]=='-')
                {
                    while(l.elem[i-1]!='-'||l.elem[i]!='>')i++;
                    // i++;
                    continue;
                }
                Tag tag;
                tag.p = l.elem+i-1; 
                strcat(tag.s,strL);
                push(s, tag);   
                // if(!strcmp(tag.s,"body"))
                // {
                //     cout<<tag.p;
                // }   
                while(l.elem[i]!='>')i++;
                // i++;
            }

            else if(cc=='/')
            {
                i++;
                char strR[30]="";
                getTag(l, i, strR);
                Tag tagR;
                tagR.p = l.elem+i+strlen(strR);//!!!!!!!!
                strcat(tagR.s,strR);

                Tag tagL;
                pop(s, tagL);
                // if(!strcmp(tagL.s,"body"))
                // {
                //     cout<<tagL.p;
                // }   
                if(strcmp(tagL.s,tagR.s)!=0)//不是一对儿，不合法
                {
                    cout<<"left tag ["<<(tagL.s)<<"] at No."<<tagL.p-l.elem<<" char position in html can't match right tag ["<<(tagR.s)<<']'<<" at No."<<i<<" char position in html";
                    return;
                }   
                t.nodes[t.n].startPtr=tagL.p;
                t.nodes[t.n].endPtr=tagR.p;
                strcat(t.nodes[t.n].tag,tagR.s);
                t.n++;

                while(l.elem[i]!='>')i++;
                // i++;
            }
        }
        else if(c!='\n'&&c!=' '&&c!='\t')
        {
            t.nodes[t.n].startPtr=l.elem+i;
            strcat(t.nodes[t.n].tag,"text");


            while(l.elem[i]!='<'||l.elem[i+1]=='j')i++;
            // while(l.elem[i]!='<')i++;
            i--;
            t.nodes[t.n].endPtr=l.elem+i;
            t.n++;
        }
    }
    sort(t.nodes,t.nodes+t.n,compare);
    t.r=0;
    // cout<<t.n<<"   "<<t.nodes[t.r].tag;
    cout<<"totally "<<t.n<<" nodes,"<<" root's tag is "<<t.nodes[t.r].tag<<endl;
}
void buildChilden(SqList l, tree &t)
{
    for(int i=0;i<l.length;i++)
    {
        char c = l.elem[i];
        if(c=='<')
        {
            int start=0;
            int end=0;
            int target=0;
            for(int k=0;k<t.n;k++)
            {
                if(t.nodes[k].startPtr==l.elem+i)
                {
                    start=t.nodes[k].startPtr-l.elem;
                    end=t.nodes[k].endPtr-l.elem;
                    target=k;
                    break;
                }
            }
            for(int j=start;j<end;j++)
            {
                if(l.elem[j]=='<')
                {
                    for(int k=0;k<t.n;k++)
                    {
                        if(t.nodes[k].startPtr==l.elem+j)
                        {
                            if(k==target)
                            {
                                while(l.elem[j]!='>')j++;
                                // j++;
                                break;
                            }
                            // cNode *cp = (cNode*)malloc(sizeof(cNode));
                            cPtr cp = t.nodes[target].firstchild;
                            if(cp==NULL || cp==0x0)
                            {
                                cp = (cNode*)malloc(sizeof(cNode));
                                t.nodes[target].firstchild = cp;
                            }
                            else
                            {
                                while(cp->next!=0x0)
                                {
                                    cp=cp->next;
                                }
                                if(cp->next==0x0)
                            {
                                cp->next = (cNode*)malloc(sizeof(cNode));
                                cp=cp->next;
                            }
                            }
                            // cNode cnode;
                            // cnode.tNum=k;
                            // cnode.next=NULL;
                            if(cp->next==0x0)
                            {
                                cp->next = (cNode*)malloc(sizeof(cNode));
                                cp=cp->next;
                            }
                            cp->tNum=k;
                            cp->next=NULL;
                            j=t.nodes[k].endPtr-l.elem;
                            break;
                        }
                    }
                }
                else
                {
                    for(int k=0;k<t.n;k++)
                    {
                        if(t.nodes[k].startPtr==l.elem+j)
                        {
                            cPtr cp = t.nodes[target].firstchild;
                            if(cp==NULL || cp==0x0)
                            {
                                cp = (cNode*)malloc(sizeof(cNode));
                                t.nodes[target].firstchild = cp;
                            }
                            else
                            {
                                while(cp->next!=0x0)
                                {
                                    cp=cp->next;
                                }
                                if(cp->next==0x0)
                            {
                                cp->next = (cNode*)malloc(sizeof(cNode));
                                cp=cp->next;
                            }
                            }
                            cp->tNum=k;
                            cp->next=NULL;

                            j=t.nodes[k].endPtr-l.elem;
                            break;
                        }
                    }
                }
            }
        }
    }
}
#endif