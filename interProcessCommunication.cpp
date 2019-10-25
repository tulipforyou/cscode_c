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
    读写消息队列：int msgsnd(int msqid,struct msgbuf *msgp,int msgsz,int msgflg);msgp是消息内容，msgsz是消息大小，msgflg消息队列没有足够空间时的操作
共享内存：
    创建或打开：int shmget(key_t key,int size,int shmflg);size是内存的大小，shmflg是权限
    读写共享内存：void shmat(int shm_id,void *shm_addr,int shmflg);shm_addr设置共享内存映射到进程地址空间的具体位置，一般情况为NULL，shmflg是权限，函数返回映射后共享内存的地址
                通过这个地址，进程可以像访问一般内存一样访问共享内存了
    共享内存脱离地址空间：int shmdt(void *shmaddr);执行成功返回0
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
#include <syslog.h>
#include <time.h>
#include <sys/shm.h>

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

void msgQueue() //消息队列
{
    int fifod[2];
    int buf[BUFSIZE];
    if (pipe(fifod) < 0) //创建匿名管道
    {
        cout << "pipe error!";
        exit(1);
    }

    pid_t pid;
    pid = fork(); //创建子进程删除消息队列
    if (pid < 0)
    {
        cout << "fork error......" << endl;
        exit(1);
    }
    if (pid == 0)
    {
        cout << "20s后删除消息队列" << endl;
        close(fifod[1]);
        read(fifod[0], buf, sizeof(buf));
        int a = buf[0];
        sleep(20);
        msgctl(a, IPC_RMID, NULL); //删除消息队列
        signal(SIGCHLD, SIG_IGN);
        time_t now;
        time(&now);
        syslog(LOG_USER | LOG_INFO, "消息队列子进程在\t%s\t后删除了消息队列后退出！！！", ctime(&now));
    }
    else
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
        buf[0] = qid;
        close(fifod[0]);
        write(fifod[1], buf, sizeof(buf));
        if (qid < 0)
        {
            cout << "msgget error......" << endl;
            exit(1);
        }
        else
        {
            cout << "消息队列创建成功！" << endl;
        }
        cout << "父进程退出...." << endl;
    }
}

void shm_communication()
{
    int shmid;
    pid_t pid;
    int psm;
    struct shmid_ds dsbuf;
    key_t key = ftok("/home/sunchaohui/CProject/test_c", 's');
    if (key < 0)
    {
        cout << "ftok error" << endl;
        exit(1);
    }
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        cout << "shmget error" << endl;
        exit(1);
    }
    else
    {
        cout << "创建共享内存成功" << endl;
    }

    //shmctl(shmid,IPC_RMID,NULL);//删除共享内存
}

int main()
{
    //pipe_communication_nm();
    //signal_set();
    // msgQueue();
    shm_communication();
    return 0;
}
