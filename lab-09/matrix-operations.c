// Roll No.: CS21B2019
// Name: Devarakonda SLR Siddesh
#include <stdio.h>
#include <pthread.h>

int m1[3][3], m2[3][3];
int a[3][3], s[3][3], m[3][3];

void *operations(void *arg)
{   
    int t = (long int)arg;
    if(t == 0 || t == 1)
    {   
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            {   
                if(t == 0)
                    a[i][j] = m1[i][j] + m2[i][j];
                else
                    s[i][j] = m1[i][j] - m2[i][j];
            }
    }
    else if(t == 2)
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            {   
                m[i][j] = 0;
                for(int k = 0; k < 3; k++)
                    m[i][j] += m1[i][k] * m2[k][j];
            }
    }
    else
        printf("Invalid argument passed to thread!\n");

    return NULL;
}

int main()
{
    int ret;
    pthread_t threads[3];
    char *ops = "+-*";

    printf("Enter the elements of the first matrix (M1) : \n");
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            scanf("%d", &m1[i][j]);
    
    printf("Enter the elements of the second matrix (M2) : \n");
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            scanf("%d", &m2[i][j]);

    printf("\nM1 : ");
    for(int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
            printf("%d ", m1[i][j]);
        printf("\n");
    }
    printf("\nM2 : ");
    for(int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
            printf("%d ", m2[i][j]);
        printf("\n");
    }

    for(long int i = 0; i < 3; i++)
    {
        ret = pthread_create(&threads[i], NULL, operations, (void *)i);
    }

    for(int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    for(int k = 0; k < 3; k++)
    {
        printf("\nM1 %c M2 = \n", ops[k]);
        for(int i = 0; i < 3; i++)
        {   
            for(int j = 0; j < 3; j++)
                printf("%d ", (k == 0) ? a[i][j] : (k == 1) ? s[i][j] : m[i][j]);
            printf("\n");
        }
    }

    return 0;
}