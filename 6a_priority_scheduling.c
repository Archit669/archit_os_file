#include<stdio.h>  
#include<stdlib.h>  

struct process {  
    int process_id;  
    int burst_time;  
    int priority;  
    int waiting_time;  
    int turnaround_time;  
};

void input_processes(struct process[], int);
void priority_scheduling(struct process[], int);
void find_waiting_time(struct process[], int, int[]);
void find_turnaround_time(struct process[], int, int[], int[]);
void find_average_time(struct process[], int);

int main()  
{  
    int n;  
    struct process proc[10];  
  
    printf("Enter the number of processes: ");  
    scanf("%d", &n);  
  
    input_processes(proc, n);

    priority_scheduling(proc, n);  

    return 0;  
}  

void input_processes(struct process proc[], int n)  
{  
    int i;  
    for(i = 0; i < n; i++)  
    {  
        printf("\nEnter the process ID: ");  
        scanf("%d", &proc[i].process_id);  
  
        printf("Enter the burst time: ");  
        scanf("%d", &proc[i].burst_time);  
  
        printf("Enter the priority: ");  
        scanf("%d", &proc[i].priority);  
    }  
}  

void find_waiting_time(struct process proc[], int n, int wt[])  
{  
    int i;  
    wt[0] = 0;  
  
    for(i = 1; i < n; i++)  
    {  
        wt[i] = proc[i - 1].burst_time + wt[i - 1];  
    }  
}  

void find_turnaround_time(struct process proc[], int n, int wt[], int tat[])  
{  
    int i;  
    for(i = 0; i < n; i++)  
    {  
        tat[i] = proc[i].burst_time + wt[i];  
    }  
}  

void find_average_time(struct process proc[], int n)  
{  
    int wt[10], tat[10], total_wt = 0, total_tat = 0, i;  
  
    find_waiting_time(proc, n, wt);  
    find_turnaround_time(proc, n, wt, tat);  
  
    printf("\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time");  
  
    for(i = 0; i < n; i++)  
    {  
        total_wt = total_wt + wt[i];  
        total_tat = total_tat + tat[i];  
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", proc[i].process_id, proc[i].burst_time, proc[i].priority, wt[i], tat[i]);  
    }  
  
    printf("\n\nAverage Waiting Time = %f", (float)total_wt/n);  
    printf("\nAverage Turnaround Time = %f\n", (float)total_tat/n);  
}  

void priority_scheduling(struct process proc[], int n)  
{  
    int i, j, pos;  
    struct process temp;  
    for(i = 0; i < n; i++)  
    {  
        pos = i;  
        for(j = i + 1; j < n; j++)  
        {  
            if(proc[j].priority < proc[pos].priority)  
                pos = j;  
        }  
  
        temp = proc[i];  
        proc[i] = proc[pos];  
        proc[pos] = temp;  
    }  
  
    find_average_time(proc, n);  
}
