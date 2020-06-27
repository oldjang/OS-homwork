#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    pid_t fpid; //进程ID
    char ch='A';  //标识进程ABC
    for(int i=0;i<2;i++)//创建两个子进程
    {
        fpid=fork();
        if(fpid==-1)
            cout<<"ERROR"<<endl; //如果创建进程错误
        if(fpid==0){
            ch='B'+i; //如果是子进程，那么用ch标识不同进程
            break;
        }
    }
    cout<<"The process "<<ch<<" is running!"<<endl; //输出进程ABC
    return 0;
}
