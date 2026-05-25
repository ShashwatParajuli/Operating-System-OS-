#include <stdio.h>

#define MAX 100

int main() {
    int n;
    int PID[MAX], AT[MAX], BT[MAX], TYPE[MAX];
    int CT[MAX], TAT[MAX], WT[MAX];
    int completed[MAX] = {0};
    float avg_TAT=0,avg_WT=0;

    int time = 0, done = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("PID AT BT TYPE: ");
        scanf("%d %d %d %d", &PID[i], &AT[i], &BT[i], &TYPE[i]);
    }

    while (done < n) {
        int idx = -1;

        // Step 1: Find System process (TYPE = 0)
        for (int i = 0; i < n; i++) {
            if (!completed[i] && TYPE[i] == 0 && AT[i] <= time) {
                if (idx == -1 || AT[i] < AT[idx])
                    idx = i;
            }
        }

        // Step 2: If no System process found → pick User process
        if (idx == -1) {
            for (int i = 0; i < n; i++) {
                if (!completed[i] && TYPE[i] == 1 && AT[i] <= time) {
                    if (idx == -1 || AT[i] < AT[idx])
                        idx = i;
                }
            }
        }

        // Step 3: If still no process → CPU idle
        if (idx == -1) {
            time++;
            continue;
        }

        // Execute process
        time += BT[idx];
        CT[idx] = time;
        TAT[idx] = CT[idx] - AT[idx];
        WT[idx] = TAT[idx] - BT[idx];

        completed[idx] = 1;
        done++;
    }

    // Output
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               PID[i], AT[i], BT[i], TYPE[i],
               CT[i], TAT[i], WT[i]);
    }

    for(int i=0;i<n;i++){
        avg_TAT+=TAT[i];
        avg_WT+=WT[i];
    }
    printf("Average TAT:%.2f ms\n",avg_TAT/n);
    printf("Average WT:%.2f ms\n",avg_WT/n);
    return 0;
}