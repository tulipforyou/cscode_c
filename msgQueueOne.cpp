#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include<string.h>

struct msgbuff  //定义消息结构
{
    long mtype;
    char mtext[512];
};

int main()
{
    int qid;
    key_t key;
    int res;
    struct msgbuff buf;
    key=ftok("/home/sunchaohui/CProject/test_c",'a');
    if(key<0)
    {
        cout<<"ftok error"<<endl;
        exit(1);
    }
    qid=msgget(key,IPC_CREAT|0666);
    if(qid<0)
    {
        cout<<"msgget error"<<endl;
        exit(1);
    }
    while(1)
    {
        cout<<"input the message to msgQueue:  ";
        cin>>buf.mtext;
        if(strcmp(buf.mtext,"exit")==0)break;
        buf.mtype=getpid();
        res=msgsnd(qid,&buf,512,0);
        if(res<0)
        {
            cout<<"msgsnd error"<<endl;
            exit(1);
        }
        else
        {
            cout<<"success!"<<endl;
        }
        
    }

    return 0;
}