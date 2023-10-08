#include<stdio.h>
#include<stdlib.h>

int search(int * ar,int key,int n)
{
    int cnt=0;
    for(int i=0 ; i<n ; i++)
    {
        cnt++;
        if(ar[i]==key)
          {
            printf("Element found!! Position is %d\n",(i+1));
            return cnt;
          } 
    }
    printf("Element %d not found!!\n",key);
    return cnt;
}

void main()
{
    int key,i,av_cnt;
    FILE * fp1,* fp2,* fp3;

    fp1 = fopen("worst.txt","a");
    fp2 = fopen("best.txt","a");
    fp3 = fopen("average.txt","a");

    int * ar;
    for(int n=10; n<=100 ; n+=10)
    {
        ar = (int *)malloc(n*sizeof(int));
        for(int i=0 ; i<n ; i++)
            ar[i]=i;

       // WORST CASE
       ar[n-1]=-9999;
       key = ar[n-1];
       fprintf(fp1,"%d %d\n",n,search(ar,key,n));
    
       //BEST CASE
       key = ar[0];
       fprintf(fp2,"%d %d\n",n,search(ar,key,n));

       //AVERAGE CASE
       av_cnt=0;
       for(i=1 ; i<n-1 ; i++)
        {
            key=ar[i];
            av_cnt +=  search(ar,key,n);
        }   
        fprintf(fp3,"%d %f\n",n,((float)av_cnt/(n-2)));
        free(ar);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    system("gnuplot>load command.txt"); 
}