#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// This code implements the shortest job first algorithm which uses a non-preemptive method
// The preemptive version of this algorithm is referred to as shortest remaining time first algorithm
struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
};

bool compare(const Process& p1, const Process& p2) {
    if (p1.burstTime == p2.burstTime) {
        return p1.arrivalTime < p2.arrivalTime;
    }
    return p1.burstTime < p2.burstTime;
}

void calculateCompletionTime(const vector<Process>& processes, vector<int>& completionTimes) {
    int n = processes.size();
    vector<Process> sortedProcesses = processes;
    sort(sortedProcesses.begin(), sortedProcesses.end(), compare);

    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        int processIndex = sortedProcesses[i].processId - 1;
        int processBurstTime = sortedProcesses[i].burstTime;

        if (currentTime < sortedProcesses[i].arrivalTime) {
            currentTime = sortedProcesses[i].arrivalTime;
        }

        completionTimes[processIndex] = currentTime + processBurstTime;
        currentTime += processBurstTime;
    }
}

void calculateTurnaroundTime(const vector<Process>& processes, const vector<int>& completionTimes, vector<int>& turnaroundTimes) {
    int n = processes.size();

    for (int i = 0; i < n; i++) {
        turnaroundTimes[i] = completionTimes[i] - processes[i].arrivalTime;
    }
}

void calculateWaitingTime(const vector<Process>& processes, const vector<int>& turnaroundTimes, vector<int>& waitingTimes) {
    int n = processes.size();

    for (int i = 0; i < n; i++) {
        waitingTimes[i] = turnaroundTimes[i] - processes[i].burstTime;
    }
}

void calculateResponseTime(const vector<int>& waitingTimes, vector<int>& responseTimes) {
    int n = waitingTimes.size();

    for (int i = 0; i < n; i++) {
        responseTimes[i] = waitingTimes[i];
    }
}

void displayTable(const vector<Process>& processes, const vector<int>& arrivalTimes, const vector<int>& burstTimes, const vector<int>& completionTimes, const vector<int>& turnaroundTimes, const vector<int>& waitingTimes, const vector<int>& responseTimes) {
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time" << endl;

    for (int i = 0; i < processes.size(); i++) {
        cout << processes[i].processId << "\t" << arrivalTimes[i] << "\t\t" << burstTimes[i] << "\t\t"
             << completionTimes[i] << "\t\t" << turnaroundTimes[i] << "\t\t" << waitingTimes[i] << "\t\t" << responseTimes[i] << endl;
    }

    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes -> ";
    cin >> n;

    vector<Process> processes(n);
    vector<int> arrivalTimes(n);
    vector<int> burstTimes(n);

    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;

        cout << "Enter arrival time for Process " << i + 1 << " -> ";
        cin >> processes[i].arrivalTime;
            cout << "Enter burst time for Process " << i + 1 << ": -> ";
    cin >> processes[i].burstTime;
}

    vector<int> completionTimes(n);
    vector<int> turnaroundTimes(n);
    vector<int> waitingTimes(n);
    vector<int> responseTimes(n);

    calculateCompletionTime(processes, completionTimes);
    calculateTurnaroundTime(processes, completionTimes, turnaroundTimes);
    calculateWaitingTime(processes, turnaroundTimes, waitingTimes);
    calculateResponseTime(waitingTimes, responseTimes);
    displayTable(processes, arrivalTimes, burstTimes, completionTimes, turnaroundTimes, waitingTimes, responseTimes);
    return 0;
}