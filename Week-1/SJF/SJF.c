#include <stdio.h>

int main() {
    int n, i, j, time;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], wt[n], tat[n], ct[n], pid[n];

    // Input
    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Sort by Arrival Time
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(at[i] > at[j]) {
                int temp;

                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    time = at[0];

    // SJF Scheduling
    for(i = 0; i < n; i++) {

        int pos = i;

        // Find shortest burst among arrived processes
        for(j = i + 1; j < n; j++) {
            if(at[j] <= time && bt[j] < bt[pos]) {
                pos = j;
            }
        }

        // Swap to current position
        int temp;

        temp = at[i]; at[i] = at[pos]; at[pos] = temp;
        temp = bt[i]; bt[i] = bt[pos]; bt[pos] = temp;
        temp = pid[i]; pid[i] = pid[pos]; pid[pos] = temp;

        if(time < at[i])
            time = at[i];

        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        time = ct[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Output
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}