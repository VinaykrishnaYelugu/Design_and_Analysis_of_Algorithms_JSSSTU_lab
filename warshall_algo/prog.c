#include<stdio.h>
#include<stdlib.h>

int warshall_algo(int *M,int n)
{
    int i,j,k,count=0;
    for( k=0 ; k<n ; k++ )
      for( i=0 ; i<n ; i++ )
         for( j=0 ; j<n ; j++ )
            { count++; *(M+n*i+j)=*(M+n*i+j)||(*(M+n*i+k) && *(M+n*k+j)); }
    return count;
}

void analyze()
{
   int i,j,*M;
   FILE *fp=fopen("plot.txt","w");
   for( int n=10 ; n<=200 ; n+=10 )
   {
      M = ( int *)malloc((n*n)*sizeof(int));
      for( i=0 ; i<n ; i++ )
      {
        for( j=0 ; j<n ; j++ )
        {
            if( i==j )
               *(M+n*i+j)=0;
            else
              *(M+n*i+j)=1;
        }
      }
      fprintf(fp,"%d %d\n",n,warshall_algo(M,n));
      free(M);
   }
   fclose(fp);
   system("gnuplot>load command.txt");
}

void test()
{
    int i,j,n,*M;
    printf("Enter number of vertices :  ");
    scanf("%d",&n);
    M = (int *)malloc(sizeof(int)*(n*n));
    printf("Enter the adjacecymatrix : \n");
    for( i=0 ; i<n ; i++ )
       for( j=0 ; j<n ; j++ )
           scanf("%d",(M+n*i+j));
    warshall_algo(M,n);
    printf("M3 => \n");
    for( i=0 ; i<n ; i++ )
     {
        for( j=0 ; j<n ; j++ )
           printf("%d ",*(M+n*i+j));
        printf("\n");
     } 

}

void main()
{
    int ch;
    for( ; ; )
    {
        printf("Enter choice :  ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1 : test(); break;
            case 2 : analyze(); break;
            case 3 : exit(0);
        }
    }
}