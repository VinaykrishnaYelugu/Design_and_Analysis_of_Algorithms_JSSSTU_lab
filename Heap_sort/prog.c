//Sucessful heap sort....
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int H[1500],a_count;

void swap( int *a,int *b )
{
   int temp=*a;
   *a=*b;
   *b=temp;
}

void Heapify(int n,int pi)
{
   if( (2*pi)<=n )
   {
        int ci,lc,rc;
        
        if( (2*pi)<n )  //2 children
            { a_count++;  ci = ( (H[2*pi]>H[2*pi+1]) ? (2*pi) : (2*pi+1) ); }
        else if( (2*pi)==n )
            { ci=(2*pi); }
        a_count++;
        if( H[pi]<H[ci] )
        {
            swap(&H[ci],&H[pi]);
            Heapify(n,ci);
        }
   }   
}

void Heap_sort(int n)
{
    for( int i=(n/2) ; i>=1 ; i-- )
         Heapify(n,i);
         
    int tnum=n;
    while( tnum>=1 )
    {
        swap(&H[1],&H[tnum--]);
        Heapify(tnum,1);
    }
    printf("Sorted array : \n");
    for( int i=1 ; i<=n ; i++ )
        printf("%d  ",H[i]);
}

void analyze()
{
   int i,n;
   FILE *fp1=fopen("HPbest.txt","w"),*fp2=fopen("HPworst.txt","w");
   for( n=100 ; n<=1000 ; n+=100 )
   {
    //best case
    for( i=1 ; i<=n ; i++ )
        H[i]=n-i;
    a_count=0;
    Heap_sort(n);
    fprintf(fp1,"%d %d\n",n,a_count);

    //worst case
    for( i=1 ; i<=n ; i++ )
        H[i]=i+1;
    a_count=0;
    Heap_sort(n);
    fprintf(fp2,"%d %d\n",n,a_count);
   }
   fclose(fp1);
   fclose(fp2);
   system("gnuplot>load command.txt");
}

void test()
{
    srand(time(NULL));
    int n,i;
    printf("Enter number os elements :  "); scanf("%d",&n);
    for( i=1 ; i<=n ; i++ )
        H[i]=rand()%n;
    a_count=0;
    Heap_sort(n);
    printf("\nA_count=%d\n",a_count);
}

void main()
{
    int ch;
    for( ; ; )
    {
        printf("Enter choice :  "); scanf("%d",&ch);
        switch(ch)
        {
            case 1 : test(); break;
            case 2 : analyze(); break;
            case 3 : exit(0);
        }
    }
}