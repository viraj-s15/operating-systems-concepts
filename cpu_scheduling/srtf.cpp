#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

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
};

// Function to calculate waiting time, turnaround time, and response time for each process
void findWaitingTurnaroundAndResponseTime(vector<Process>& processes) {
    int n = processes.size();
    vector<int> remainingTime(n);

    // Copy burst times to remainingTime array
    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burstTime;

    int completed = 0, currentTime = 0, minRemainingTime = INT_MAX;
    int shortestProcess = 0, finishTime;
    bool found = false;

    vector<int> processEntryTime(n, -1); // Stores the entry time of each process

    while (completed != n) {
        // Find the process with the shortest remaining time at the current time
        for (int j = 0; j < n; j++) {
            if ((processes[j].arrivalTime <= currentTime) &&
                (remainingTime[j] < minRemainingTime) && remainingTime[j] > 0) {
                minRemainingTime = remainingTime[j];
                shortestProcess = j;
                found = true;
            }
        }

        // If no process is found, increment the current time
        if (found == false) {
            currentTime++;
            continue;
        }

        remainingTime[shortestProcess]--;

        minRemainingTime = remainingTime[shortestProcess];
        if (minRemainingTime == 0)
            minRemainingTime = INT_MAX;

        // If it's the first time the process is executed, update its entry time
        if (processEntryTime[shortestProcess] == -1) {
            processEntryTime[shortestProcess] = currentTime;
        }

        // If the process has completed its execution
        if (remainingTime[shortestProcess] == 0) {
            completed++;
            found = false;

            finishTime = currentTime + 1;

            // Calculate waiting time, completion time, turnaround time, and response time
            processes[shortestProcess].waitingTime = finishTime - processes[shortestProcess].burstTime -
                                                     processes[shortestProcess].arrivalTime;

            if (processes[shortestProcess].waitingTime < 0)
                processes[shortestProcess].waitingTime = 0;

            processes[shortestProcess].completionTime = finishTime;

            processes[shortestProcess].turnAroundTime = processes[shortestProcess].burstTime +
                                                        processes[shortestProcess].waitingTime;

            processes[shortestProcess].responseTime = processEntryTime[shortestProcess] -
                                                      processes[shortestProcess].arrivalTime;
        }

        currentTime++;
    }
}

// Function to calculate and print the average waiting time, turnaround time, and response time for all processes
void findAverageTime(vector<Process>& processes) {
    int n = processes.size();

    findWaitingTurnaroundAndResponseTime(processes);

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
    cout << "\nAverage response time = " << averageResponseTime;
    cout << endl;
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
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    findAverageTime(processes);
    return 0;
}