#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE * fp;
    fp = fopen ("input.txt", "a+");
    int num1, num2, i, j, gcd;
    fscanf(fp,"%d", &num1);
    fscanf(fp,"%d", &num2);
    for(i=1; i <= num1 && i <= num2; ++i)
    {
        // gcd is greatest common divisor 
        if(num1%i==0 && num2%i==0)
            gcd = i;
    }
    fprintf(fp,"\n%d\n",gcd);
    int arr[gcd][gcd];

    //first element of each row is 1
    for(i=0;i<gcd;i++)
    {
        arr[i][0] = 1;
    }

    //last element of each row is 1
    for(i=0;i<gcd;i++)
    {
        arr[i][i]=1;
    }

    //populating pascal triangle
    for(i=1; i<gcd;i++)
    {
        for(j=1;j<i;j++)
        {
            arr[i][j]=arr[i-1][j]+arr[i-1][j-1];
        }
    }

    //printing pascal's triangle on console
    /*for(i=0;i<gcd;i++)
    {
        for(j=0;j<=i;j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }*/

    //writing pascal's triangle to the file
    for(i=0;i<gcd;i++)
    {
        for(j=0;j<=i;j++)
        {
            fprintf(fp,"%d ",arr[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;
}