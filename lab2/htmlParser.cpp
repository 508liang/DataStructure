#include "header.h"
#include "stack.h"
#include "seqListForHtml.h"
//*********************************************************************************
// //判断tag是不是单标签                                                   
bool typeSingle(char* s);              
//匹配到<和字母一起出现 字母位作为numStart 在这个函数中判断tag究竟是什么
bool getTag(SqList l, int numStart, char* str);

// //检验HTML代码的合法性
bool CheckHTML(SqList l);

//输出匹配段全部html文本
void printH(SqList l, Tag tag);
void outHTML(SqList l);

//输出匹配段中所有text
void printT(SqList l, Tag tag);
void text(SqList l);
//********************************************************************************
//token matching function
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
    (!strcmp(s, "keygen")))return true;
    
    return false;
}
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


bool CheckHTML(SqList l)    //input输入好的l
{
    sqStack s;
    initStack(s);
    for(int i=0;i<l.length;i++)
    {
        char c = l.elem[i];
        if(c=='<')
        {
            i++;
            char cc = l.elem[i];    //<的下一个字符

            //是左标签或字母开头的单标签
            // if(cc>='a'&&cc<='z')
            if(cc!='/')
            {
                char strL[30]="";
                getTag(l, i, strL);
                if(typeSingle(strL))continue;
                if(strL[0]=='!')continue;  //单标签或者不在我们考虑范围内的tag，continue即可
                Tag tag;
                tag.p = l.elem+i-1; //p是<对应位置
                strcat(tag.s,strL);
                push(s, tag);   //需要在未来判断是否有相对应的右标签，push进stack中
            }
            //是右标签
            else if(cc=='/')
            {
                i++;
                char strR[30]="";
                getTag(l, i, strR);
                Tag tagR;
                tagR.p = l.elem+i-1;
                strcat(tagR.s,strR);

                Tag tagL;
                pop(s, tagL);   //每遇到一个右标签就pop出stack中的一个左标签
                if(strcmp(tagL.s,tagR.s)!=0)//不是一对儿，不合法
                {
                    cout<<"left tag ["<<(tagL.s)<<"] at No."<<tagL.p-l.elem<<" char position in html can't match right tag ["<<(tagR.s)<<']'<<" at No."<<i<<" char position in html";
                    return false;
                }   
            }
        }
        
    }
    //一开始可能多出些左标签，右标签则少些，上述不是一对儿的判断中无法判断此种情况违法，另要判断一下
    if(!stackEmpty(s))return false;

    printf("Html document is legal.\n");
    return true;
}

void printH(SqList l, Tag tag)  //match好了path,tag记录最后一个str及其位置
{
    for(int i=(tag.p-l.elem);i<l.length;i++)
    {
        char c = l.elem[i];
        if(c=='<')
        {
            i++;
            char cc = l.elem[i];    //<的下一个字符
            if(cc=='/')
            {
                i++;
                char strR[30]="";
                getTag(l, i, strR);
                Tag tagR;
                int len=0;
                for(int q=0;;q++)
                {
                    if(strR[q]=='\0')break;
                    len++;
                }
                tagR.p = l.elem+i-1;
                strcat(tagR.s,strR);
                if(strcmp(tag.s,tagR.s)==0)//是一对儿
                {
                    for(int p=tag.p-l.elem;p<=i+len;p++)
                    {
                        cout<<l.elem[p];
                    }
                    return;
                }   
            }
        }
        
    }
   return;
}

// 读一个path，输出其最后一个tag内的所有html代码文本
void outHTML(SqList l)
{
    char path[77];
    scanf("%s", path);
    // bool pathLock = false;  //我们需要完全匹配，不多不少；stack维护过程中，存在正在等待中间掺入的无关tag pairs跳出的时候，
    //                         //这时即使匹配到path的下一个tag也不能要
    char pathStrs[30][30];
    int pathLen = 0;
    for(int i=0;;i++)
    {
        if(path[i]=='\0')break;
        if(path[i]=='/')
        {
            char p[7]="";  //临时记录path中的tag
            for(int j=i+1;;j++)
            {
                if(path[j]=='/'||path[j]=='\0')break;
                strncat(p, path+j, 1);
            }
            strcpy(pathStrs[pathLen],p);
            pathLen++;   //记录
        }
    }

    Tag printStart;
    Tag printEnd;

    int cur=0; //记录匹配到了path中第几个str了
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
                // if(pathLock)continue;
                char strL[30]="";
                getTag(l, i, strL);
                if(typeSingle(strL))continue;
                if(strL[0]=='!')continue;  //单标签或者不在我们考虑范围内的tag，continue即可
                Tag tag;
                tag.p = l.elem+i-1; //p是<对应位置
                strcat(tag.s,strL);
                push(s, tag);   //需要在未来判断是否有相对应的右标签，push进stack中
                if(strcmp(tag.s,pathStrs[cur])==0)
                {
                    // bool sub=false;
                    
                    if(cur==pathLen-1)   //达到最后啦 并且之前没有掺入别的
                    {
                        printStart=tag;   //这个tag可以哦,把它前面的<的地址记录给printStart
                        printH(l, printStart);
                        printf("\n");
                        // cur--;  //还要继续尝试 前面pathLen-1位已经匹配上了，卡死了
                        // sub=true;
                    }
                    // if(!sub)
                    cur++;
                    
                    
                    
                }
            }

            //是右标签
            else if(cc=='/')
            {
                i++;
                char strR[30]="";
                getTag(l, i, strR);
                Tag tagR;
                tagR.p = l.elem+i-1;
                strcat(tagR.s,strR);

                Tag tagL;
                pop(s, tagL);   //每遇到一个右标签就pop出stack中的一个左标签
                if(strcmp(strR,pathStrs[cur-1])==0)
                cur--;
            }
        }
    }
    return;

}


