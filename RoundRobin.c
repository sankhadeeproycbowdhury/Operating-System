#include <stdio.h>

typedef struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void roundRobin(Process processes[], int n, int quantum) {
    int remaining_time[n];
    int current_time = 0;
    int completed = 0;
    int time_quantum = quantum;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    while (completed < n) {
        int flag = 0;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                flag = 1;
                if (remaining_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    current_time += remaining_time[i];
                    processes[i].completion_time = current_time;
                    remaining_time[i] = 0;
                    completed++;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                }
            }
        }
        if (flag == 0) {
            current_time++;
        }
    }
}

void printTable(Process processes[], int n) {
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
    }
}

void printGanttChart(struct Process processes[], int n) {
    int i, j;
    
    printf("+");
    for(i = 0; i < n; i++) {
        for(j = 0; j < 5; j++)
            printf("-");
        printf("++");
        for(j = 0; j < 5; j++)
            printf("-");
        printf("+");
    }
    printf("\n|");

    for(i = 0; i < n; i++) {
        for(j = 0; j < 5; j++)
            printf(" ");
        printf("P%d", processes[i].pid);
        for(j = 0; j < 5; j++)
            printf(" ");
        printf("|");
    }
    printf("\n+");

    for(i = 0; i < n; i++) {
        for(j = 0; j < 5; j++)
            printf("-");
        printf("++");
        for(j = 0; j < 5; j++)
            printf("-");
        printf("+");
    }
    printf("\n");
}

int main() {
    int n, quantum, choice;
  printf("enter 1 for ccase 1\n");
  printf("enter 2 for case 2\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        n = 4;
        quantum = 2;
        Process processes[] = {{1, 0, 4}, {2, 1, 5}, {3, 2, 2}, {4, 3, 1}};
        roundRobin(processes, n, quantum);
        

        for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (processes[j].completion_time > processes[j+1].completion_time) {
                // Swap arr[j] and arr[j+1]
                int temp = processes[j].completion_time;
                processes[j].completion_time = processes[j+1].completion_time;
                processes[j+1].completion_time = temp;

                temp = processes[j].pid;
                processes[j].pid = processes[j+1].pid;
                processes[j+1].pid = temp;
            }
        }
    }

        printGanttChart(processes, n);

  float Avg_Waiting_time = 0;
  float Avg_TAT = 0;
  int scheduling_length = processes[n-1].completion_time - processes[0].arrival_time;

  for(int i = 0 ; i < n ;i++){
    Avg_Waiting_time += processes[i].waiting_time;
    Avg_TAT += processes[i].turnaround_time;
  }

  Avg_TAT = Avg_TAT / n;
  Avg_Waiting_time = Avg_Waiting_time / n;

  printf("Avg_Waiting_time: %f\nAvg_TAT: %f\nscheduling_length: %d" ,Avg_Waiting_time,Avg_TAT,scheduling_length); 
    } 
    else if (choice == 2) {
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        printf("Enter the time quantum for Round Robin: ");
        scanf("%d", &quantum);
        
        Process user_processes[n];
        for (int i = 0; i < n; i++) {
            printf("Enter arrival time and burst time for process %d: ", i + 1);
            scanf("%d", &user_processes[i].arrival_time);
            scanf("%d", &user_processes[i].burst_time);
            user_processes[i].pid = i + 1;
        }
        roundRobin(user_processes, n, quantum);
        printTable(user_processes, n);

        for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (user_processes[j].completion_time > user_processes[j+1].completion_time) {
                // Swap arr[j] and arr[j+1]
                int temp = user_processes[j].completion_time;
                user_processes[j].completion_time = user_processes[j+1].completion_time;
                user_processes[j+1].completion_time = temp;

                temp = user_processes[j].pid;
                user_processes[j].pid = user_processes[j+1].pid;
                user_processes[j+1].pid = temp;
            }
        }
    }

        printGanttChart(user_processes, n);

  float Avg_Waiting_time = 0;
  float Avg_TAT = 0;
  int scheduling_length = user_processes[n-1].completion_time - user_processes[0].arrival_time;

  for(int i = 0 ; i < n ;i++){
    Avg_Waiting_time += user_processes[i].waiting_time;
    Avg_TAT += user_processes[i].turnaround_time;
  }

  Avg_TAT = Avg_TAT / n;
  Avg_Waiting_time = Avg_Waiting_time / n;

  printf("Avg_Waiting_time: %f\nAvg_TAT: %f\nscheduling_length: %d" ,Avg_Waiting_time,Avg_TAT,scheduling_length); 
    } 
    else {
        printf("Invalid choice.\n");
    }

    return 0;
}
