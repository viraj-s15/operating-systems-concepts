#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// This code implements the first come first serve algorithm
// It is non-preemptive in nature

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
};

void calculateCompletionTime(const vector<Process>& processes, vector<int>& completionTimes) {
    int n = processes.size();
    vector<Process> sortedProcesses = processes;
    sort(sortedProcesses.begin(), sortedProcesses.end(), [](const Process& p1, const Process& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    });

    completionTimes[0] = sortedProcesses[0].arrivalTime + sortedProcesses[0].burstTime;

    for (int i = 1; i < n; i++) {
        int currentCompletionTime = completionTimes[i - 1] + sortedProcesses[i].burstTime;
        completionTimes[i] = max(currentCompletionTime, sortedProcesses[i].arrivalTime + sortedProcesses[i].burstTime);
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

void displayTable(const vector<Process>& processes,const vector<int>& completionTimes, const vector<int>& turnaroundTimes, const vector<int>& waitingTimes, const vector<int>& responseTimes) {
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time" << endl;

    for (int i = 0; i < processes.size(); i++) {
        cout << processes[i].processId << "\t" << processes[i].arrivalTime << "\t\t" <<  processes[i].burstTime << "\t\t"
             << completionTimes[i] << "\t\t" << turnaroundTimes[i] << "\t\t" << waitingTimes[i] << "\t\t" << responseTimes[i] << endl;
    }

    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    vector<int> arrivalTimes(n);
    vector<int> burstTimes(n);

    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;

        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;

        cout << "Enter burst time for Process " << i + 1 << ": ";
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
    displayTable(processes,completionTimes, turnaroundTimes, waitingTimes, responseTimes);
    return 0;
}