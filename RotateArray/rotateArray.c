#include <stdio.h>
void printArr(int *a, int size)
{
    printf("Array = [ ");
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
    
    printArr(a, size);
    int swap;
    for (int i=0; i<k; i++)
    {
        swap = a[i];
        for (int j=k; j<size; j=j+k)
        {
            int temp = a[(j+k)%size];
            a[(j+k)%size] = swap;
            swap = temp;
        }
    }
    printArr(a, size);
}
