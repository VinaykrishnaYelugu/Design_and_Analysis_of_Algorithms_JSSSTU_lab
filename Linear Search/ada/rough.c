#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void main()
{
    int *ar;
    for(int n=5; n<20; n++)
    {
       ar = (int *)malloc(n*sizeof(int));
       for(int i=0; i<n ; i++)
       {
        // srand(time(NULL));
         ar[i] = rand()%100;
         printf("%d  ",ar[i]);
       }
    printf("\n");
    }
}