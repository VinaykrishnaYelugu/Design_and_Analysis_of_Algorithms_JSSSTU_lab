#include<stdio.h>
#include<stdlib.h>

int euclid(int m,int n)
{
   int r,count=0;
   while( n>0 )
   {
      count++;
      r = m%n;
      m = n;
      n = r;
   }
   printf("GCD by euclid method = %d\n",m);
   return count;
}

int consec(int m,int n)
{
   int count=0,min = ( m<n ) ? m : n ;

   while( 1 )
   {
      count++;
      if( m%min==0 )
      {
          count++;
          if( n%min==0 )
              break;
          min--;
      }
      else
          min--;
   } 
   printf("GCD by consecutive check method = %d\n",min );
   return count;
}

int modified(int m,int n)
{
    int temp,count=0;
    while( n>0 )
    {
        if ( n>m )
        {
            temp=m;
            m=n;
            n = temp;     
        }
        m=m-n;
        count++;
    }
    printf("GCD by modified euclid method = %d\n",m);
    return count;
}

void test()
{
    int m,n;
    printf("Enter two intgers :  ");
    scanf("%d",&m);
    scanf("%d",&n);
    printf("Euclid method => \n");
    euclid(m,n);
    printf("Consecutive method => \n");
    consec(m,n);
    printf("Modified euclid method => \n");
    modified(m,n);    
}

void analyze()
{
    int m,n,i,j,ch=1,k,mincount,maxcount,count;
    FILE *fp1,*fp2;
    while( ch<=3 )
    {
        for( i=10 ; i<=100 ; i+=10 )
        {
            mincount=10000;
            maxcount=0;
            for( j=2 ; j<=i ; j++ )
            {
                for( k=2 ; k<=i ; k++ )
                {
                    m=j;
                    n=k;
                    switch(ch)
                    {
                        case 1 : count=euclid(m,n); break;
                        case 2 : count=consec(m,n); break;
                        case 3 : count=modified(m,n); break;
                    }
                    if( count>maxcount )
                            maxcount=count;
                    if( count<mincount )
                            mincount=count;
                }
            }
                
            switch(ch)
            {
                case 1 : fp1=fopen("e_best.txt","a"); fp2=fopen("e_worst.txt","a"); break;
                case 2 : fp1=fopen("c_best.txt","a"); fp2=fopen("c_worst.txt","a"); break;
                case 3 : fp1=fopen("m_best.txt","a"); fp2=fopen("m_worst.txt","a"); break;
            }

            fprintf(fp1,"%d  %d\n",n,mincount);
            fprintf(fp2,"%d  %d\n",n,maxcount);
            fclose(fp1);
            fclose(fp2);
        }
        ch++;
    }
    system("gnuplot>load command.txt");
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
            case 2 : analyze();  break;
            case 3 : exit(0);
        }
    }
}