//PRIMS =>TO FIND MINIMUM SPANNING TREE
#include<stdio.h>
#include<stdlib.h>

int dist[200],flag[200],parent[200],M[200][200];

void display(int n,int x)
{
   int i;
   printf("curr=%d    \n",x);
   printf("\ndistance :  ");
   for( i=0 ; i<n ; i++ )
      printf("%d  ",dist[i]);
   printf("\nflags : ");
   for( i=0 ; i<n ; i++ )
      printf("%d  ",flag[i]);
   printf("\nparent : ");
   for( i=0 ; i<n ; i++ )
      printf("%d  ",parent[i]);
   printf("\n\n");
}

void mst(int n)
{
    int i,distance=0;
    for( i=1 ; i<n ; i++ )
    {
       printf("%d--%d => %d\n",i,parent[i],M[i][parent[i]]);
       distance+=M[i][parent[i]];
    }
    printf("Minimum distance=> %d\n",distance);
}

void prim(int n)
{
         display(n,0);
   dist[0]=0;
   parent[0]=-1;
   
   for( int i=0 ; i<n ; i++ )
   {
      int mini=__INT_MAX__;
      int u;
      //find min value
      for( int v=0 ; v<n ; v++ )
      {
         if ( (flag[v]==0) && (dist[v]<mini) )
          {
               u=v;
               mini=dist[v];
          }
      }
      printf("HI\n");

      //mark min node as true
      flag[u]=1;

      //adjacency matrix
      for( int v=0 ; v<n ; v++ )
      {
         if( M[u][v]!=-1 )
         {
            if( (flag[v]==0) && (M[u][v]<dist[v]) )
            {
               parent[v]=u;
               dist[v]=M[u][v];
            }
         }
      }
      display(n,u);
   }
   
}

void analyze()
{

}

void test()
{
   int n,i,j;
   FILE *fp = fopen("data.txt","r");
   printf("Enter number of vertices :  \n");
   scanf("%d",&n);
   printf("Enter the cost matrix : \n");
   for( i=0 ; i<n ; i++ )
   {
      dist[i]=__INT_MAX__;
      flag[i]=0;
      parent[i]=-1;  
      for( j=0 ; j<n ; j++ )
      {
         fscanf(fp,"%d ",&M[i][j]);
      }
   }
   fclose(fp);
   prim(n);
   mst(n);
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