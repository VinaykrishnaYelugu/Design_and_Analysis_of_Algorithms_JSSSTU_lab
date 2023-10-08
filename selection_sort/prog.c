#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int * a,int *b)
{
    int temp=*a;
    *a = *b;
    *b = temp;
}

int selection_sort(int * arr, int n)
{
    int i,j,count=0,flag,min;
    for( i=0 ; i<n-1 ; i++ )
    {
        min=i;
        for( j=i+1 ; j<n ; j++ )
        {
            count++;
            if( *(arr+j)<*(arr+min) )
               min=j; 
        }
        swap((arr+i),(arr+min));
    }
    return count;
}

void analyze()
{
    srand(time(NULL));
    int *arr,i;
    FILE *fp1=fopen("best.txt","w"),*fp2=fopen("worst.txt","w"),*fp3=fopen("avg.txt","w");
    for( int n=10 ; n<=200 ; n+=10 )
    {
        arr=(int *)malloc(n*sizeof(int));

        //best case
        for( i=0 ; i<n ; i++ )
            *(arr+i)=i+1;
        fprintf(fp1,"%d %d\n",n,selection_sort(arr,n));

        //worst case
        for( i=0 ; i<n ; i++ )
            *(arr+i)=n-i;
        fprintf(fp2,"%d %d\n",n,selection_sort(arr,n));

        //general case
        for( i=0 ; i<n ; i++ )
            *(arr+i)=rand()%n;
        fprintf(fp3,"%d %d\n",n,selection_sort(arr,n));

        free(arr);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    system("gnuplot>load command.txt");
}

void test()
{
    srand(time(NULL));
    int *arr,n,i;
    printf("Enter the number of elements :  "); scanf("%d",&n);
    arr = (int *)malloc(n*sizeof(int));
    for( i=0 ; i<n ; i++ )
       *(arr+i)=rand()%n;
    int x=selection_sort(arr,n);
    printf("\nSorted array : \n");
    for( i=0 ; i<n ; i++ )
       printf("%d  ",*(arr+i));
    printf("\n");
}

void main()
{
    int ch;
    for( ; ; )
    {
        printf("Enter the choice :  "); scanf("%d",&ch);
        switch(ch)
        {
            case 1 : test(); break;
            case 2 : analyze(); break;
            case 3 : exit(0);
        }
    }
}