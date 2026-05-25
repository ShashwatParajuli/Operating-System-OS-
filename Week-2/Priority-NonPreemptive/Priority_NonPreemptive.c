#include <stdio.h>

int main() {
    int n, i, time = 0, highest, completed = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], ct[n], wt[n], tat[n];
    int done[n];

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);

        done[i] = 0; // Process not completed
    }

    while(completed < n) {
        highest = -1;

        for(i = 0; i < n; i++) {

            if(at[i] <= time && done[i] == 0) {

                if(highest == -1)
                    highest = i;

                else if(pr[i] < pr[highest])   // Higher priority = smaller number
                    highest = i;

                // Tie breaking using FCFS
                else if(pr[i] == pr[highest]) {

                    if(at[i] < at[highest])
                        highest = i;

                    else if(at[i] == at[highest] && i < highest)
                        highest = i;
                }
            }
        }

        if(highest == -1) {
            time++;   // CPU Idle
        }
        else {

            time += bt[highest];  // Execute process completely

            ct[highest] = time;
            tat[highest] = ct[highest] - at[highest];
            wt[highest] = tat[highest] - bt[highest];

            avg_wt += wt[highest];
            avg_tat += tat[highest];

            done[highest] = 1;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i],
               ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}