#ifndef __SELECTOR_H__
#define __SELECTOR_H__
#include "seqListForHtml.h"
#include "stack.h"
#include "header.h"
#include "tree.h"
typedef struct inArray
{
    int indexs[MAX_TREE_SIZE];
    int n=0;
}inArray;
void class1(tree t, inArray &l, char*s);
void class2(tree t, inArray &l, char*s);
void classChild(tree t, inArray &l, char*s);
void id(tree t, inArray &l, char*s);
void all(tree t, inArray &l, char*s);
void tag1(tree t, inArray &l, char*s);
void tagClass(tree t, inArray &l, char*s);
void tag2(tree t, inArray &l, char*s);
void tagSon(tree t, inArray &l, char*s);
void tagChild(tree t, inArray &l, char*s);
void tagHeel(tree t, inArray &l, char*s);
void tagAfter(tree t, inArray &l, char*s);

void innerText(tree t, inArray &l);
void outerHTML(tree t, inArray &l);
void href(tree t, inArray &l);

void selector(tree t, inArray &l, char* s)
{
    int i=1;
    if(s[0]=='.')
    {
        while(s[i]!='\0')
        {
            if(s[i]=='.')
            {
                if(s[i-1]==' ')
                {
                    classChild(t,l,s);
                }
                else
                {
                    class2(t,l,s);
                }
                break;
            }
            i++;
        }
        if(s[i]=='\0')class1(t,l,s);
    }
    else if(s[0]=='#')
    {
        id(t,l,s);
    }
    else if(s[0]=='*')
    {
        all(t,l,s);
    }
    else
    {
        while(s[i]!='\0')
        {
            if(s[i]=='.')
            {
                tagClass(t,l,s);
                break;
            }
            if(s[i]==',')
            {
                tag2(t,l,s);
                break;
            }
            if(s[i]==' '&&s[i+1]!='>'&&s[i+1]!='+'&&s[i+1]!='~')//，后有‘ ’的情况可以排除，因为先判断，
            {
                tagChild(t,l,s);
                break;
            }
            if(s[i]=='>')
            {
                tagSon(t,l,s);
                break;
            }
            if(s[i]=='+')
            {
                tagHeel(t,l,s);
                break;
            }
            if(s[i]=='~')
            {
                tagAfter(t,l,s);
                break;
            }
            i++;
        }
        if(s[i]=='\0')tag1(t,l,s);
    }
    int j=0;
    while(s[j]!='\0')
    {
        if(s[j-1]==':' && s[j]==':')
        {
            if(s[j+1]=='t')
            {
                innerText(t,l);
                break;
            }
            if(s[j+1]=='h'&&s[j+2]=='t')
            {
                outerHTML(t,l);
                break;
            }
            if(s[j+1]=='h'&&s[j+2]=='r')
            {
                href(t,l);
                break;
            }
        }
        j++;
    }
}
void innerText(tree t, inArray &l)
{
    for(int i=0;i<l.n;i++)
    {
        char* startP=t.nodes[l.indexs[i]].startPtr;
        char* endP=t.nodes[l.indexs[i]].endPtr;
        for(int j=0;j<t.n;j++)
        {
            if(!strcmp(t.nodes[j].tag,"text"))
            {
                if(t.nodes[j].startPtr>startP&&t.nodes[j].endPtr<endP)
                {
                    for(char* k=t.nodes[j].startPtr;k<=t.nodes[j].endPtr;k++)
                    print_char(*k);
                    cout<<endl;
                }
            }
        }
    }
}
void outerHTML(tree t, inArray &l)
{
    for(int i=0;i<l.n;i++)
    {
        char* startP=t.nodes[l.indexs[i]].startPtr;
        char* endP=t.nodes[l.indexs[i]].endPtr;
                    for(char* k=startP;k<=endP;k++)
                    print_char(*k);
                    cout<<endl;
    }  
}
void href(tree t, inArray &l)
{
    for(int i=0;i<l.n;i++)
    {
        char* startP=t.nodes[l.indexs[i]].startPtr;
        char* endP=t.nodes[l.indexs[i]].endPtr;
        char* thishref=0x0;
        getHref(startP,endP,thishref);
        if(thishref==0x0)continue;
        for(char* k=thishref;;k++)
        {
            if((*k)=='\"')break;
            print_char(*k);
        }
        cout<<endl;
    }
}

