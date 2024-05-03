#include <stdio.h>

struct Process {
  int id;
  int arrival_time;
  int burst_time;
  int completion_time;
  int turnaround_time;
  int waiting_time;
};

void calculate_times(struct Process processes[], int n) {
  int current_time = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (processes[j].arrival_time > processes[j + 1].arrival_time) {
        int temp = processes[j].arrival_time;
        processes[j].arrival_time = processes[j + 1].arrival_time;
        processes[j + 1].arrival_time = temp;
        temp = processes[j].id;
        processes[j].id = processes[j + 1].id;
        processes[j + 1].id = temp;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (current_time < processes[i].arrival_time) {
      current_time = processes[i].arrival_time;
    }
    processes[i].completion_time = current_time + processes[i].burst_time;
    processes[i].turnaround_time =
        processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time =
        processes[i].turnaround_time - processes[i].burst_time;
    current_time = processes[i].completion_time;
  }
}

void display_processes(struct Process processes[], int n) {
  printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround "
         "Time\tWaiting Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id,
           processes[i].arrival_time, processes[i].burst_time,
           processes[i].completion_time, processes[i].turnaround_time,
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
        printf("P%d", processes[i].id);
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
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  struct Process processes[n];

  printf("Enter arrival time and burst time for each process:\n");
  for (int i = 0; i < n; i++) {
    processes[i].id = i + 1;
    printf("Process %d: ", i + 1);
    scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
  }

  calculate_times(processes, n);

  display_processes(processes, n);

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

  return 0;
}
