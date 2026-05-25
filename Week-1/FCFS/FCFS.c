#include <stdio.h>

int main() {
    int n, i, j;
    int at[20], bt[20], ct[20], wt[20], tat[20], pid[20];
    float twt = 0, ttat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);


    // Input
    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Sorting by Arrival Time (Bubble Sort)
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(at[j] > at[j + 1]) {

                // Swap Arrival Time
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap Burst Time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap Process ID
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    // First Process
    ct[0] = at[0] + bt[0];
    wt[0] = 0;
    tat[0] = bt[0];

    // Remaining Processes
    for(i = 1; i < n; i++) {

        if(ct[i - 1] < at[i]) {
            ct[i] = at[i] + bt[i];
            wt[i] = 0;
        } else {
            ct[i] = ct[i - 1] + bt[i];
            wt[i] = ct[i - 1] - at[i];
        }

        tat[i] = bt[i] + wt[i];
    }

    // Calculate averages
    for(i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    printf("\n\nPROCESS\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", twt/n);
    printf("\nAverage Turnaround Time = %.2f\n", ttat/n);

    return 0;
}