void class0(tree t, inArray &l, char*s)// 作为classChild的子函数
{
    char ss[30]="";
    strncat(ss,s,strlen(s));
    for(int i=0;i<t.n;i++)
    {
        if(strcmp(t.nodes[i].tag,"text"))
        {
            char* c=0x0;
            getClass(t.nodes[i].startPtr,t.nodes[i].endPtr,c);
            if(hasClass(c,ss))
            {
                    if(t.nodes[i].firstchild!=0x0)
                    {
                        if(c>(t.nodes[t.nodes[i].firstchild->tNum].startPtr))continue;
                    }
                    l.indexs[l.n]=i;
                    l.n++;
            }
        }
    }
}
void class1(tree t, inArray &l, char*s)
{
    char ss[30]="";
    strncat(ss,s+1,strlen(s)-1);
    cout<<"开始执行class1，选择类名为 "<<ss<<" 的元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        if(strcmp(t.nodes[i].tag,"text"))
        {
            char* c=0x0;
            getClass(t.nodes[i].startPtr,t.nodes[i].endPtr,c);
            if(hasClass(c,ss))
            {
                    if(t.nodes[i].firstchild!=0x0)
                    {
                        if(c>(t.nodes[t.nodes[i].firstchild->tNum].startPtr))continue;
                    }
                    l.indexs[l.n]=i;
                    l.n++;
            }
        }
    }
    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
void class2(tree t, inArray &l, char*s)
{
    char ss[50]="";
    strncat(ss,s+1,strlen(s)-1);
    char *p = strtok(ss, ".");
    char s1[30]="";
    char s2[30]="";
    int i = 0;
    while (p != NULL) 
    {
        if (i == 0) {
        strcpy(s1, p);  // Copy first substring to c1
        } 
        else if (i == 1) {
        strcpy(s2, p);  // Copy second substring to c2
        }
        p = strtok(NULL, " ");
        i++;
    }
    cout<<"开始执行class2，选择class属性同时包含 "<<s1<<" 和 "<<s2<<" 的元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        if(strcmp(t.nodes[i].tag,"text"))
        {
            char* c=0x0;
            getClass(t.nodes[i].startPtr,t.nodes[i].endPtr,c);
            if(hasClass(c,s1)&&hasClass(c,s2))
            {
                    if(t.nodes[i].firstchild!=0x0)
                    {
                        if(c>(t.nodes[t.nodes[i].firstchild->tNum].startPtr))continue;
                    }
                    l.indexs[l.n]=i;
                    l.n++;
            }
        }
    }
    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
