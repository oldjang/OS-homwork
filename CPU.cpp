#include <iostream>

using namespace std;

enum StateType {
    R, E
};

class PCB {
private:
    static int currentID;
    int ID;
    int totalTime;
    int priority;
    StateType state;

public:
    PCB *nextPCB;

    PCB(int time, int Priority) {
        ID = currentID++;
        totalTime = time;
        priority = Priority;
        state = R;
        nextPCB = nullptr;
    }

    void printPCB() {
        cout << "The P" << ID
             << " with priority " << priority
             << " needs to run " << totalTime
             << endl;
    }

    void run() {
        cout << "The P" << ID << " is running!" << endl;
        priority--;
        totalTime--;
        if (totalTime == 0)
            state = E;
    }

    bool judgeState() {
        return state == R;
    }

    bool operator<(const PCB &pcb) {
        return priority < pcb.priority;
    }

};

int PCB::currentID = 0;

struct ProcessQueue {
    PCB *head;

    ProcessQueue() { head = nullptr; }

    void push(PCB *currentPCB) {
        if (head == nullptr || (*head) < (*currentPCB)) {
            currentPCB->nextPCB = head;
            head = currentPCB;
        } else {
            PCB *tmp = head;
            while (tmp->nextPCB != nullptr && (*currentPCB) < (*(tmp->nextPCB)))
                tmp = tmp->nextPCB;

            currentPCB->nextPCB = tmp->nextPCB;
            tmp->nextPCB = currentPCB;
        }
    }

    PCB *pop() {
        PCB *currentPCB = head;
        head = head->nextPCB;
        return currentPCB;
    }

    bool empty() {
        return head == nullptr;
    }

    void printState() {
        if (empty()) {
            cout << "There is no ready process!" << endl;
        } else {
            cout << "The remaining ready processes:" << endl;
            for (PCB *currentPCB = head; currentPCB != nullptr; currentPCB = currentPCB->nextPCB)
                currentPCB->printPCB();
        }
        cout << endl;
    }

};

void work(ProcessQueue workQueue) {
    int currentTime = 0;
    while (!workQueue.empty()) {
        cout << "When time " << currentTime << " :" << endl;
        workQueue.printState();
        PCB *currentPCB = workQueue.pop();
        currentPCB->run();
        workQueue.printState();
        cout << endl;
        if (currentPCB->judgeState())
            workQueue.push(currentPCB);

        currentTime++;
    }
}

int main() {
    int count;
    cout << "Please input the number of processes: ";
    cin >> count;

    ProcessQueue workQueue;
    for (int i = 1; i <= count; i++) {
        int priority, totalTime;
        cout << "The priority and the time required running of the " << i << "-th process are:";
        cin >> priority >> totalTime;
        workQueue.push(new PCB(totalTime, priority));
    }

    work(workQueue);
    return 0;
}