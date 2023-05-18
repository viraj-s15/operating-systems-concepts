#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int processId;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    int responseTime;
};

void findWaitingTurnaroundAndResponseTime(vector<Process>& processes, int timeQuantum) {
    int n = processes.size();
    vector<int> remainingTime(n);

    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burstTime;

    int completed = 0, currentTime = 0;

    while (completed != n) {
        bool isProcessExecuted = false;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] > 0 && processes[i].remainingTime > 0) {
                if (remainingTime[i] <= timeQuantum) {
                    currentTime += remainingTime[i];
                    processes[i].completionTime = currentTime;
                    processes[i].remainingTime = 0;
                    processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                    processes[i].responseTime = processes[i].waitingTime;
                    completed++;
                } else {
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                }

                isProcessExecuted = true;
            }
        }

        if (!isProcessExecuted)
            currentTime++;
    }
}

void findAverageTime(vector<Process>& processes, int timeQuantum) {
    int n = processes.size();

    findWaitingTurnaroundAndResponseTime(processes, timeQuantum);

    cout << " Process\tBurst Time\tArrival Time\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n";

    float totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalResponseTime += processes[i].responseTime;
        cout << " " << processes[i].processId << "\t\t" << processes[i].burstTime
             << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].completionTime
             << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].turnAroundTime
             << "\t\t" << processes[i].responseTime << endl;
    }

    float averageWaitingTime = totalWaitingTime / n;
    float averageTurnAroundTime = totalTurnAroundTime / n;
    float averageResponseTime = totalResponseTime / n;

    cout << "\nAverage waiting time = " << averageWaitingTime;
    cout << "\nAverage turn around time = " << averageTurnAroundTime;
    cout << "\nAverage response time = " << averageResponseTime << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes ->  ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter the burst time and arrival time for each process -> \n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " -> \n";
        cout << "Arrival Time ->  ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time ->  ";
        cin >> processes[i].burstTime;
        processes[i].processId = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int timeQuantum;
    cout << "Enter the time quantum ->  ";
    cin >> timeQuantum;

    findAverageTime(processes, timeQuantum);
    return 0;
}