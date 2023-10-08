#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count;

void swap( int *a,int *b )
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int split_func(int * arr,int l,int r)
{
    int ip=l,fp=r+1,pivot=l;
    do
    {    
        do
        {
            ip++; count++;
            if( *(arr+ip)>=*(arr+pivot) )
                break;
        } while ( ip<r );
        do
        {
            fp--; count++;
            if( *(arr+fp)<=*(arr+pivot) )
                break;
        } while ( fp>l );

        if( ip<fp )
          swap((arr+ip),(arr+fp));
        
    } while (ip<fp);

    swap((arr+pivot),(arr+fp));
    return fp;
}

void quick_sort(int * arr,int l,int r)
{
    int n=r-l+1;
    if( n>1 )
    {
        count=0;
        int split=split_func(arr,l,r);
        int cnt1=count;
        count=0;
        quick_sort(arr,l,split-1);
        int cnt2=count;
        count=0;
        quick_sort(arr,split+1,r);
        int cnt3=count;
        count=cnt1+cnt2+cnt3;
    }
}

void analyze()
{
   srand(time(NULL));
   int *arr,i;
   FILE *fp1=fopen("best.txt","w"), *fp2=fopen("worst.txt","w"), *fp3=fopen("avg.txt","w");
   for( int n=10 ; n<=200 ; n+=10 )
   {
       arr=(int *)malloc(n*sizeof(int));
       
       //best case
       for( i=0 ; i<n ; i++ )
          *(arr+i)=10;
        count=0;
        quick_sort(arr,0,n-1);
        fprintf(fp1,"%d %d\n",n,count);
        
        
        //worst case
        for( i=0 ; i<n ; i++ )
           *(arr+i)=i;
        count=0;
        quick_sort(arr,0,n-1);
        fprintf(fp2,"%d %d\n",n,count);
        
        //general case
        for( i=0 ; i<n ; i++ )
           *(arr+i)=rand()%n;
        count=0;
        quick_sort(arr,0,n-1);
        fprintf(fp3,"%d %d\n",n,count);
        
        free(arr);
   }
   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
   system("gnuplot>load command.txt");
}

void test()
{
    int n,i,*arr;
    srand(time(NULL));
    printf("Enter number of elements :  ");
    scanf("%d",&n);
    arr = (int *)malloc(n*sizeof(int));
    printf("Enter array elements:  \n");
    for( i=0 ; i<n ; i++ )
       *(arr+i)=rand()%n;
    quick_sort(arr,0,n-1);
    printf("Sorted array :\n");
    for( i=0 ; i<n ; i++ )
        printf("%d   ",*(arr+i));
    printf("\n");
    free(arr);
}

void main()
{
    int ch;
    for( ; ; )
    {
        printf("Enter choice : "); scanf("%d",&ch);
        switch(ch)
        {
            case 1 : test(); break;
            case 2 : analyze(); break;
            case 3 : exit(0);
        }
    }
}