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
#include <string.h>

struct msgbuff //定义消息结构
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
    key = ftok("/home/sunchaohui/CProject/test_c", 'a');
    if (key < 0)
    {
        cout << "ftok error" << endl;
        exit(1);
    }
    qid = msgget(key, IPC_EXCL | 0666); //打开消息队列，注意，不是创建
    if (qid < 0)
    {
        cout << "msgget error" << endl;
        exit(1);
    }
    while (1)
    {
        memset(&buf, 0, sizeof(buf));
        res = msgrcv(qid, &buf, 512, 0, 0);
        if (res < 0)
        {
            cout << "msgrcv error" << endl;
            exit(1);
        }
        else
        {
            cout << "从消息队列里接收到的消息是: " << endl;
            cout << buf.mtype << "  " << res << "  " << buf.mtext << endl;
        }
        if(strcmp(buf.mtext,"del")==0)
        {
            msgctl(qid, IPC_RMID, NULL);   
            exit(0);
        }
    }

    return 0;
}