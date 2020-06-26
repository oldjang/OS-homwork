#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    pid_t fpid;
    char ch='A';
    for(int i=0;i<2;i++)
    {
        fpid=fork();
        if(fpid==-1)
            cout<<"ERROR"<<endl;
        if(fpid==0){
            ch=ch+i+1;
            break;
        }
    }
    cout<<"The process "<<ch<<" is running!"<<endl;
    return 0;
}
