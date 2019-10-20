#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>
#include <iostream>
/*
此程序用于守护进程的测试用例
功能：守护进程时刻检查时间，到指定时间进行提醒信息，并做出其他设定操作
*/
int main()
{
    pid_t pid;
    time_t now;
    struct tm *p;
    pid = fork();
    if (pid < 0)
        exit(1);
    if (pid > 0)
        exit(0);
    for (int i = 0; i < 1024; i++)
        close(i);
    chdir("/tmp");
    setsid();
    umask(0);
    signal(SIGCHLD, SIG_IGN);
    while (1)
    {
        time(&now);
        p = gmtime(&now);
        if (p->tm_hour > 10 && p->tm_min > 43)
        {
            syslog(LOG_USER | LOG_INFO, "关机时间是：\t%s\n,关机进程是：\t%d", ctime(&now), getpid());
            std::string str="kill %d"+getpid();
            system("shutdown -h 10");
            system(str.c_str());
        }
        sleep(5);
    }
}