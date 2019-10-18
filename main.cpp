#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include "file.h"
using namespace std;
#define SIZE 64
int main()
{
    time_t tim;
    time(&tim);
    cout << "当前时间为： " << ctime(&tim);
    cout << "当前用户为： " << getlogin() << endl;
    /*struct passwd * user;
    user=getpwent();
    while(user!=NULL)
    {
        cout<<user->pw_name<<" "<<user->pw_passwd<<endl;
        user=getpwent();
    }
    endpwent();*/
    /*char *p;
    p=getenv("SHELL");//获取环境变量
    if(p==NULL)
    {
        cout<<"error"<<endl;
        exit(1);
    }
    else
    {
        cout<<p<<endl;
    }
    
    vector<int> v;
    for (int i = 0; i < 5; i++)
        v.push_back(i);
    cout << v.size() << endl;
    for (vector<int>::iterator i = v.begin(); i != v.end(); i++)
        cout << *i << " ";
    cout << endl;
    cout << abs(-56) << endl;
    char s[SIZE]="sch";
    char s2[SIZE]="wbq";
    strcat(s,s2);  //字符串连接函数
    cout<<s<<endl;
    char str[SIZE]="sch love wbq";
    char *p1;
    p1=strtok(str," ");//字符串分割函数
    while(p1!=NULL)
    {
        cout<<p1<<endl;
        p1=strtok(NULL," ");
    }
    cout<<str<<endl;*/
    
    
    
    return 0;
}