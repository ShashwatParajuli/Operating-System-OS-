#include <stdio.h>
int main() {
    int n, tq, time = 0, i;
    int at[20], bt[20], rt[20];
    int ct[20], tat[20], wt[20];
    int queue[100], front = 0, rear = 0;
    int visited[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter AT and BT:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    queue[rear++] = 0;
    visited[0] = 1;

    while(front < rear) {
        int i = queue[front++];

        if(rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
        } else {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
        }

        for(int j = 0; j < n; j++) {
            if(at[j] <= time && visited[j] == 0) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if(rt[i] > 0) {
            queue[rear++] = i;
        }
    }

    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage WT = %.2f", total_wt/n);
    printf("\nAverage TAT = %.2f\n", total_tat/n);

    return 0;
}