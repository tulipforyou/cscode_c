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
#include "findAlgorithm.h"
#include "sortAlgorthm.h"
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

    /*vector<int> v;
    findAlgorithm<int> fa;
    for (int i = 0; i < 50000; i++)
        v.push_back(i);
    clock_t begin1=clock();
    cout << "二分查找法：" << endl;
    cout << fa.binarySearch(2345, v) << "次比较" << endl;
    clock_t end1=clock();
    cout <<"二分查找用时："<< end1-begin1 << endl;
    cout << "二叉排序树法：" << endl;
    binarySortTree<int> bst;
    bst.CreatebinarySortTree(v, 50000);
    clock_t begin2=clock();
    bst.search(2345);
    clock_t end2=clock();
    cout<<"二叉排序树查找用时:"<<end2-begin2<<endl;*/

    sortAlgorithm<int> sa;
    vector<int> v = {5985, 6, 16, 1, 16, 1, 166, 16, 16, 16, 1, 515, 156, 1, 1, 6161, 161646};
    cout<<"插入排序:"<<endl;
    sa.insertSort(v);
    cout<<"希尔排序:"<<endl;
    sa.shellSort(v);
    cout<<"冒泡排序:"<<endl;
    sa.bubbleSort(v);
    cout<<"快速排序:"<<endl;
    sa.quickSort(v);
    cout<<"选择排序:"<<endl;
    sa.selectSort(v);
    return 0;
}