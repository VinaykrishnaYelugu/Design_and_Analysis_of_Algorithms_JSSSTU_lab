#include<stdio.h>
#include<stdlib.h>

struct ITEM
{
    int weight,value;
};
typedef struct ITEM  it;

int V[500][500],bag[500],count;
it item[500];

int Max( int a,int b)
{
    return ( (a>b)? a : b );
}

void KNAPSACK_BAG(int n,int W)
{
   int i=n,j=W,k=-1;
   while( (i>=1)&&(j>=0) )
   {
      if( V[i-1][j] != V[i][j] )
      {
           bag[++k]=i;
           j = j-item[i].weight;
      }
       i--;
   }

   printf("KNAPSACK BAG =>\n");
   printf("S.no.  Weight   Value\n");
   while( k>=0 )
   {
      printf("%d      %d        %d\n",bag[k],item[bag[k]].weight,item[bag[k]].value);
      k--;
   }
}

void KNAPSACK_TABLE(int n,int W)
{
    int i,j,d;
    printf("Knapsack Table => \n");
    for( i=0 ; i<=n ; i++ )
    {
        for( j=0 ; j<=W ; j++ )
        {
            count++;
            if( i==0 || j==0 )
              {  V[i][j]=0;  printf("%d   ",V[i][j]); continue;   }

            d = j-item[i].weight ;
            if( d<0 )
               V[i][j] = V[i-1][j];
            else
                V[i][j] = Max( V[i-1][j],(V[i-1][d]+item[i].value) );

             printf("%d   ",V[i][j]);
        }
        printf("\n");
    }
}

void analyze()
{
   int i,j,n,W;
   FILE *fp=fopen("plot.txt","w");
   for( n=10 ; n<=200 ; n+=10 )
   {
        for( i=1 ; i<=n ; i++ )
        {
           item[i].weight = rand()%n ;
           item[i].value = rand()%n ;
        }
        W = n/2 ;
        count=0;
        KNAPSACK_TABLE(n,W);
        KNAPSACK_BAG(n,W);
        fprintf(fp,"%d %d\n",n,count);
   }
   fclose(fp);
   system("gnuplot>load command.txt");
}

void test()
{
   int i,j,n,W;
   printf("Enter the number of items :  "); scanf("%d",&n);
   for( i=1 ; i<=n ; i++ )
   {
      printf("\nItem-%d\n",i);
      printf("Enter weight :  "); scanf("%d",&item[i].weight);
      printf("Enter value  :  "); scanf("%d",&item[i].value);
   }
   printf("Enter the maximum capacity :  "); scanf("%d",&W);
   KNAPSACK_TABLE(n,W);
   KNAPSACK_BAG(n,W);
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
            case 3 : exit(0); break;
        }
    }
}