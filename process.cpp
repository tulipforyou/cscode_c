#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include<syslog.h>
#include<time.h>
using namespace std;

#define SIZE 1024

void POPEN()//管道
{
    char buff[SIZE];
    FILE *P;
    string cmd = "ps -f";
    if ((P = popen(cmd.c_str(), "r")) == NULL)
    {
        cout << "命令有误！" << endl;
        exit(1);
    }
    while (fgets(buff, sizeof(buff), P)) //将P中的数据流读到缓冲区
        cout << buff << endl;
    pclose(P);
}

void FORK()
{
    pid_t pid;
    //int sta;
    int j = 1;
    string tr = "我爱孙朝辉";
    pid = fork(); // 创建进程
    if (pid < 0)
    {
        cout << "进程创建失败" << endl;
        exit(1);
    }
    if (pid == 0)
    {
        cout << "子进程：" << endl;
        cout << "pid=" << getpid() << endl;
        cout << "ppid=" << getppid() << endl;
        cout << "gid=" << getgid() << endl;
        cout << "优先级:" << getpriority(PRIO_PROCESS, getpid()) << endl;


        for (int i = 0; i < 1024; i++)
            close(i);             //关闭父进程打开的文件描述符
        chdir("/tmp");            //改变工作目录
        setsid();                 //创建新会话
        umask(0);                 //重设文件权限掩码
        signal(SIGCHLD, SIG_IGN); //防止子进程成为僵尸进程
        //  此时子进程已经是一个守护进程了

        //守护进程的后台运行
       /* while (1)
        {
            FILE *fp = fopen("/home/sunchaohui/test.txt", "a");
            if (fp == NULL)
                cout << "文件打开失败" << endl;
            fputs(tr.c_str(), fp);
            fclose(fp);
            sleep(1);
        }*/

        //守护进程的输出
        time_t now;
        syslog(LOG_USER|LOG_INFO,"守护进程测试\n");  //输出到/var/log/syslog文件里了
        while(1)
        {
            time(&now);
            syslog(LOG_USER|LOG_INFO,"当前时间：\t%s\t\n",ctime(&now));
            sleep(5);
        }
    }
    else
    {
        cout << "父进程：" << endl;
        cout << "pid=" << getpid() << endl;
        cout << "ppid=" << getppid() << endl;
        cout << "gid=" << getgid() << endl;
        cout << "优先级:" << getpriority(PRIO_PROCESS, getpid()) << endl;

        for (j = 1; j < 100; j++)
            cout << "父进程运行:" << j << " \t";
        cout << endl;
        /*if (pid != wait(&sta)) //父进程阻塞，等待子进程结束
        {
            cout << "wait error" << endl;
            exit(1);
        }
        if (WIFEXITED(sta))
            i = WEXITSTATUS(sta);
        cout<<"子进程终止信号是："<<i<<endl;*/
        cout << "父进程结束" << endl;
    }
}

int main()
{
    // POPEN();
    FORK();
    return 0;
}
