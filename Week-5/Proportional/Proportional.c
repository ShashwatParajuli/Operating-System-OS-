#include <stdio.h>

#define MAX 10

int main() {
    int n, i;
    int burst_time[MAX], remaining_time[MAX], weight[MAX];
    int completed[MAX] = {0};
    int total_weight = 0;
    int TIME_QUANTUM;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    printf("Enter weight for each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
        total_weight += weight[i];
    }

    printf("Enter TIME_QUANTUM: ");
    scanf("%d", &TIME_QUANTUM);

    int unfinished = n;

    while (unfinished > 0) {
        for (i = 0; i < n; i++) {

            if (!completed[i] && remaining_time[i] > 0) {

                // calculate proportional time slice
                int time_slice = (weight[i] * TIME_QUANTUM) / total_weight;

                if (time_slice <= 0)
                    time_slice = 1; // ensure minimum execution

                printf("P%d->%d\n", i, time_slice);

                // run process
                remaining_time[i] -= time_slice;

                if (remaining_time[i] <= 0) {
                    printf("Process P%d completed\n", i);
                    completed[i] = 1;
                    unfinished--;

                    // update total weight
                    total_weight -= weight[i];
                }
            }
        }
    }

    printf("All processes completed.\n");
    return 0;
}