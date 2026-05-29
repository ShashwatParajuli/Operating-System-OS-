#include <stdio.h>
#include <string.h>

#define MAX 50

int present(int f[], int n, int p) {
    for (int i = 0; i < n; i++)
        if (f[i] == p) return i;
    return -1;
}

void show(int f[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        f[i] == -1 ? printf("- ") : printf("%d ", f[i]);
    printf("]");
}

void fifo(int p[], int n, int nf) {
    int f[10], front = 0, faults = 0;
    memset(f, -1, sizeof(f));

    printf("\nFIFO\n");

    for (int i = 0; i < n; i++) {
        printf("%d -> ", p[i]);

        if (present(f, nf, p[i]) != -1)
            printf("HIT ");
        else {
            f[front] = p[i];
            front = (front + 1) % nf;
            faults++;
            printf("FAULT ");
        }

        show(f, nf);
        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

void lru(int p[], int n, int nf) {
    int f[10], used[10], faults = 0;
    memset(f, -1, sizeof(f));
    memset(used, -1, sizeof(used));

    printf("\nLRU\n");

    for (int i = 0; i < n; i++) {
        int idx = present(f, nf, p[i]);

        printf("%d -> ", p[i]);

        if (idx != -1) {
            used[idx] = i;
            printf("HIT ");
        } else {
            int r = -1;

            for (int j = 0; j < nf; j++)
                if (f[j] == -1) {
                    r = j;
                    break;
                }

            if (r == -1) {
                r = 0;
                for (int j = 1; j < nf; j++)
                    if (used[j] < used[r]) r = j;
            }

            f[r] = p[i];
            used[r] = i;
            faults++;
            printf("FAULT ");
        }

        show(f, nf);
        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

void optimal(int p[], int n, int nf) {
    int f[10], faults = 0;
    memset(f, -1, sizeof(f));

    printf("\nOPTIMAL\n");

    for (int i = 0; i < n; i++) {
        printf("%d -> ", p[i]);

        if (present(f, nf, p[i]) != -1)
            printf("HIT ");
        else {
            int r = -1;

            for (int j = 0; j < nf; j++)
                if (f[j] == -1) {
                    r = j;
                    break;
                }

            if (r == -1) {
                int far = -1;

                for (int j = 0; j < nf; j++) {
                    int next = n;

                    for (int k = i + 1; k < n; k++)
                        if (p[k] == f[j]) {
                            next = k;
                            break;
                        }

                    if (next > far) {
                        far = next;
                        r = j;
                    }
                }
            }

            f[r] = p[i];
            faults++;
            printf("FAULT ");
        }

        show(f, nf);
        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

int main() {
    int p[MAX], n, nf;

    printf("Enter frames: ");
    scanf("%d", &nf);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter pages:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    fifo(p, n, nf);
    lru(p, n, nf);
    optimal(p, n, nf);

    return 0;
}