#include<stdio.h>

void inputProcesses(int n, int a[], int b[]) {
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &a[i]);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &b[i]);
    }
}

void printTableHeader() {
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
}

void printProcessDetails(int i, int burstTime, int arrivalTime, int waitingTime, int turnaroundTime, int completionTime) {
    printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime, arrivalTime, waitingTime, turnaroundTime, completionTime);
}

void calculateTimes(int n, int a[], int b[]) {
    int x[10], waiting[10], turnaround[10], completion[10];
    int count = 0, time = 0;
    double avgWaiting = 0, avgTurnaround = 0;

    for (int i = 0; i < n; i++)
        x[i] = b[i];

    b[9] = 9999;

    for (time = 0; count != n; time++) {
        int smallest = 9;
        for (int i = 0; i < n; i++) {
            if (a[i] <= time && b[i] < b[smallest] && b[i] > 0)
                smallest = i;
        }
        b[smallest]--;
        if (b[smallest] == 0) {
            count++;
            int end = time + 1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
        }
    }

    printTableHeader();
    for (int i = 0; i < n; i++) {
        printProcessDetails(i, x[i], a[i], waiting[i], turnaround[i], completion[i]);
        avgWaiting += waiting[i];
        avgTurnaround += turnaround[i];
    }

    printf("\nAverage waiting time = %lf", avgWaiting / n);
    printf("  Average Turnaround time = %lf\n", avgTurnaround / n);
}

int main() {
    int n;
    printf("Archit Jain \nCSE-B \nRollno : 72\n\nEnter the number of Processes: ");
    scanf("%d", &n);

    int arrivalTime[10], burstTime[10];

    inputProcesses(n, arrivalTime, burstTime);
    calculateTimes(n, arrivalTime, burstTime);

    return 0;
}
