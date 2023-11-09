#include<stdio.h>
#include<limits.h>

struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival Time of the process
    int burstTime;      // Burst Time of the process
    int completionTime; // Completion Time of the process
    int turnaroundTime; // Turnaround Time of the process
    int waitingTime;    // Waiting Time of the process
};

// Function to input process details
void inputProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }
}

// Function to perform Shortest Job First Scheduling
void sjfScheduling(struct Process processes[], int n) {
    int currentTime = 0;    // Current time during scheduling
    int completed = 0;      // Number of completed processes

    while (completed < n) {
        int shortestJob = -1;    // Index of the process with the shortest burst time
        int shortestTime = INT_MAX; // Shortest burst time

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].completionTime) {
                if (processes[i].burstTime < shortestTime) {
                    shortestTime = processes[i].burstTime;
                    shortestJob = i;
                }
            }
        }

        if (shortestJob == -1) {
            currentTime++;  // If no process is ready, increment current time
        } else {
            // Update process information and move to the next process
            processes[shortestJob].completionTime = currentTime + processes[shortestJob].burstTime;
            processes[shortestJob].turnaroundTime = processes[shortestJob].completionTime - processes[shortestJob].arrivalTime;
            processes[shortestJob].waitingTime = processes[shortestJob].turnaroundTime - processes[shortestJob].burstTime;
            currentTime = processes[shortestJob].completionTime;
            completed++;
        }
    }
}

// Function to display process details
void displayProcesses(struct Process processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].completionTime, processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

// Function to calculate and display average waiting time
void calculateAverageWaitingTime(struct Process processes[], int n) {
    float totalWaitingTime = 0;
    float averageWaitingTime;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
    }

    averageWaitingTime = totalWaitingTime / n;
    printf("Average waiting time is: %f\n", averageWaitingTime);
}

int main() {
    printf("\nArchit Jain\nCSE-B\n72\n\n");

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    inputProcesses(processes, n);

    // Perform SJF Scheduling
    sjfScheduling(processes, n);

    // Display process details
    displayProcesses(processes, n);

    // Calculate and display average waiting time
    calculateAverageWaitingTime(processes, n);

    return 0;
}
