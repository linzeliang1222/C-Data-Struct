#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double * ptd;
    int max;
    int number;
    int i = 0;

    puts("What's the maximum number of type double entries?");
    if (scanf("%d", &max) != 1)
    {
        puts("Please input correctly entered -- bye.");
        exit(EXIT_FAILURE);
    }
    ptd = (double *) malloc(max * sizeof(double));
    if (ptd == NULL)
    {
        puts("Memory allocation failed, GoodBye.");
        exit(EXIT_FAILURE);
    }
    /* ptd现在指向有max个元素的数组 */
    puts("Enter the value (q to quit)");
    while (i < max && scanf("%lf", &ptd[i]) == 1)
        i++;
    printf("Here are your %d entries:\n", number = i);
    for (i = 0; i < max; i++)
    {
        printf("%7.2f ", ptd[i]);
        if (6 == i % 7)
            putchar('\n');
    }
    if (0 != i % 7)
        putchar('\n');
    puts("Done!");
    free(ptd);
    
    return 0;
}