void printT(SqList l, Tag tag)  //match好了path,tag记录最后一个str及其位置
{
    for(int i=(tag.p-l.elem);i<l.length;i++)
    {
        char c = l.elem[i];
        if(c=='<')
        {
            i++;
            char cc = l.elem[i];    //<的下一个字符
            if(cc=='/')
            {
                i++;
                char strR[30]="";
                getTag(l, i, strR);
                Tag tagR;
                int len=0;
                for(int q=0;;q++)
                {
                    if(strR[q]=='\0')break;
                    len++;
                }
                tagR.p = l.elem+i-1;
                strcat(tagR.s,strR);
                if(strcmp(tag.s,tagR.s)==0)//是一对儿
                {
                    bool lock=false;
                    for(int p=tag.p-l.elem;p<=i+len;p++)
                    {
                        char c = l.elem[p];
                        if(c=='<')
                        {
                        lock=true;
                        }
                        
                        if(!lock)
                        {
                        char cafter = '0';
                        char cbefore='0';
                        if(c=='\n'||c=='\t')
                        {
                            if(p>0)cbefore=l.elem[p-1];
                            if(p<l.length-1)cafter=l.elem[p+1];
                            bool good=false;
                            // if((cbefore>='a'&&cbefore<='z')||(cbefore>='A'&&cbefore<='Z')||(cafter>='a'&&cafter<='z')||(cafter>='A'&&cafter<='Z')
                            //||cbefore=='{' ||cafter=='{'||cbefore=='}'||cafter=='}'||cbefore=='.'||cafter=='.'||cbefore=='!'||cbefore==';')
                            // good=true;
                            // if((cbefore=='\n'||cafter=='\n')||(cbefore=='\t'||cafter=='\t')||(cafter=='<'&&cbefore=='>')||
                            // (cafter=='<'&&cbefore==' ')||(cafter=='<'&&cbefore=='\t')
                            // ||(cafter=='\t'&&cbefore=='>')&&!good// )
                            {
                                continue;
                            } 
                        }
                        // if(c==' '&&(cafter=='0'&&cbefore=='0'))continue;
                        cout<<c;
                        }
                        if(c=='>')lock=false;
                    }
                    cout<<endl;
                    return;
                }   
            }
        }
        
    }
   return;
}
void text(SqList l)
{
    char path[77];
    scanf("%s", path);
    // bool pathLock = false;  //我们需要完全匹配，不多不少；stack维护过程中，存在正在等待中间掺入的无关tag pairs跳出的时候，
    //                         //这时即使匹配到path的下一个tag也不能要
    char pathStrs[30][30];
    int pathLen = 0;
    for(int i=0;;i++)
    {
        if(path[i]=='\0')break;
        if(path[i]=='/')
        {
            char p[7]="";  //临时记录path中的tag
            for(int j=i+1;;j++)
            {
                if(path[j]=='/'||path[j]=='\0')break;
                strncat(p, path+j, 1);
            }
            strcpy(pathStrs[pathLen],p);
            pathLen++;   //记录
        }
    }

    Tag printStart;
    Tag printEnd;

    int cur=0; //记录匹配到了path中第几个str了
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
                // if(pathLock)continue;
                char strL[30]="";
                getTag(l, i, strL);
                if(typeSingle(strL))continue;
                if(strL[0]=='!')continue;  //单标签或者不在我们考虑范围内的tag，continue即可
                Tag tag;
                tag.p = l.elem+i-1; //p是<对应位置
                strcat(tag.s,strL);
                push(s, tag);   //需要在未来判断是否有相对应的右标签，push进stack中
                if(strcmp(tag.s,pathStrs[cur])==0)
                {
                    // bool sub=false;
                    
                    if(cur==pathLen-1)   //达到最后啦 并且之前没有掺入别的
                    {
                        printStart=tag;   //这个tag可以哦,把它前面的<的地址记录给printStart
                        printT(l, printStart);
                        // printf("\n");
                        // cur--;  //还要继续尝试 前面pathLen-1位已经匹配上了，卡死了
                        // sub=true;
                    }
                    // if(!sub)
                    cur++;
                }
            }

            //是右标签
            else if(cc=='/')
            {
                i++;
                char strR[30]="";
                getTag(l, i, strR);
                Tag tagR;
                tagR.p = l.elem+i-1;
                strcat(tagR.s,strR);

                Tag tagL;
                pop(s, tagL);   //每遇到一个右标签就pop出stack中的一个左标签
                if(strcmp(strR,pathStrs[cur-1])==0)cur--;
            }
        }
    }
    return;

}

int main()
{
    SqList L;
    InitSqList(L);
 
    char name[20]="";
    scanf("%s",name);
    inputFromFile(L, name, true);
//    print(L);
    char o[10]="";
    while(strcmp(o,"Exit"))
    {
    InitSqList(L);
    inputFromFile(L, name,false);
    scanf("%s",o);
    if(!strcmp(o,"OutHTML"))outHTML(L);
    if(!strcmp(o,"CheckHTML"))CheckHTML(L);
    if(!strcmp(o,"Text"))text(L);
    }
    // text(L);
    return 0;
}