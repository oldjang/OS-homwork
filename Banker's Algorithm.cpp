#include <iostream>
#include <vector>

using namespace std;

//重载vector的加减法
vector<int> operator+(const vector<int>& v1, const vector<int>& v2) {
	
  	vector<int> r;
  	r.reserve(v1.size());
  	for(auto i=0; i<v1.size();i++) 
    	r.push_back(v1[i] + v2[i]);
  	return r;
}

vector<int> operator-(const vector<int>& v1, const vector<int>& v2) {
	
  	vector<int> r;
  	r.reserve(v1.size());
  	for(auto i=0; i<v1.size();i++) 
    	r.push_back(v1[i] - v2[i]);
  	return r;
}

vector<int> available, tryAvailable, request;

struct Process
{
    vector<int> need, allocation;
};

vector<Process> process, tryProcess;

int resourceType, processNum;

void init() //输入初始状态
{
    //输入资源种类
    cout << "Enter the number of resource types : ";
    cin >> resourceType;
    available.resize(resourceType);
    tryAvailable.resize(resourceType);
    request.resize(resourceType);

    //输入初始资源的数量
    cout << "Enter the number of each resource : ";
    for (int i = 0; i < resourceType; i++)
        cin >> available[i];

    //输入进程数
    cout << "Enter the number of processes: ";
    cin >> processNum;
    process.resize(processNum);
    tryProcess.resize(processNum);

    //输入每个进程需要的资源
    cout << "Enter the resources required by each process : " << endl;
    for (int i = 0; i < processNum; i++)
    {
        cout << "Enter the number of each resource required by the " << i << "-th process : ";
        process[i].need.resize(resourceType);
        tryProcess[i].need.resize(resourceType);
        for (int j = 0; j < resourceType; j++)
            cin >> process[i].need[j];
        process[i].allocation.resize(resourceType);
        tryProcess[i].allocation.resize(resourceType);
    }

    //如果有需要，输入已经分配的资源情况
}

bool isSecure()
{
    //安全性检查
    //输出安全序列
}

bool tryAllocate() //尝试分配
{
    //复制向量
    //分配
    //安全性检查
}

int main()
{
    init();

    while (true)
    {
        int pid;
        cout << "Enter the pid: ";
        cin >> pid;
        cout << "Enter the resource vector of process " << pid << " : " << endl;
        //输入请求向量
        //假如可以分配，分配向量，输出目前状态
        //如果请求向量大于所需资源向量，输出错误信息
        //如果请求向量大于当前可利用资源向量，则让进程等待
    }

    return 0;
}
