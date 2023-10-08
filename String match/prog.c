#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a_count;

int String_match(char * text, char * pattern)
{
    int i,j,k,tl=strlen(text),pl=strlen(pattern);
    printf("%d-string guss gaya\n",pl);
    for( i=0 ; i<(tl-pl+1) ; i++ )
    {
        for( j=i,k=0 ; j<(i+pl) ; j++,k++ )
        {
            a_count++;
            if( *(text+j)!=*(pattern+k) )
                {  break; }
        }
        if( k==pl )
           return (i+1);
    }
    return -1;
}

void analyze()
{
    int pl,tl=1011,i;
    char *text=(char *)calloc(sizeof(char),tl), *pattern;
    FILE *fp1=fopen("best.txt","w"), *fp2=fopen("worst.txt","w");

    //text
    for( i=0 ; i<tl-1 ; i++ )
        *(text+i)='a';
    *(text+tl-1)=0;

    for( pl=11 ; pl<=1011 ; pl+=100 )
    {
      pattern=(char *)calloc(sizeof(char),pl);
      //pattern
      for( i=0 ; i<pl-1 ; i++ )
          *(pattern+i)='a';
      *(pattern+pl-1)=0;

       //text=aaaaa...aa pattern=aaaa...aa
       a_count=0;
       String_match(text,pattern);
       fprintf(fp1,"%d %d\n",pl,a_count);

       //text=aaaa...aa  pattern=aaa...aab
       *(pattern+pl-2)='b';
       a_count=0;
       String_match(text,pattern);
       fprintf(fp2,"%d %d\n",pl,a_count);
    }
    fclose(fp1);
    fclose(fp2);
    system("gnuplot>load command.txt");
}

void test()
{
    char *text=(char *)calloc(sizeof(char),250),*pattern=(char *)calloc(sizeof(char),250);
    printf("Enter the text : ");
    scanf("%s",text);
    printf("Enter the pattern :  ");
    scanf("%s",pattern);
    int n=strlen(text),m=strlen(pattern);
    int pos=String_match(text,pattern);
    if( pos==-1 )
       printf("Pattern not found in text!!\n");
    else 
       printf("Pattern found in text, position=%d\n",(pos));
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