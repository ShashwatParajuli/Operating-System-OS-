#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes : ");
    scanf("%d", &n);

    printf("Enter number of resources : ");
    scanf("%d", &m);

    int allocation[n][m], request[n][m];
    int available[m];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d : ", i);

        for(j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    // Input Request Matrix
    printf("\nEnter Request Matrix:\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d : ", i);

        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);
    }

    // Input Available Resources
    printf("\nEnter Available Resources : ");

    for(i = 0; i < m; i++)
        scanf("%d", &available[i]);

    int work[m], finish[n];

    for(i = 0; i < m; i++)
        work[i] = available[i];

    // Initialize finish array
    for(i = 0; i < n; i++)
    {
        int zero = 1;

        for(j = 0; j < m; j++)
        {
            if(allocation[i][j] != 0)
            {
                zero = 0;
                break;
            }
        }

        if(zero)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    while(1)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > work[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    for(k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    found = 1;

                    printf("P%d is executed\n", i);
                }
            }
        }

        if(found == 0)
            break;
    }

    int deadlock = 0;

    for(i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            deadlock = 1;
            break;
        }
    }

    if(deadlock)
    {
        printf("\nSYSTEM IS IN DEADLOCK\n");
        printf("Deadlocked Processes are : ");

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
                printf("P%d ", i);
        }
    }
    else
    {
        printf("\nSYSTEM IS NOT IN DEADLOCK\n");
    }

    return 0;
}