void classChild(tree t, inArray &l, char*s)
{
    
    char *p = strtok(s, " ");
    char s1[30]="";
    char s2[30]="";
    int i = 0;
    while (p != NULL) 
    {
        if (i == 0) {
        strcpy(s1, p);  // Copy first substring to c1
        } 
        else if (i == 1) {
        strcpy(s2, p);  // Copy second substring to c2
        }
        p = strtok(NULL, " ");
        i++;
    }
    char c1[30]="";
    char c2[30]="";
    strncat(c1,s1+1,strlen(s1)-1);
    strncat(c2,s2+1,strlen(s1)-1);

    cout<<"开始执行classChild，选择类名为 "<<c1<<" 的元素后代中所有类名为 "<<c2<<" 的元素"<<endl;
    class0(t,l,c1);

    inArray l2;
    l2.n=0;
    class0(t,l2,c2);
    inArray l3;
    l3.n=0;
    for(int i=0;i<l.n;i++)
    {
        char* startP=t.nodes[l.indexs[i]].startPtr;
        char* endP=t.nodes[l.indexs[i]].endPtr;
        for(int j=0;j<l2.n;j++)
        {
            if(t.nodes[l2.indexs[j]].startPtr>startP&&t.nodes[l2.indexs[j]].endPtr<endP)
            {
                l3.indexs[l3.n]=l2.indexs[j];
                l3.n++;
            }
        }
    }
    memcpy(&l, &l3, sizeof(inArray));

    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
void id(tree t, inArray &l, char*s)
{
    char ss[30]="";
    strncat(ss,s+1,strlen(s)-1);
    cout<<"开始执行id，选择id为 "<<ss<<" 的元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        if(strcmp(t.nodes[i].tag,"text"))
        {
            char* c=0x0;
            getID(t.nodes[i].startPtr,t.nodes[i].endPtr,c);

            char cc[30]="";
            if(c!=0x0)
            {
                strncat(cc,c,strlen(s)-1);
                if(!strcmp(ss,cc) && (*(c+strlen(s)-1)=='\"'))
                {
                    if(t.nodes[i].firstchild!=0x0)
                    {
                        if(c>(t.nodes[t.nodes[i].firstchild->tNum].startPtr))continue;
                    }
                    l.indexs[l.n]=i;
                    l.n++;
                }
            }
            // cout<<i;
            
        }
    }
        cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
void all(tree t, inArray &l, char*s)
{
    cout<<"开始执行all，选择所有元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        // if(!strcmp(t.nodes[i].tag,ss))
        // {
            l.indexs[l.n]=i;
            l.n++;
        // }
    }
        cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl;
        // <<"在存储中的序号分别为：";
    // for(int i=0;i<l.n;i++)
    // {
    //     cout<<l.indexs[i]<<" 位的 ";
    //     cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    // }
    // cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
void tag1(tree t, inArray &l, char*s)
{
    char ss[30]="";
    strncat(ss,s,strlen(s));
    cout<<"开始执行tag1，选择所有 <"<<ss<<"> 元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        if(!strcmp(t.nodes[i].tag,ss))
        {
            l.indexs[l.n]=i;
            l.n++;
        }
    }
        cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
void tagClass(tree t, inArray &l, char*s)
{
    char ss[30]="";
    strncat(ss,s,strlen(s));
    char *p = strtok(ss, ".");
    char s1[30]="";
    char s2[30]="";
    int i = 0;
    while (p != NULL) 
    {
        if (i == 0) {
        strcpy(s1, p);  // Copy first substring to s1
        } 
        else if (i == 1) {
        strcpy(s2, p);  // Copy second substring to s2
        }
        p = strtok(NULL, " ");
        i++;
    }
    cout<<"开始执行tagClass，选择tag <"<<s1<<"> 的元素中 class="<<s2<<" 的元素"<<endl;

    for(int i=0;i<t.n;i++)
    {
        if(!strcmp(t.nodes[i].tag,s1))
        {
            l.indexs[l.n]=i;
            l.n++;
        }
    }
    inArray l2;
    l2.n=0;
    for(int i=0;i<l.n;i++)
    {
        if(strcmp(t.nodes[l.indexs[i]].tag,"text"))
        {
            char* c=0x0;
            getClass(t.nodes[l.indexs[i]].startPtr,t.nodes[l.indexs[i]].endPtr,c);
            if(hasClass(c,s2))
            {
                    if(t.nodes[l.indexs[i]].firstchild!=0x0)
                    {
                        if(c>(t.nodes[t.nodes[l.indexs[i]].firstchild->tNum].startPtr))continue;
                    }
                    l2.indexs[l2.n]=l.indexs[i];
                    l2.n++;
            }
        }
    }
    memcpy(&l, &l2, sizeof(inArray));

    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
void tag2(tree t, inArray &l, char*s)
{
    
    char ss[30]="";
    strncat(ss,s,strlen(s));
    char *p = strtok(ss, ",");
    char s1[30]="";
    char s2[30]="";
    int i = 0;
    while (p != NULL) 
    {
        if (i == 0) {
        strcpy(s1, p);  // Copy first substring to s1
        } 
        else if (i == 1) {
        strcpy(s2, p);  // Copy second substring to s2
        }
        p = strtok(NULL, " ");
        i++;
    }
    cout<<"开始执行tag2，选择所有 <"<<s1<<"> 和所有 <"<<s2<<"> 元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        if(!strcmp(t.nodes[i].tag,s1)||!strcmp(t.nodes[i].tag,s2))
        {
            l.indexs[l.n]=i;
            l.n++;
        }
    }
    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
void tagChild(tree t, inArray &l, char*s)
{
    char ss[30]="";
    strncat(ss,s,strlen(s));
    char *p = strtok(ss, " ");
    char s1[30]="";
    char s2[30]="";
    int i = 0;
    while (p != NULL) 
    {
        if (i == 0) {
        strcpy(s1, p);  // Copy first substring to s1
        } 
        else if (i == 1) {
        strcpy(s2, p);  // Copy second substring to s2
        }
        p = strtok(NULL, " ");
        i++;
    }
    cout<<"开始执行tagChild，选择 <"<<s1<<"> 元素内所有 <"<<s2<<"> 元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        if(!strcmp(t.nodes[i].tag,s1))
        {
            l.indexs[l.n]=i;
            l.n++;
        }
    }
    inArray l2;
    l2.n=0;
    int n0=l.n;
    // l.n=0;
    for(int i=0;i<n0;i++)
    {
        char* startP=t.nodes[l.indexs[i]].startPtr;
        char* endP=t.nodes[l.indexs[i]].endPtr;
        for(int j=0;j<t.n;j++)
        {
            if(!strcmp(t.nodes[j].tag,s2))
            {
                if(t.nodes[j].startPtr>startP&&t.nodes[j].endPtr<endP)
                {
                    bool found=false;
                    for(int k=0;k<l2.n;k++)
                    {
                        if(l2.indexs[k]==j)found=true;
                    }
                    if(found)continue;
                    l2.indexs[l2.n]=j;
                    l2.n++;
                }
            }
        }
    }
    memcpy(&l, &l2, sizeof(inArray));

    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;

}
void tagSon(tree t, inArray &l, char*s)
{
    char ss[30]="";
    strncat(ss,s,strlen(s));
    char *p = strtok(ss, ">");
    char s1[30]="";
    char s2[30]="";
    int i = 0;
    while (p != NULL) 
    {
        if (i == 0) {
        strcpy(s1, p);  // Copy first substring to s1
        } 
        else if (i == 1) {
        strcpy(s2, p);  // Copy second substring to s2
        }
        p = strtok(NULL, " ");
        i++;
    }
    cout<<"开始执行tagSon，选择父元素是 <"<<s1<<"> 的所有 <"<<s2<<"> 元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        if(!strcmp(t.nodes[i].tag,s1))
        {
            l.indexs[l.n]=i;
            l.n++;
        }
    }
    inArray l2;
    l2.n=0;
    int n0=l.n;
    // l.n=0;
    for(int i=0;i<n0;i++)
    {
        char* startP=t.nodes[l.indexs[i]].startPtr;
        char* endP=t.nodes[l.indexs[i]].endPtr;
        for(int j=0;j<t.n;j++)
        {
            if(!strcmp(t.nodes[j].tag,s2))
            {
                if(t.nodes[j].startPtr>startP&&t.nodes[j].endPtr<endP)
                {
                    cPtr cp = t.nodes[l.indexs[i]].firstchild;
                    if(cp==NULL || cp==0x0)continue;
                    while(1)
                    {
                        if(cp->tNum==j)
                        {
                            l2.indexs[l2.n]=j;
                            l2.n++;
                        }
                        if(cp->next==0x0)break;
                        cp=cp->next;
                    }
                }
            }
        }
    }
    memcpy(&l, &l2, sizeof(inArray));
    // innerText(t,l);
    // href(t,l);
    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}

