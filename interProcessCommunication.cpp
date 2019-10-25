/*
Designed by sch
time:2019.10.24
此文件用于进程间通信测试用例

管道：匿名管道和命名管道两种，匿名管道占用资源少
    匿名管道创建：int pipe(int fd[2])
    读写匿名管道：只要管道中用空闲区域，写进程就会向管道写入数据，管道中如有数据，读进程就会读取数据，若读进程没有及时读走数据，写进程就会一直阻塞
                如果读端被关闭，默认写进程也会被关闭，但可设置其他动作
                向管道中写数据时必须关闭读端，读数据是必须关闭写端！！！！！！！！！！！！！！
    命名管道创建：int mkfifo(const char *pathname,mode_t mode)  //pathname是管道名字的全路径，mode是权限
    删除命名管道：int unlink(const char * pathname)
    打开命名管道：使用命名管道之前要使用open函数打开管道文件
    读写命名管道：暂无
消息队列：
    创建：int msgget(key_t key,int msgflg);key为键值，可直接指定或ftok函数自动生成。msgflg是设置消息队列的权限。
    控制消息队列：int msgctl(int msqid,int cmd,struct msqid_ds *buf)；
                msqid是消息队列的标识符，cmd为所要进行的操作，cmd有以下几个选项：
                                                                    IPC_STAT:获取消息状态。信息存在buf指向的msqid_ds结构中中
                                                                    IPC_SET:设置队列属性。要设置的属性存在buf指向的msqid_ds结构中
                                                                    IPC_RMID:删除消息队列
*/

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

#define BUFSIZE 256

void pipe_communication_nm() //匿名管道通信测试
{
    pid_t pid;
    int fifod[2];
    int sta;
    char buf[BUFSIZE] = "I love sch,because sch is so handsome!";
    if (pipe(fifod) < 0) //创建匿名管道
    {
        cout << "pipe error!";
        exit(1);
    }
    pid = fork(); //子进程
    if (pid < 0)
    {
        cout << "fork error";
        exit(1);
    }
    if (pid == 0) //子进程
    {
        close(fifod[0]); //关闭读端
        write(fifod[1], buf, sizeof(buf));
    }
    else //父进程
    {
        close(fifod[1]); //关闭写端
        read(fifod[0], buf, sizeof(buf));
        cout << "Received data from child process,and the data is: \n";
        cout << buf << endl;
        if (pid != wait(&sta))
        {
            cout << "wait error" << endl;
            exit(1);
        }
    }
}

void signal_set_handler(int sig) //sig是信号的编号,
{
    cout << "接收到信号：" << sig << endl;
    exit(0);
}
void signal_set() //信号集
{
    sigset_t set;                       //定义一个信号集
    sigemptyset(&set);                  //初始化信号集，清空所有信号
    sigaddset(&set, SIGINT);            //把SIGINT信号加入到set信号集里面
    signal(SIGINT, signal_set_handler); //设置信号处理函数
    while (1)
    {
        /* code */
        sigprocmask(SIG_BLOCK, &set, NULL); //阻塞信号
        cout << "SIGINT信号阻塞中。。。。。。" << endl;
        sleep(5);
        sigprocmask(SIG_UNBLOCK, &set, NULL); //解除阻塞
        cout << "SIGINT信号已解阻。。。。。。" << endl;
        sleep(5);
    }
}

void msgQueue()//消息队列
{
    int qid;
    key_t key;
    key = ftok("/home/sunchaohui/CProject/test_c", 'a'); //生成键值
    if (key < 0)
    {
        cout << "ftok error......" << endl;
        exit(1);
    }
    qid = msgget(key, IPC_CREAT | 0666); //创建消息队列
    if (qid < 0)
    {
        cout << "msgget error......" << endl;
        exit(1);
    }
    else
    {
        cout << "消息队列创建成功！" << endl;
    }
}

int main()
{
    //pipe_communication_nm();
    //signal_set();
    msgQueue();
    return 0;
}
