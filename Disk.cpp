#include <iostream>
#include <bitset>
#include <string>

using namespace std;

const int ByteNum = 8;

bool bitmap[ByteNum][8];
int bitCount;

void init()
{
    for (int i = 0; i < ByteNum; i++)
        for (int j = 0; j < 8; j++)
            bitmap[i][j] = 0;
    bitCount = 0;
}

void print()
{
    cout << "The current bitmap is:" << endl;
    cout << "  ";
    for (int i = 0; i < 8; i++)
        cout << i << ' ';
    cout << endl;
    for (int i = 0; i < ByteNum; i++)
    {
        cout << i << ' ';
        for (int j = 0; j < 8; j++)
            cout << bitmap[i][j] << ' ';
        cout << endl;
    }
}

void allocate(int num)
{
    if (num + bitCount > 8 * ByteNum)
    {
        cout << "Insufficient disk space!" << endl;
        return;
    }
    cout << "Allocation success!" << endl;
    cout << "The physical addresses are:" << endl;
    for (int i = 0; i < ByteNum; i++)
        for (int j = 0; j < 8; j++)
            if (!bitmap[i][j])
            {
                cout << "The cylinder number is " << i
                     << ", the track number is " << (j >> 2)
                     << ", and the physical record number is " << (j - ((j >> 2) << 2))
                     << "." << endl;
                bitmap[i][j] = 1;
                num--;
                bitCount--;
                if (num == 0)
                    return;
            }
}

void freeMem(int cid, int tid, int pid)
{
    int byteId = cid, bitId = (tid << 2) | pid;
    if (!bitmap[byteId][bitId])
    {
        cout << "This address has not been allocated!" << endl;
        return;
    }

    bitmap[byteId][bitId] = 0;
    bitCount++;

    cout << "Addresses with byte number " << byteId
         << " and bit number " << bitId << " have been recovered." << endl;
}

int main()
{
    init();
    while (true)
    {
        print();

        cout << "If you want to allocate space, please enter 'new' and the required number of disk blocks." << endl;
        cout << "If you want to free up disk space, please enter 'free' and physical address (including cylinder number, track number, physical record number)." << endl;

        string op;
        cin >> op;

        if (op == "new")
        {
            int num;
            cin >> num;
            allocate(num);
        }

        if (op == "free")
        {
            int cid, tid, pid;
            cin >> cid >> tid >> pid;
            freeMem(cid, tid, pid);
        }
    }
    return 0;
}