#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void printResult(int processSize[], int n, int allocation[]) {
    printf("\n  %-12s %-15s %-10s\n", "Process No.", "Process Size", "Block No.");
    printf("  %-12s %-15s %-10s\n", "-----------", "------------", "---------");

    for (int i = 0; i < n; i++) {
        printf("  %-12d %-15d ", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%-10d\n", allocation[i] + 1);
        else
            printf("%-10s\n", "Not Allocated");
    }
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    printf("\nFIRST FIT ALLOCATION\n");

    int allocation[MAX_PROCESSES];
    int tempBlock[MAX_BLOCKS];

    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < m; i++)
        tempBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tempBlock[j] >= processSize[i]) {
                allocation[i] = j;
                tempBlock[j] -= processSize[i];
                break;
            }
        }
    }

    printResult(processSize, n, allocation);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    printf("\nBEST FIT ALLOCATION\n");

    int allocation[MAX_PROCESSES];
    int tempBlock[MAX_BLOCKS];

    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < m; i++)
        tempBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;

        for (int j = 0; j < m; j++) {
            if (tempBlock[j] >= processSize[i]) {
                if (bestIdx == -1 || tempBlock[j] < tempBlock[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            tempBlock[bestIdx] -= processSize[i];
        }
    }

    printResult(processSize, n, allocation);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    printf("\nWORST FIT ALLOCATION\n");

    int allocation[MAX_PROCESSES];
    int tempBlock[MAX_BLOCKS];

    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < m; i++)
        tempBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;

        for (int j = 0; j < m; j++) {
            if (tempBlock[j] >= processSize[i]) {
                if (worstIdx == -1 || tempBlock[j] > tempBlock[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            tempBlock[worstIdx] -= processSize[i];
        }
    }

    printResult(processSize, n, allocation);
}

int main() {
    int m, n;

    printf("CONTIGUOUS MEMORY ALLOCATION SIMULATOR\n");

    printf("\nEnter number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[MAX_BLOCKS];

    printf("Enter size of each block:\n");

    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    int processSize[MAX_PROCESSES];

    printf("Enter size of each process:\n");

    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    printf("\nBlock Sizes: ");

    for (int i = 0; i < m; i++)
        printf("%d ", blockSize[i]);

    printf("\nProcess Sizes: ");

    for (int i = 0; i < n; i++)
        printf("%d ", processSize[i]);

    printf("\n");

    firstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    worstFit(blockSize, m, processSize, n);

    return 0;
}