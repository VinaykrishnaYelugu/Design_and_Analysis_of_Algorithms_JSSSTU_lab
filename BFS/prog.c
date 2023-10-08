#include<stdio.h>
#include<stdlib.h>

int *Q,r,f,*parent,*q_visit;
int cycle=0,v_count,a_count;

void bfs(int *M,int *visit,int n,int x)
{
   if( *(visit+x)!=0 )
       return;
   int i,j,flag;
   *(visit+x)=++v_count;
   printf("%d-%d  ",x,v_count);
   for( i=0 ; i<n ; i++ )
   {
      a_count++;
      if( *(M+n*x+i)==1 )
      {
         if( (*(visit+i)==0) && (*(q_visit+i)==0) )
                { *(q_visit+i)=1; *(parent+i)=x; *(Q+(++r))=i; }
         else if ( (*(visit+i) !=0)&&( i!=*(parent+x) ) )
            cycle=1;
      }
   }
   f++;
   if( f>r )
   {
     f=0,r=-1;
     return;
   }
   bfs(M,visit,n,*(Q+f));
}

void BFS(int * M,int *visit,int n, int sv)
{
    int x=sv,k=0;
    f=0,r=-1;
    v_count=0;
    do
    {
       if( *(visit+x)==0 )
       {
            printf("\nComponent-%d  =>",(++k));
            *(q_visit+x)=1; 
            *(Q+(++r))=x;
            cycle=0;
            bfs(M,visit,n,x);
            if( cycle==1 )
                printf("\nComponent-%d is cyclic",k);
            else
                printf("\nComponent-%d is acyclic\n",k);
       }
       if( x==sv )
       {
         if( v_count==n )
            printf("\nGraph is connecetd!!");
         else
            printf("\nComponents of graph are not connected!!\n");
       }
       if( v_count==n )
          break;
       x=(x+1)%n;
    } while ( x!=sv );
    free(M);
    free(visit);
    printf("\n");
}

void analyze()
{
    int *M,*visit,i,j,n,sv;
    FILE *fp=fopen("plot.txt","w");
    for( n=10 ; n<=200 ; n+=10 )
    {
        a_count=0;
        M = (int *)malloc((n*n)*sizeof(int));
        visit = (int *)malloc(n*sizeof(int));
        q_visit = (int *)malloc(n*sizeof(int));
        Q = (int *)malloc(n*sizeof(int));
        parent = (int *)malloc(n*sizeof(int));
        printf("Enter the adjacency matrix :  \n");
        for( i=0 ; i<n ; i++ )
        {
            *(visit+i)=0;
            *(Q+i)=0;
            *(parent+i)=0;
            *(q_visit+i)=0;
            for( j=0 ; j<n ; j++ )
            {
                if( i==j )
                   *(M+n*i+j)=0;
                else
                   *(M+n*i+j)=1;
            }
        }
        sv=0;
        BFS(M,visit,n,sv);
        fprintf(fp,"%d %d\n",n,a_count);
        free(M);
        free(visit);
    }
    fclose(fp);
    system("gnuplot>load command.txt");
}

void test()
{
    int *M,*visit,i,j,n,sv;
    FILE * p=fopen("data.txt","r");
    printf("Enter the number of vertices :  "); scanf("%d",&n);
    M = (int *)malloc((n*n)*sizeof(int));
    visit = (int *)malloc(n*sizeof(int));
    q_visit = (int *)malloc(n*sizeof(int));
    Q = (int *)malloc(n*sizeof(int));
    parent = (int *)malloc(n*sizeof(int));
    printf("Enter the adjacency matrix :  \n");
    for( i=0 ; i<n ; i++ )
    {
        *(visit+i)=0;
        *(Q+i)=0;
        *(parent+i)=0;
        *(q_visit+i)=0;
        for( j=0 ; j<n ; j++ )
        {
            fscanf(p,"%d",(M+n*i+j));
        }
    }
    fclose(p);
    printf("Enter the starting vertex : "); scanf("%d",&sv);
    BFS(M,visit,n,sv);    
    free(M);
    free(Q);
    free(parent);
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