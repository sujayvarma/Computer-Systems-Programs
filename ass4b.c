#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

char *  getReverse(char input[])
{
    char * start = &input[0];
    int n = strlen(input);
    char * end   = &input[n-1];
    char ch;
    for(int i =0; i <n/2;i++)
    {
        ch = *start;
        *start = *end;
        *end = ch;
        start++;
        end--;
    }

    return &input[0];
}

char * removeDup( char *str ) 
{
    for ( char *p = str, *q = str; *q++; )
    {
        if ( *p != *q ) *++p = *q;
    }

    return &str[0];
}

int main()
{
    int n;
    printf("Enter the length of string:");
    scanf("%d",&n);
    char input[2*n], reverse[n];
    printf("Enter the string:");
    scanf("%s", input);

    //Remove double letters;
    removeDup( input );

    strcpy(reverse,input);
   
    getReverse(reverse);// get reverse of string
    printf("Reversed output: %s\n", reverse);
    char * ptr1 = &input[strlen(input)-1];
    char * ptr2 = &reverse[0];
    char ch;

    //concatenate reverse
    for (int i=0; i<strlen(input); i++)
    {
        ch = * ptr2;
        ptr1++;
        *ptr1 = ch;
        ptr2++;
    }

    removeDup( input ); // removing double letters which have arised due to concatenation
    
    printf("Concatenated output: %s\n", input);

    return 0;
}