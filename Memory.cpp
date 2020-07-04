#include <iostream>
#include <vector>

using namespace std;

const int MemSize = 128 << 10;

struct MemoryPartition
{
    int start, length;

    MemoryPartition(int start, int length)
    {
        this->start = start;
        this->length = length;
    }

    MemoryPartition splitMemory(int size)
    {
        this->start = start + size;
        this->length = length - size;
        return MemoryPartition(start - size, size);
    }

    void mergeMemory(MemoryPartition m)
    {
        this->start = min(this->start, m.start);
        this->length += m.length;
    }

    int end()
    {
        return this->start + this->length - 1;
    }

    bool operator<(const MemoryPartition &b) const
    {
        return this->start < b.start;
    }
};

vector<MemoryPartition> emptyMem;
vector<pair<MemoryPartition, bool>> usedMem;

void init()
{
    emptyMem.push_back(MemoryPartition(0, MemSize));
}

bool allocate(int size)
{
    bool flag = 0;
    for (int i = 0; i < emptyMem.size(); i++)
        if (emptyMem[i].length >= size)
        {
            MemoryPartition newMem = emptyMem[i].splitMemory(size);
            usedMem.push_back({newMem, false});
            if (emptyMem[i].length == 0)
                emptyMem.erase(emptyMem.begin() + i);
            flag = 1;
            break;
        }
    return flag;
}

bool release(int id)
{
    if (usedMem[id].second)
        return false;
    usedMem[id].second = true;
    MemoryPartition nowMem = usedMem[id].first;

    int insertId = lower_bound(emptyMem.begin(), emptyMem.end(), nowMem) - emptyMem.begin();

    if (insertId < emptyMem.size() && nowMem.end() + 1 == emptyMem[insertId].start)
    {
        emptyMem[insertId].mergeMemory(nowMem);
    }
    else
        emptyMem.insert(emptyMem.begin() + insertId, nowMem);

    if (insertId > 0 && emptyMem[insertId].start == emptyMem[insertId - 1].end() + 1)
    {
        emptyMem[insertId - 1].mergeMemory(emptyMem[insertId]);
        emptyMem.erase(emptyMem.begin() + insertId);
    }
    return true;
}

void printMem()
{
    cout << "Memory Allocation:" << endl;
    if (emptyMem.empty())
    {
        cout << "Memory from " << 0
             << " to " << MemSize - 1 << " is used." << endl;
    }
    else
    {

        if (emptyMem[0].start > 0)
            cout << "Memory from " << 0
                 << " to " << emptyMem[0].start - 1 << " is used." << endl;
        for (int i = 0; i < emptyMem.size(); i++)
        {
            if (i > 0 && emptyMem[i - 1].end() + 1 < emptyMem[i].start)
                cout << "Memory from " << emptyMem[i - 1].end() + 1
                     << " to " << emptyMem[i].start - 1 << " is used."
                     << endl;
            cout << "Memory from " << emptyMem[i].start
                 << " to " << emptyMem[i].end() << " is empty."
                 << endl;
        }
        if (emptyMem[emptyMem.size() - 1].end() + 1 < MemSize - 1)
            cout << "Memory from " << emptyMem[emptyMem.size()].end() + 1
                 << " to " << MemSize - 1 << " is used." << endl;

        cout << endl;
    }

    cout << "Used Memory List:" << endl;
    int id = 0;
    for (auto now : usedMem)
    {
        if (!now.second)
            cout << "Memory block with index " << id
                 << " used memory " << now.first.start << " to " << now.first.end()
                 << "." << endl;
        id++;
    }
    cout << endl;
}

int main()
{
    init();

    while (true)
    {
        cout << "If you want to allocate a memory block with indicated size, enter 'new' and the indicated size" << endl;
        cout << "If you want to free the indicated memory with indicated index, enter 'free' and the indicated index" << endl;

        string op;
        int parameter;

        cin >> op >> parameter;

        if (op == "new")
        {
            if (allocate(parameter))
            {
                int id = usedMem.size() - 1;
                cout << "The allocated memory starts with " << usedMem[id].first.start
                     << " and length " << usedMem[id].first.length
                     << ", and the index is " << id << "!" << endl;
            }
            else
                cout << "Can't allocate memory with size " << parameter << " bytes!" << endl;
        }

        if (op == "free")
        {
            if (release(parameter))

                cout << "Free the memory block with index " << parameter << "!" << endl;
            else
                cout << "Can't free the memory block with index" << parameter << "!" << endl;
        }

        printMem();
    }

    return 0;
}
