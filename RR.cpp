#include <iostream>
using namespace std;

#define MAX 50

class cir_que {
public:
    int item[MAX];
    int front, rear;

    cir_que() {
        front = rear = -1;
    }

    bool isEmpty() {
        return (front == -1);
    }

    bool isFull() {
        return ((front == 0 && rear == MAX - 1) || (front == rear + 1));
    }

    void enque(int x) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        if (front == -1)
            front = rear = 0;
        else
            rear = (rear + 1) % MAX;
        item[rear] = x;
    }

    int deque() {
        if (isEmpty()) {
            return -1;
        }
        int x = item[front];
        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % MAX;
        return x;
    }
};

void RoundRobin(int process[], int n, int arrival[], int burst[], int quantum) {
    cir_que q;
    int remaining[n], waiting[n] = {0}, turnaround[n] = {0};
    int completion[n] = {0};
    bool inQueue[n] = {false};
    int currentTime = 0, completed = 0;

    for (int i = 0; i < n; i++)
        remaining[i] = burst[i];

    cout << "\nGantt Chart (Process Execution Order):\n";

    for (int i = 0; i < n; i++) {
        if (arrival[i] <= currentTime && !inQueue[i]) {
            q.enque(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        if (q.isEmpty()) {
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (arrival[i] <= currentTime && !inQueue[i]) {
                    q.enque(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int i = q.deque();
        cout << "| P" << process[i] << " ";

        if (remaining[i] > quantum) {
            remaining[i] -= quantum;
            currentTime += quantum;
        } else {
            currentTime += remaining[i];
            remaining[i] = 0;
            completion[i] = currentTime;
            turnaround[i] = completion[i] - arrival[i];
            waiting[i] = turnaround[i] - burst[i];
            completed++;
        }

        for (int j = 0; j < n; j++) {
            if (arrival[j] <= currentTime && !inQueue[j] && remaining[j] > 0) {
                q.enque(j);
                inQueue[j] = true;
            }
        }

        if (remaining[i] > 0)
            q.enque(i);
    }

    cout << "|\n\n";

    double totalWT = 0, totalTAT = 0;
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        totalWT += waiting[i];
        totalTAT += turnaround[i];
        cout << "P" << process[i] << "\t" << arrival[i] << "\t" << burst[i] << "\t"
             << completion[i] << "\t" << turnaround[i] << "\t" << waiting[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
}

int main() {
    int n, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    int process[n], arrival[n], burst[n];

    for (int i = 0; i < n; i++) {
        process[i] = i + 1;
        cout << "\nEnter Arrival Time for P" << process[i] << ": ";
        cin >> arrival[i];
        cout << "Enter Burst Time for P" << process[i] << ": ";
        cin >> burst[i];
    }

    cout << "\nEnter Time Quantum: ";
    cin >> quantum;

    RoundRobin(process, n, arrival, burst, quantum);

    return 0;
}

