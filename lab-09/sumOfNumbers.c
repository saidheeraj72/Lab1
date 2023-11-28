// Roll No.: CS21B2019
// Name: Devarakonda SLR Siddesh
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int n1, n2;
    int sum;
} args;

void *cumulative_sum(void *a)
{   
    args *temp = a;
    int s1 = temp->n2 * (temp->n2 + 1) / 2;
    int s2 = temp->n1 * (temp->n1 + 1) / 2;
    temp->sum = s1 - s2;
    return NULL;
}

int main()
{
    int n, tn, tot = 0, ret;

    printf("Enter the n value: ");
    scanf("%d", &n);

    printf("Enter the number of threads: ");
    scanf("%d", &tn);

    pthread_t threads[tn];
    args a[5];

    for(int i = 0; i < tn; i++) {
        a[i].n1 = i * (n / tn);
        a[i].n2 = (i + 1) * (n / tn);
        ret = pthread_create(&threads[i], NULL, &cumulative_sum, &a[i]);
    }

    for(int i = 0; i < tn; i++) {
        pthread_join(threads[i], NULL);
        tot += a[i].sum;
    }

    printf("Sum of first %d natural numbers: %d\n", n, tot);

    return 0;
}