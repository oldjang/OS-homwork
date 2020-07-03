#include <iostream>
#include <vector>

using namespace std;

//重载vector的加减法
vector<int> operator+(const vector<int> &v1, const vector<int> &v2)
{

    vector<int> r;
    for (auto i = 0; i < v1.size(); i++)
        r.push_back(v1[i] + v2[i]);
    return r;
}

vector<int> operator-(const vector<int> &v1, const vector<int> &v2)
{

    vector<int> r;
    for (auto i = 0; i < v1.size(); i++)
        r.push_back(v1[i] - v2[i]);
    return r;
}

bool operator<=(const vector<int> &v1, const vector<int> &v2)
{
    bool r = 1;
    for (auto i = 0; i < v1.size(); i++)
        r &= v1[i] <= v2[i];
    return r;
}

vector<int> available, tryAvailable;

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

    //输入初始资源的数量
    cout << "Enter the number of each resource : ";
    for (int i = 0; i < resourceType; i++)
        cin >> available[i];

    //输入进程数
    cout << "Enter the number of processes: ";
    cin >> processNum;
    process.resize(processNum);

    //输入每个进程需要的资源
    cout << "Enter the resources required by each process : " << endl;
    for (int i = 0; i < processNum; i++)
    {
        cout << "Enter the number of each resource required by the " << i << "-th process : ";
        process[i].need.resize(resourceType);
        for (int j = 0; j < resourceType; j++)
            cin >> process[i].need[j];
    }

    //如果有需要，输入已经分配的资源情况
    cout << "Do you need to allocate resources in advance?(y:yes,n:no)" << endl;
    for (int i = 0; i < processNum; i++)
        process[i].allocation.resize(resourceType);
    char yOrn;
    cin >> yOrn;

    if (yOrn == 'y')
    {
        for (int i = 0; i < processNum; i++)
        {
            cout << "Enter the number of each resource allocated to the " << i << "-th process : ";
            for (int j = 0; j < resourceType; j++)
                cin >> process[i].allocation[j];
        }
    }
}

vector<int> findSafeSequence() //安全性检查
{
    vector<int> nowAvailable = available;
    vector<bool> released(false, processNum);
    vector<int> safeSequence;

    for (int i = 0; i < processNum; i++)
    {
        bool flag = 0;
        for (int j = 0; j < processNum; j++)
            if (process[j].need <= nowAvailable)
            {
                released[j] = true;
                nowAvailable = nowAvailable + process[j].allocation;
                safeSequence.push_back(j);
                flag = 1;
                break;
            }
        if (!flag)
        {
            safeSequence.clear();
            break;
        }
    }
    return safeSequence;
}

int main()
{
    init();

    while (true)
    {
        cout << "Now the need matrix is:" << endl;
        for (int i = 0; i < processNum; i++)
        {
            for (int j = 0; j < resourceType; j++)
                cout << process[i].need[j] << ' ';
            cout << endl;
        }

        cout << "Now the available vector is:" << endl;
        for (int i = 0; i < resourceType; i++)
            cout << available[i] << ' ';
        cout << endl;

        int pid;
        cout << "Enter the pid: ";
        cin >> pid;
        cout << "Enter the resource vector of process " << pid << " : " << endl;

        //输入请求向量
        vector<int> request;
        request.resize(resourceType);
        for (int i = 0; i < resourceType; i++)
            cin >> request[i];

        //如果请求向量大于所需资源向量，输出错误信息
        if (!(request <= process[pid].need))
        {
            cout << "Request exceeds required resources!" << endl;
            continue;
        }

        //如果请求向量大于当前可利用资源向量，则让进程等待
        if (!(request <= available))
        {
            cout << "Request is greater than available resources!" << endl;
            continue;
        }

        //假如可以分配

        //尝试分配
        process[pid].allocation = process[pid].allocation + request;
        process[pid].need = process[pid].need - request;
        available = available - request;

        //检查是否安全
        vector<int> safeSequece = findSafeSequence();
        if (safeSequece.size() > 0)
        {
            cout << "Successful request!" << endl;
            cout << "The current safety sequence can be: ";
            for (int i = 0; i < processNum; i++)
                cout << safeSequece[i] << ' ';
            cout << endl;
        }
        else
        {
            cout << "Request failed!" << endl;
            process[pid].allocation = process[pid].allocation - request;
            process[pid].need = process[pid].need + request;
            available = available + request;
        }
    }

    return 0;
}
