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
    读写命名管道：
*/

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

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
            cout << "eait error" << endl;
            exit(1);
        }
    }
}

void pipe_communication_mm()
{

}

int main()
{
    pipe_communication_nm();
    return 0;
}
