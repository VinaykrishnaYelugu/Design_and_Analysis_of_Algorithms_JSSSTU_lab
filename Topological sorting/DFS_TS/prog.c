#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int V[200][200],visit[200],dfs_visit[200],order[200],cycle,v_count,top,a_count;

void dfs(int n,int x)
{
    if( visit[x]!=0 )
       return;
    printf("%d-Guss gayaa\n",x);
    int i,j;
    visit[x]=++v_count;
    dfs_visit[x]=1;
    for( i=0 ; i<n ; i++ )
    {
        a_count++;
        if( V[x][i]==1 )
        {
            if( visit[i]==0 )
                dfs(n,i);
            else if ( (visit[i]!=0)&&(dfs_visit[i]==1) )
                cycle=1;
        }
    }
    order[++top]=x;
    dfs_visit[x]=0;
}

void Topological_sort(int n)
{
   int i,v_count=0,flag,x=0;
   top=-1;
   i=x;
   do
   {
      if( visit[i]==0 )
      {
        cycle=0;
        flag=0;
        dfs(n,i);
        if( cycle==1 )
            { printf("\nTopological sorting not possible\n"); break; }
      }
      i = (i+1)%n;
   } while( i!=x );

   if( cycle==0 )
   {
      printf("\nTopological order :  \n");
      while( top>=0 )
      {
        printf("%d   ",order[top--]);
      }
      printf("\n\n");
   }
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
            dfs_visit[i]=0;
            for( j=0 ; j<n ; j++ )
            {
                if( i==j )
                   V[i][j]=0;
                else
                   V[i][j]=1;
            }
        }
        a_count=0;
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
        dfs_visit[i]=0;
        for( j=0 ; j<n ; j++ )
          fscanf(fp,"%d ",&V[i][j]);
     }
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