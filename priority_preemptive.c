#include <stdio.h>

struct Process {
  int id;
  int arrival_time;
  int burst_time;
  int priority;
  int is_completed;
  int completion_time;
  int turnaround_time;
  int waiting_time;
};

void schedule(struct Process Processes[], int burst_times[], int n,
              int quanta) {
  int current_time = 0;
  int SL = 0;
  int processes_remaining = n;
  while (processes_remaining > 0) {
    int highest_priority = -1;
    int current_process = -1;
    for (int i = 0; i < n; i++) {
      if (Processes[i].is_completed == 0 &&
          Processes[i].arrival_time <= current_time) {
        if (highest_priority == -1 ||
            Processes[i].priority < highest_priority) {
          highest_priority = Processes[i].priority;
          current_process = i;
        }
      }
    }
    if (current_process != -1) {
      if (Processes[current_process].burst_time <= quanta) {
        current_time += Processes[current_process].burst_time;
        processes_remaining--;
        SL += quanta;
        printf("P%d |", Processes[current_process].id);
        Processes[current_process].is_completed = 1;
        Processes[current_process].completion_time = current_time;
        Processes[current_process].turnaround_time =
            Processes[current_process].completion_time -
            Processes[current_process].arrival_time;
        Processes[current_process].waiting_time =
            Processes[current_process].turnaround_time -
            burst_times[current_process];
      } else {
        current_time += quanta;
        printf("P%d |", Processes[current_process].id);
        SL += Processes[current_process].burst_time;
        Processes[current_process].burst_time -= quanta;
      }
    } else {
      current_time++;
    }
  }
  printf("\nScheduling length = %f\n", (float)n / SL);
}

void print_table(struct Process Processes[], int n) {
  float avg_WT = 0, avg_CT = 0, avg_TAT = 0;
  printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround "
         "Time\tWaiting Time\n");
  for (int i = 0; i < n; i++) {
    avg_WT += Processes[i].waiting_time;
    avg_CT += Processes[i].completion_time;
    avg_TAT += Processes[i].turnaround_time;
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", Processes[i].id,
           Processes[i].arrival_time, Processes[i].burst_time,
           Processes[i].completion_time, Processes[i].turnaround_time,
           Processes[i].waiting_time);
  }
  printf("average CT = %f,WT = %f,TAT = %f\n", avg_CT / n, avg_WT / n,
         avg_TAT / n);
}

int main() {
  int a;
  printf("Press 1 for case 1(hard coded values)\n");
  printf("Press 2 for case 1(user defined values)\n");
  scanf("%d", &a);
  if (a == 1) {
    struct Process Processes[5] = {{1, 3, 4, 3, 0},
                                   {2, 2, 5, 2, 0},
                                   {3, 6, 2, 5, 0},
                                   {4, 7, 3, 1, 0},
                                   {5, 1, 5, 4, 0}};
    int burst_times[5] = {4, 5, 2, 3, 5};
    schedule(Processes, burst_times, 5, 2);
    print_table(Processes, 5);
  } else if (a == 2) {
    int n, quanta;
    printf("enter number of processes\n");
    scanf("%d", &n);
    printf("enter time quanta\n");
    scanf("%d", &quanta);
    struct Process Processes[n];
    int burst_times[n];
    for (int i = 0; i < n; i++) {
      printf("enter arrival time,burst time and priority  for process %d\n", i);
      scanf("%d", &Processes[i].arrival_time);
      scanf("%d", &Processes[i].burst_time);
      burst_times[i] = Processes[i].burst_time;
      scanf("%d", &Processes[i].priority);
      Processes[i].id = i;
      Processes[i].is_completed = 0;
    }
    schedule(Processes, burst_times, n, quanta);
    print_table(Processes, n);
  }
  return 0;
}
