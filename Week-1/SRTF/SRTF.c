#include <stdio.h>

int main() {
    int n, i, time = 0, smallest, completed = 0;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], ct[n], wt[n], tat[n];
    int response[n], started[n];

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rt[i] = bt[i];       // Remaining time
        started[i] = 0;      // Not started yet
    }

    while(completed < n) {
        smallest = -1;

        for(i = 0; i < n; i++) {

            if(at[i] <= time && rt[i] > 0) {

                if(smallest == -1)
                    smallest = i;

                else if(rt[i] < rt[smallest])
                    smallest = i;

                // Tie case (FCFS rule)
                else if(rt[i] == rt[smallest]) {

                    if(at[i] < at[smallest])
                        smallest = i;

                    else if(at[i] == at[smallest] && i < smallest)
                        smallest = i;
                }
            }
        }

        if(smallest == -1) {
            time++;  // CPU idle
        }
        else {

            // Calculate Response Time (only first time)
            if(started[smallest] == 0) {
                response[smallest] = time - at[smallest];
                avg_rt += response[smallest];
                started[smallest] = 1;
            }

            rt[smallest]--;
            time++;

            if(rt[smallest] == 0) {
                completed++;
                ct[smallest] = time;
                tat[smallest] = ct[smallest] - at[smallest];
                wt[smallest] = tat[smallest] - bt[smallest];

                avg_wt += wt[smallest];
                avg_tat += tat[smallest];
            }
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i],
               wt[i], tat[i], response[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Response Time = %.2f\n", avg_rt / n);

    return 0;
}