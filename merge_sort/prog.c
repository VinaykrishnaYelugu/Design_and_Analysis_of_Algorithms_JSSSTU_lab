#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void w_arrange(int *arr1,int *arr2,int n1, int n2)
{
   int i,j,k=0;
   int *dup=(int *)malloc((n1+n2)*sizeof(int));
   i=0,j=0 ;
   while((i<n1)&&(j<n2)) 
   {
        *(dup+(k++))=*(arr1+(i++)); 
        *(dup+(k++))=*(arr2+(j++));
   }

   while( i<n1 )
      { *(dup+(k++))=*(arr1+(i++)); }

   while( j<n2 )
      { *(dup+(k++))=*(arr2+(j++)); }

   for(i=0 ; i<(n1+n2) ; i++ )
      *(arr1+i)=*(dup+i);
   free(dup);
}

void w_case(int *arr, int n)
{
    if( n>1 )
    {
        int *arr1=arr,*arr2=(arr+n/2),n1=(n/2),n2=(n-n/2);
        w_case(arr1,n1);
        w_case(arr2,n2);
        w_arrange(arr1,arr2,n1,n2);
    }
}

int sorting(int *arr1,int *arr2,int n1, int n2 )
{
   int i,j,k=0,count=0;
   int *dup=(int *)malloc((n1+n2)*sizeof(int));
   i=0,j=0 ;
   while((i<n1)&&(j<n2)) 
   {
      count++;
      if( *(arr1+i)<*(arr2+j) )
          { *(dup+k)=*(arr1+i); k++; i++; }
      else
          { *(dup+k)=*(arr2+j); k++; j++; }
   }

   while( i<n1 )
      { *(dup+(k++))=*(arr1+(i++)); }

   while( j<n2 )
      { *(dup+(k++))=*(arr2+(j++)); }

   for(i=0 ; i<(n1+n2) ; i++ )
      *(arr1+i)=*(dup+i);
   free(dup);
   return count;
}

int merge_sort(int * arr, int n )
{
    if( n>1 )
    {
        int *arr1=arr,*arr2=(arr+(n/2)),n1=n/2,n2=(n-n/2);
        return ( merge_sort( arr1,(n/2) )+merge_sort( arr2,(n-n/2) )+sorting(arr1,arr2,(n/2),(n-n/2)) );
    }
    return 0;
}

void analyze()
{
    srand(time(NULL));
    int *arr,i;
    FILE *fp1=fopen("best.txt","w"),*fp2=fopen("worst.txt","w"),*fp3=fopen("avg.txt","w");
    for( int n=2 ; n<=4096 ; n*=2 )
    {
        arr=(int *)malloc(n*sizeof(int));

        //best case
        for( i=0 ; i<n ; i++ )
            *(arr+i)=i+1;
        fprintf(fp1,"%d %d\n",n,merge_sort(arr,n));

        //worst case
        w_case(arr,n);
        fprintf(fp2,"%d %d\n",n,merge_sort(arr,n));

        //general case
        for( i=0 ; i<n ; i++ )
            *(arr+i)=rand()%n;
        fprintf(fp3,"%d %d\n",n,merge_sort(arr,n));

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
    merge_sort(arr,n);
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