#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N 5

HANDLE forks[N];

DWORD WINAPI philosopher(LPVOID num)
{
    int id = *(int *)num;

    printf("Philosopher %d is thinking\n", id);
    Sleep(1000);

    // Pick up left fork
    WaitForSingleObject(forks[id], INFINITE);
    // Pick up right fork
    WaitForSingleObject(forks[(id + 1) % N], INFINITE);

    printf("Philosopher %d is eating\n", id);
    Sleep(2000);

    printf("Philosopher %d finished eating\n", id);

    // Put down forks
    ReleaseMutex(forks[id]);
    ReleaseMutex(forks[(id + 1) % N]);

    return 0;
}

int main()
{
    HANDLE th[N];
    int i, id[N];

    // Create mutex for each fork
    for(i = 0; i < N; i++)
        forks[i] = CreateMutex(NULL, FALSE, NULL);

    // Create philosopher threads
    for(i = 0; i < N; i++)
    {
        id[i] = i;
        th[i] = CreateThread(NULL, 0, philosopher, &id[i], 0, NULL);
    }

    // Wait for all threads to finish
    WaitForMultipleObjects(N, th, TRUE, INFINITE);

    // Cleanup
    for(i = 0; i < N; i++)
    {
        CloseHandle(th[i]);
        CloseHandle(forks[i]);
    }

    return 0;
}