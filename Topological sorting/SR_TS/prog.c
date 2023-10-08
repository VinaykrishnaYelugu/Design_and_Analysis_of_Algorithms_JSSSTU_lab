#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int V[200][200],visit[200],indegree[200],order[200],top,a_count;

void Indegree_func(int n)
{
    int i,j;
    for( i=0 ; i<n ; i++ )
        for( j=0 ; j<n ; j++ )
            if( V[i][j]==1 )
                indegree[j]++;
}

int vertex(int sv,int n)
{
    int i=sv;
    do
    {
        a_count++;
        if( (indegree[i]==0) && (visit[i]==0) )
           return i;
        i=(i+1)%n;
    } while ( i!=sv );
    return -1;
}

void Topological_sort(int n)
{
   int i,sv=0,x;
   top=-1;
   while(1)
   {
        x = vertex(sv,n);
        if( x==-1 )
           break; 
        visit[x]=1;
        order[++top]=x;
        for( i=0 ; i<n ; i++ )
        {
            a_count++;
            if( V[x][i]==1 )
              indegree[i]--;
        }
        x=(x+1)%n;
   }
   if( top==n-1 )
   {
      printf("Topological order :  ");
      i=0;
      while( i<=top )
      {
        printf("%d  ",order[i++]);
      }
      printf("\n\n");
   }
   else
      printf("Topological sorting not possible\n\n");
}

void analyze()
{
    int n,j,i;
    FILE *fp = fopen("plot.txt","w");
    for ( n=10 ; n<=200 ; n+=10 )
    {
        printf("Enter adjacency matrix :  =>\n");
        for( i=0 ; i<n ; i++ )
        {
            visit[i]=0;
            for( j=0 ; j<n ; j++ )
            {
                if( j==(i+1) )
                   V[i][j]=1;
                else
                   V[i][j]=0;

                if( i==0 )
                   V[i][n-1]=1;
            }
        }
        a_count=0;
        Indegree_func(n);
        Topological_sort(n);
        fprintf(fp,"%d %d\n",n,a_count);
    }
    fclose(fp);
    system("gnuplot>lod command.txt");
}

void test()
{
    int n,j,i;
    FILE * fp = fopen("data.txt","r");
    printf("Enter number of vertices :  "); scanf("%d",&n);
    printf("Enter adjacency matrix :  =>\n");
    for( i=0 ; i<n ; i++ )
     {
        visit[i]=0;
        for( j=0 ; j<n ; j++ )
          fscanf(fp,"%d ",&V[i][j]);
     }
    Indegree_func(n);
    Topological_sort(n);
    fclose(fp);
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