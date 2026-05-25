#include <stdio.h>
#define MAX 10
// GCD function
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
// LCM function
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
// Find hyperperiod
int find_hyperperiod(int Ti[], int n) {
    int hp = Ti[0];
    for (int i = 1; i < n; i++) {
        hp = lcm(hp, Ti[i]);
    }
    return hp;
}
int main() {
    int n;
    int Ci[MAX], Ti[MAX], Di[MAX];
    int remaining[MAX], next_arrival[MAX], abs_deadline[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    // Input
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Capacity (Ci): ");
        scanf("%d", &Ci[i]);
        printf("Period (Ti): ");
        scanf("%d", &Ti[i]);
        printf("Deadline (Di): ");
        scanf("%d", &Di[i]);
        remaining[i] = 0;
        next_arrival[i] = 0;
        abs_deadline[i] = 0;
    }
    int hyperperiod = find_hyperperiod(Ti, n);
    printf("\nHyperperiod = %d\n", hyperperiod);
    int current_process = -1;
    int start_time = 0;
    printf("\nExecution Timeline:\n");
    for (int t = 0; t < hyperperiod; t++) {
        // Step: Job arrival
        for (int i = 0; i < n; i++) {
            if (t == next_arrival[i]) {
                remaining[i] = Ci[i];
                abs_deadline[i] = t + Di[i];
                next_arrival[i] += Ti[i];
            }
        }
        // Step: Select process with earliest deadline
        int idx = -1;
        int min_deadline = 100000;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                if (abs_deadline[i] < min_deadline) {
                    min_deadline = abs_deadline[i];
                    idx = i;
                }
            }
        }
        // If process changes → print interval
        if (idx != current_process) {
            if (t > start_time) {
                if (current_process == -1)
                    printf("%d - %d : Idle\n", start_time, t);
                else
                    printf("%d - %d : P%d\n", start_time, t, current_process + 1);
            }
            start_time = t;
            current_process = idx;
        }
        // Execute
        if (idx != -1) {
            remaining[idx]--;
        }
    }
    // Print last interval
    if (current_process == -1)
        printf("%d - %d : Idle\n", start_time, hyperperiod);
    else
        printf("%d - %d : P%d\n", start_time, hyperperiod, current_process + 1);
    return 0;
}