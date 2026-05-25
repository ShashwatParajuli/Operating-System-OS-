#include <stdio.h>

int main() {
    int n, i, time = 0, highest, completed = 0;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], rt[n], ct[n], wt[n], tat[n];
    int response[n], started[n];

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);

        rt[i] = bt[i];     // Remaining Time
        started[i] = 0;    // Process not started
    }

    while(completed < n) {
        highest = -1;
        for(i = 0; i < n; i++) {

            if(at[i] <= time && rt[i] > 0) {

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
            time++;   // CPU idle
        }
        else {

            // Response Time (first execution only)
            if(started[highest] == 0) {
                response[highest] = time - at[highest];
                avg_rt += response[highest];
                started[highest] = 1;
            }

            rt[highest]--;
            time++;

            if(rt[highest] == 0) {
                completed++;

                ct[highest] = time;
                tat[highest] = ct[highest] - at[highest];
                wt[highest] = tat[highest] - bt[highest];

                avg_wt += wt[highest];
                avg_tat += tat[highest];
            }
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tWT\tTAT\tRT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], ct[i],
               wt[i], tat[i], response[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Response Time = %.2f\n", avg_rt / n);

    return 0;
}