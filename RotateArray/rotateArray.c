#include <stdio.h>
void printArr(int *a, int size, char *prefix)
{
    printf("%s -- Array = [ ", prefix);
    for (int i=0; i<size; i++)
        printf("%d ", a[i]);
    printf("]\n");
}
void main()
{
    int size = 10;
    int k = 3;
    int a[size];
    for (int i=1; i<=size; i++)
        a[i] = i;

    printArr(a, size, "Before");
    int swap;
    for (int i=0; i<k; i++)
    {
        swap = a[i];
        for (int j=i+k; j<size+k; j=j+k)
        {
            int temp = a[(j)%size];
            a[(j)%size] = swap;
            swap = temp;
        }
    }
    printArr(a, size, "After");
}
