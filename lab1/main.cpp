#include "header.h"
#include "LinkedList.h"
#include "SeqList.h"
#include "word.h"
int main()
{
    int input_way=-1;
    int m=0;
    SqList l;
    SqList* listL[10];
    /*====================INPUT===================*/
    cout<<"Hey guy! The following is the tokens of input types, please have a look!"<<endl;
    cout<<"1 means: type in string(s)."<<endl<<"2 means: input string(s) from file(s) contained in current folder."<<endl;
    cout<<"Which way do you want to choose?(1 or 2)";
    scanf("%d", &input_way);
    while(input_way!=1 & input_way!=2)
    {
        cout<<"Wrong input! Please input 1 or 2:";
        scanf("%d", &input_way);
    }
    
    if(input_way==1)
    {
        cout<<"Please type in the number of strings you want to input:";
        scanf("%d", &m);
        if(m==1)
        {
            InitSqList(l);
            cout<<"Just type in it!"<<endl;
            inputFromStdin(l);
            cout<<"===Congratulations!!! You have input it! Its 5 words ahead(or its all words if len<5) is:"<<endl;
            for(int i=0;i<5&i<l.length;i++)
            {
                cout<<l.elem[i].w<<" ";
            }
            cout<<endl;
            cout<<"========INPUT FINISHED========"<<endl;
          
        }
        else
        {  
            for(int i=0;i<m;i++)
            {
            SqList *pl =(SqList*) malloc(sizeof(SqList));
            listL[i] = pl;
            InitSqList(*pl);
            cout<<"Please type in the No."<<i+1<<" string:";
            inputFromStdin(*pl);
            
            cout<<listL[i];
            cout<<"===Congratulations! You have input the No."<<i+1<<" string! Its 5 words ahead(or its all words if len<5) is:"<<endl;
            for(int i=0;i<5&i<(*pl).length;i++)
            {
                cout<<(*pl).elem[i].w<<" ";
            }
            cout<<endl;
            }
        cout<<"=====INPUT FINISHED====="<<endl;
        }
    }

    if(input_way==2)
    {
        cout<<"Please type in the number of strings you want to input:";
        scanf("%d", &m);
        if(m==1)
        {
            cout<<"Please type in the file name(eg.""demo.txt""):";
            char name[20];
            scanf("%s",name);
            
            InitSqList(l);
            inputFromFile(l, name);
            cout<<"===Congratulations! You have input it! Its 5 words ahead(or its all words if len<5)is:"<<endl;
            for(int i=0;i<5&i<l.length;i++)
            {
                cout<<l.elem[i].w<<" ";
            }
            cout<<endl;
            cout<<"=====INPUT FINISHED====="<<endl;
        }
        else
        {
            for(int i=0;i<m;i++)
            {
            SqList *pl =(SqList*) malloc(sizeof(SqList));
            InitSqList(*pl);
            listL[i] = pl;
            cout<<"Please type in the No."<<i+1<<" file name(eg.""demo.txt""):";
            char* name;
            scanf("%s",name);
            InitSqList(*pl);
            inputFromFile(*pl, name);
            cout<<"===Congratulations!!! You have input the No."<<i+1<<" string, its 5 words ahead(or its all words if len<5) is:"<<endl;
            for(int i=0;i<5&i<(*pl).length;i++)
            {
                cout<<(*pl).elem[i].w<<" ";
            }
            }
            cout<<endl;
            cout<<"=====INPUT FINISHED====="<<endl;
        }
    }
    /*====================OPERATION===================*/
    int o = 1;
    cout<<"Hey bro, here are the operations you can do, have a look!"<<endl;
    // int end = 1;

    while(o!=10)
    {
        cout<<endl<<"==========================================================================="<<endl<<"1 means: print the words."<<endl<<"2 means: insert one or more words."<<endl<<
       "5 means: judge if the string is palindrome."<<endl<<"6 means: get the number of words in string."<<endl<<
          "3 means: delete one or more words."<<endl<<"4 means: reverse the string."<<endl<<
       "7 means: type in a string and judge if it is contained in the previous string."<<endl<<
        "8 means: count the occurrence times of words."<<endl<<
        "9 means: merge two strings."<<endl<<
        "10 means: destroy the string(s) and EXIT."<<endl<<"==========================================================================="<<endl;
        cout<<"\nJust choose one :)"<<endl;
        scanf("%d", &o);
        int mm = 0;
        if(m!=1)
        {
            cout<<"You have built "<<m<<" strings, please choose the string you want to operate(input an integer in range of [1 to "<<m<<"]):";
            scanf("%d", &mm);
            l = *(listL[mm-1]);
        }
        int p = 0;
        int num = 0;
        if(o==1)
        {
            print(l);
        }
        if(o==2)
        {
            cout<<"the length of string is:"<<len(l)<<endl;
            cout<<"which place do you want to insert in?";
            scanf("%d", &p);

            cout<<"how many words do you want to insert?";
            scanf("%d", &num);
            
            cout<<"please type in the words one by one."<<endl;
            for(int i=0;i<num;i++)
            {
                char add[20];
                scanf("%s", add);
                insertWord(add, l, p);
            }
        }
        if(o==3)
        {
            int p = 0;
            cout<<"the length of string is:"<<len(l)<<endl;
            cout<<"which place of string do you want to delete?";
            scanf("%d", &p);
            
            cout<<"how many words do you want to delete?";
            int num = 0;
            scanf("%d", &num);

            for(int i=0;i<num;i++)
            {
                deleteWord(l, p);
            }
        }
        if(o==4)
        {
            reverse(l);
            cout<<"after reversing, the string turn to:"<<endl;
            print(l);
        }
        if(o==5)
        {
            palindrome(l, compare_word);
        }
        if(o==6)
        {
            printf("%d", len(l));
        }
        if(o==7)
        {
            searchStr(l);
        }
        if(o==8)
        {
            count(l);
        }  
        if(o==9)
        {
            SqList ll;
            if(m==1)
            {
                cout<<"Please input the string to merge:";
                InitSqList(ll);
                inputFromStdin(ll);
                merge(l, ll);
                destroy(ll);
                print(l);
            }
            else
            {
                cout<<"You have built "<<m<<" strings, please choose another string to merge into the former.(input an integer in range of [1 to "<<m<<"]):";
                int mmm=0;
                scanf("%d", &mmm);
                ll = *listL[mmm-1];
                merge(*(listL[mm-1]), ll);
                cout<<"After merging, the former list turn to:\n";
                print(*(listL[mm-1]));
            }
        } 
        if(o==10)
        {
            if(m>1)
            {
                for(int i=0;i<m;i++)
                {
                    destroy(*(listL[i]));
                }
            }
            else
            {
                destroy(l);
            }
        }    
    }
    

}