void tagHeel(tree t, inArray &l, char*s)
{
    char ss[30]="";
    strncat(ss,s,strlen(s));
    char *p = strtok(ss, "+");
    char s1[30]="";
    char s2[30]="";
    int i = 0;
    while (p != NULL) 
    {
        if (i == 0) {
        strcpy(s1, p);  // Copy first substring to s1
        } 
        else if (i == 1) {
        strcpy(s2, p);  // Copy second substring to s2
        }
        p = strtok(NULL, " ");
        i++;
    }
    cout<<"开始执行tagHeel，选择紧跟 <"<<s1<<"> 元素的首个 <"<<s2<<"> 元素"<<endl;

    for(int i=0;i<t.n;i++)
    {
        if(!strcmp(t.nodes[i].tag,s1))
        {
            l.indexs[l.n]=i;
            l.n++;
        }
    }
    inArray l2;
    l2.n=0;
    bool found=false;
    for(int i=0;i<l.n;i++)
    {
        char* startP=t.nodes[l.indexs[i]].startPtr;
        char* endP=t.nodes[l.indexs[i]].endPtr;
        for(int j=0;j<t.n;j++)
        {
            if(!strcmp(t.nodes[j].tag,s2))
            {
                if(t.nodes[j].startPtr>endP)
                {
                    l2.indexs[l2.n]=j;
                    l2.n++;
                    found=true;
                    break;
                }
            }
        }
        if(found)break;
    }
    memcpy(&l, &l2, sizeof(inArray));
    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
    // href(t,l);
}
void tagAfter(tree t, inArray &l, char*s)
{
    char ss[30]="";
    strncat(ss,s,strlen(s));
    char *p = strtok(ss, "~");
    char s1[30]="";
    char s2[30]="";
    int i = 0;
    while (p != NULL) 
    {
        if (i == 0) {
        strcpy(s1, p);  // Copy first substring to s1
        } 
        else if (i == 1) {
        strcpy(s2, p);  // Copy second substring to s2
        }
        p = strtok(NULL, " ");
        i++;
    }
    cout<<"开始执行tagAfter，选择前面有 <"<<s1<<"> 元素的所有 <"<<s2<<"> 元素"<<endl;
    for(int i=0;i<t.n;i++)
    {
        if(!strcmp(t.nodes[i].tag,s1))
        {
            l.indexs[l.n]=i;
            l.n++;
        }
    }
    inArray l2;
    l2.n=0;
    for(int i=0;i<l.n;i++)
    {
        char* startP=t.nodes[l.indexs[i]].startPtr;
        char* endP=t.nodes[l.indexs[i]].endPtr;
        for(int j=0;j<t.n;j++)
        {
            if(!strcmp(t.nodes[j].tag,s2))
            {
                if(t.nodes[j].startPtr>endP)
                {
                    bool found=false;
                    for(int k=0;k<l2.n;k++)
                    {
                        if(l2.indexs[k]==j)found=true;
                    }
                    if(found)continue;
                    l2.indexs[l2.n]=j;
                    l2.n++;
                }
            }
        }
    }
    memcpy(&l, &l2, sizeof(inArray));
    cout<<"满足您要求的元素共 "<<l.n<<" 个。"<<endl<<"在存储中的序号分别为：";
    for(int i=0;i<l.n;i++)
    {
        cout<<l.indexs[i]<<" 位的 ";
        cout<<t.nodes[l.indexs[i]].tag<<" ; ";
    }
    cout<<endl;
    cout<<"请输入你要进行的操作（text,html,href;输入q退出）"<<endl;
    char o[30]="";
    while(strcmp(o,"q"))
    {
        cin>>o;
        {
            if(!strcmp(o,"text"))innerText(t,l);
            if(!strcmp(o,"html"))outerHTML(t,l);
            if(!strcmp(o,"href"))href(t,l);
        }
    }
    return;
}
#endif