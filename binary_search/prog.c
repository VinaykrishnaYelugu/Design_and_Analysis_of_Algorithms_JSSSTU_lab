#include<stdio.h>
#include<stdlib.h>

int binary_search(int *arr,int key,int low,int high,int ch)
{
     if( low>high )
      {
         if( ch==1 )
            return -1;
         if( ch==2 )
            return 0;
      }

     int x,mid=(low+high)/2 ;
     if( *(arr+mid)==key )
      {
           if( ch==1 )
              return mid;
           if( ch==2 )
              return 1;
      }
     else if( key < *(arr+mid) )
        high=mid-1;
     else
        low=mid+1;

     x=binary_search(arr,key,low,high,ch);
         
     if( ch==1 )
        return x;
     if( ch==2 )
        return (1+x);
}

void analyse()
{
   int *arr,i,count;
   FILE *fp1,*fp2,*fp3;
   fp1 = fopen("best.txt","w");
   fp2 = fopen("worst.txt","w");
   fp3 = fopen("avg.txt","w");
   for( int n=10 ; n<=200 ; n+=10 )
   {
      arr = (int *)malloc(n*sizeof(int));
      for( i=0 ; i<n ; i++ )
          *(arr+i)=i+1;

      //best case
      fprintf(fp1,"%d %d\n",n,binary_search(arr,*(arr+n-1),0,(n-1),2));

      //worst case
      fprintf(fp2,"%d %d\n",n,binary_search(arr,*(arr+(n-1)/2),0,(n-1),2));  

      //average case
      count=0;
      for( i=1 ; i<n-1 ; i++ )
      {
         if( i==(n-1)/2 )
             continue;
         count+=binary_search(arr,*(arr+i),0,(n-1),2);
      }
      fprintf(fp3,"%d %f\n",n,((float)count/(n-2)));
   
      free(arr);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    system("gnuplot>load command.txt");
} 
      
void test()
{
  int i,n,*arr,key;
  printf("Enter the number of elements :  ");
  scanf("%d",&n);
  arr = ( int *)malloc(n*sizeof(int));
  printf("Enter the array elements : \n");
  for( i=0 ; i<n ; i++ )
      *(arr+i)=(i+1);
  printf("Enter the key element : ");
  scanf("%d",&key);
  int pos=binary_search(arr,key,0,(n-1),1);
  if( pos==-1 )
     printf("Element %d not found\n",key);
  else
     printf("Element %d found!! Position=%d\n",key,(pos+1));  
  printf("\n");   
}

void main()
{
  int ch;
  for( ; ; )
  {
    printf("Enter the choice 1)  "); scanf("%d",&ch);
    switch(ch)
    {
       case 1 : test(); break;
       case 2 : analyse(); break;
       case 3 : exit(0);
    }
   }
}