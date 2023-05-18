#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// Structure to represent a process
struct Process {
    int processId;
    int burstTime;
    int arrivalTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    int responseTime;
    int priority;
};

// Function to calculate waiting time, turnaround time, and response time for each process
void findWaitingTurnaroundAndResponseTime(vector<Process>& processes) {
    // Remaining time for each process
    vector<int> remainingTime(processes.size());

    for (int i = 0; i < processes.size(); i++)
        remainingTime[i] = processes[i].burstTime;

    int completed = 0, currentTime = 0, minRemainingTime = INT_MAX;
    int shortestProcess = 0, finishTime;
    bool found = false;

    vector<int> processEntryTime(processes.size(), -1); // Stores the entry time of each process

    while (completed != processes.size()) {
        for (int j = 0; j < processes.size(); j++) {
            if (processes[j].arrivalTime <= currentTime && remainingTime[j] < minRemainingTime && remainingTime[j] > 0) {
                minRemainingTime = remainingTime[j];
                shortestProcess = j;
                found = true;
            }
        }

        if (found == false) {
            currentTime++;
            continue;
        }

        remainingTime[shortestProcess]--;

        minRemainingTime = remainingTime[shortestProcess];
        if (minRemainingTime == 0)
            minRemainingTime = INT_MAX;

        if (processEntryTime[shortestProcess] == -1) {
            processEntryTime[shortestProcess] = currentTime;
        }

        if (remainingTime[shortestProcess] == 0) {
            completed++;
            found = false;

            finishTime = currentTime + 1;

            processes[shortestProcess].waitingTime = finishTime - processes[shortestProcess].burstTime - processes[shortestProcess].arrivalTime;
            if (processes[shortestProcess].waitingTime < 0)
                processes[shortestProcess].waitingTime = 0;

            processes[shortestProcess].completionTime = finishTime;

            processes[shortestProcess].turnAroundTime = processes[shortestProcess].burstTime + processes[shortestProcess].waitingTime;

            processes[shortestProcess].responseTime = processEntryTime[shortestProcess] - processes[shortestProcess].arrivalTime;
        }

        currentTime++;
    }
}

// Function to calculate and print the average waiting time, turnaround time, and response time for all processes
void findAverageTime(vector<Process>& processes) {
    findWaitingTurnaroundAndResponseTime(processes);

    cout << " Process\tBurst Time\tArrival Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n";

    float totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalResponseTime += processes[i].responseTime;
        cout << " " << processes[i].processId << "\t\t" << processes[i].burstTime
             << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].priority
             << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].waitingTime
             << "\t\t" << processes[i].turnAroundTime << "\t\t" << processes[i].responseTime << endl;
    }

    float averageWaitingTime = totalWaitingTime / processes.size();
    float averageTurnAroundTime = totalTurnAroundTime / processes.size();
    float averageResponseTime = totalResponseTime / processes.size();

    cout << "\nAverage waiting time = " << averageWaitingTime;
    cout << "\nAverage turn around time = " << averageTurnAroundTime;
    cout << "\nAverage response time = " << averageResponseTime << endl;
}

int main() {
    srand(time(NULL)); // Seed the random number generator with the current time

    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter the burst time and arrival time for each process:\n";
    set<int> priorities; // Set to store generated priorities

    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
        processes[i].processId = i + 1;

        // Generate a random priority between 0 and 10 (inclusive) that is different from already generated priorities
        int priority;
        do {
            priority = rand() % 11;
        } while (priorities.count(priority) > 0);
        priorities.insert(priority);
        processes[i].priority = priority;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    findAverageTime(processes);
    return 0;
}