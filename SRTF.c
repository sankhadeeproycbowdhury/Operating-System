#include<stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void SRTF(struct Process processes[], int n) {
    int remaining_time[n];
    int smallest, time = 0, completed = 0, min = 9999;

    // Initialize remaining_time array
    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].burst_time;

    while (completed != n) {
        smallest = -1;
        min = 9999;

        // Find process with smallest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && remaining_time[i] < min && remaining_time[i] > 0) {
                min = remaining_time[i];
                smallest = i;
            }
        }

        if (smallest == -1) {
            time++;
            continue;
        }

        // Reduce remaining time of the smallest process
        remaining_time[smallest]--;

        // Update time
        time++;

        // If process is completed
        if (remaining_time[smallest] == 0) {
            completed++;
            processes[smallest].completion_time = time;
            processes[smallest].turnaround_time = processes[smallest].completion_time - processes[smallest].arrival_time;
            processes[smallest].waiting_time = processes[smallest].turnaround_time - processes[smallest].burst_time;
        }
    }
}

void printTable(struct Process processes[], int n) {
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
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
    int n, choice;
  printf("enter 1 for ccase 1\n");
  printf("enter 2 for case 2\n");
    scanf("%d", &choice);

    if (choice == 1) {
        // Hardcoded values
        n = 4; // Number of processes
        struct Process processes[] = {{1, 0, 5}, {2, 1, 3}, {3, 2, 8}, {4, 3, 6}};
        SRTF(processes, n);
        printTable(processes, n);

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
        // User input values
        printf("Enter number of processes: ");
        scanf("%d", &n);

        struct Process processes[n];

        // Input process details
        for (int i = 0; i < n; i++) {
            processes[i].pid = i + 1;
            printf("Enter arrival time and burst time for process %d: ", i + 1);
            scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        }

        // Apply SRTF algorithm
        SRTF(processes, n);

        // Print table
        printTable(processes, n);

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
    else {
        printf("Invalid choice.\n");
    }



    return 0;
}
