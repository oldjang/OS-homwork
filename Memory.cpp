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

    bool operator<(const MemoryPartition &b) const
    {
        return this->start < b.start;
    }
};

vector<MemoryPartition> emptyMem, usedMem;

bool allocate(int size)
{
}

bool clear(int id)
{
}

int main()
{
    return 0;
}
