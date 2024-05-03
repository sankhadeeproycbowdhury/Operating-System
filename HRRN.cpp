#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid;            // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time
    int completion_time;
    float response_ratio;
    int final_burst_time;
    int turn_around_time;
    int waiting_time;

    Process(int id, int at, int bt)
        : pid(id), arrival_time(at), burst_time(bt), completion_time(0), response_ratio(0.0f), final_burst_time(bt), turn_around_time(0), waiting_time(0)  {}
};

void calculate_response_ratio(std::vector<Process>& processes) {
    int total_burst_time = 0;
    for (const auto& process : processes) {
        total_burst_time += process.burst_time;
    }

    for (auto& process : processes) {
        process.response_ratio = 1 + (float)(total_burst_time - process.arrival_time) / process.burst_time;
    }
}

void hrrn_scheduling(std::vector<Process>& processes) {
    int current_time = 0;
    int completed_processes = 0;
    float max_response_ratio;
    int next_process_index;

    std::cout << "PID\tArrivalTime\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime\n";

    while (completed_processes < processes.size()) {
        max_response_ratio = -1; // Initialize to a negative value
        next_process_index = -1;

        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time <= current_time && processes[i].burst_time > 0) {
                if (processes[i].response_ratio > max_response_ratio) {
                    max_response_ratio = processes[i].response_ratio;
                    next_process_index = i;
                }
            }
        }

        if (next_process_index == -1) {
            current_time++;
            continue;
        }

        processes[next_process_index].completion_time = current_time + processes[next_process_index].burst_time;
         processes[next_process_index].turn_around_time = processes[next_process_index].completion_time - processes[next_process_index].arrival_time;
          processes[next_process_index].waiting_time = processes[next_process_index].turn_around_time - processes[next_process_index].burst_time;
        processes[next_process_index].burst_time = 0;
        completed_processes++;

        std::cout << processes[next_process_index].pid << "\t\t"
                  << processes[next_process_index].arrival_time << "\t\t"
                  << processes[next_process_index].final_burst_time << "\t\t"
                  << processes[next_process_index].completion_time << "\t\t"
                  << processes[next_process_index].turn_around_time << "\t\t"
                  << processes[next_process_index].waiting_time << "\n";

        current_time = processes[next_process_index].completion_time;
    }
}


void printGanttChart(std::vector<Process>& processes) {
    int i, j;
    int n = processes.size();
    
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
    int n;
    int choice;
    printf("enter 1 for ccase 1\n");
    printf("enter 2 for case 2\n");
    scanf("%d", &choice);

    if(choice == 1){
     n = 5;
     std::vector<Process> processes;
     int at, bt;
     at = 1;
     bt = 3;
     processes.emplace_back(1, at, bt);
     at = 3;
     bt = 6;
     processes.emplace_back(2, at, bt);
     at = 5;
     bt = 8;
     processes.emplace_back(3, at, bt);
     at = 7;
     bt = 4;
     processes.emplace_back(4, at, bt);
     at = 8;
     bt = 5;
     processes.emplace_back(5, at, bt);

    calculate_response_ratio(processes);
    hrrn_scheduling(processes);
    
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

    printGanttChart(processes);

    float Avg_Waiting_time = 0;
    float Avg_TAT = 0;
    int scheduling_length = processes[n-1].completion_time - processes[0].arrival_time;

  for(int i = 0 ; i < n ;i++){
    Avg_Waiting_time += processes[i].waiting_time;
    Avg_TAT += processes[i].turn_around_time;
  }

  Avg_TAT = Avg_TAT / n;
  Avg_Waiting_time = Avg_Waiting_time / n;

  printf("Avg_Waiting_time: %f\nAvg_TAT: %f\nscheduling_length: %d" ,Avg_Waiting_time,Avg_TAT,scheduling_length);
    
    }
    else if(choice == 2){
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes;

    std::cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        int at, bt;
        std::cout << "Process " << i + 1 << ":\n";
        std::cout << "Arrival time: ";
        std::cin >> at;
        std::cout << "Burst time: ";
        std::cin >> bt;
        processes.emplace_back(i + 1, at, bt);
    }

    calculate_response_ratio(processes);
    hrrn_scheduling(processes);
    
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

    printGanttChart(processes);

    float Avg_Waiting_time = 0;
    float Avg_TAT = 0;
    int scheduling_length = processes[n-1].completion_time - processes[0].arrival_time;

  for(int i = 0 ; i < n ;i++){
    Avg_Waiting_time += processes[i].waiting_time;
    Avg_TAT += processes[i].turn_around_time;
  }

  Avg_TAT = Avg_TAT / n;
  Avg_Waiting_time = Avg_Waiting_time / n;

  printf("Avg_Waiting_time: %f\nAvg_TAT: %f\nscheduling_length: %d" ,Avg_Waiting_time,Avg_TAT,scheduling_length);
}
else{
    printf("Wrong Choice\n");
}
    return 0;
}
