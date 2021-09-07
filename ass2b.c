#include<stdio.h>
#include<stdlib.h>

int numOfDigits(int num)
{
    int digit = 0;
    if(num)
    {
        digit++;
    }
    num = num/10;
    while(num)
    {
        digit++;
        num = num/10;
    }
    return digit;
}

int getLastDigit(int num)
{
    return num % 10;
}

int intToBinary(int num, int * arr, int * ptr)
{
    int count, val;
    for (count = 3; count >= 0; count--)
    {
        val = num >> count;
        if( val & 1)
            *ptr = 1;
        else
            *ptr = 0;
        ptr++;
    }

}

int doNormalAddition(int a[],int b[], int sum[], int n)
{
    int carry=0, val;
    for(int i=n-1;i>=0;i--)
    {
        val = a[i]+b[i]+carry;
        switch (val)
        {
        case 0:
            sum[i] = 0;
            carry = 0;
            break;
        case 1:
            sum[i] = 1;
            carry = 0;
            break;
        case 2:
            sum[i] = 0;
            carry = 1;
            break;
        case 3:
            sum[i] = 1;
            carry = 1;
            break;
        default:
            break;
        }
    }
    return carry;
}

int getDec(int a, int b, int c, int d)
{
    int val = a *8 +b *4 +c *2 +d *1;
    return val;
}

int main()
{
    int num1,num2, bits,n1,n2,testCases;
    printf("Number of test cases:");
    scanf("%d",&testCases);
    while(testCases)
    {
        printf("\nFirst number:");
        scanf("%d",&num1);
        printf("\nSecond number:");
        scanf("%d",&num2);
        n1=num1;
        n2=num2;
        int digits = numOfDigits(num1);
        int arrSize = 4*digits;
        int arr1[arrSize], arr2[arrSize],tempArr1[arrSize],tempArr2[arrSize];
        int temparrSize = arrSize;
        int *ptr1 = &arr1[arrSize-4];//pointer to fourth last element
        int ldigit = getLastDigit(num1);
        while (num1)
        {

            num1 = num1/10;
            intToBinary(ldigit,arr1,ptr1);
            ptr1 = ptr1-4;
            ldigit = getLastDigit(num1);
        }
        for (int i = 0; i < arrSize; i++)
        {
            tempArr1[i] = arr1[i];
        }
            

        int *ptr2 = &arr2[arrSize-4];//pointer to fourth last element
        ldigit = getLastDigit(num2);
        while (num2)
        {

            num2 = num2/10;
            /* code */
            intToBinary(ldigit,arr2,ptr2);
            ptr2 = ptr2-4;
            ldigit = getLastDigit(num2);
        }
        for (int i = 0; i < arrSize; i++)
        {
        tempArr2[i] = arr2[i];
        }

        int sum[arrSize];
        int carry = doNormalAddition(arr1,arr2,sum,arrSize);

        int dec,proper = 0, carryNew;
        for(int i=arrSize-1;i>=0;i=i-4)
        {
            dec = getDec(sum[i-3],sum[i-2],sum[i-1],sum[i]);
            if(dec>9)
            {
                int len = (digits-proper)*4;
                int newArray[len];
                for(int k =0;k<len;k++)
                {
                    newArray[k] = 0;
                }
                newArray[len-1] =0;
                newArray[len-2] =1;
                newArray[len-3] =1;
                newArray[len-4] =0;
                carryNew = doNormalAddition(sum,newArray,sum,arrSize-(proper*4));
                proper++;
            }
            else
            {
                proper++;
            }
        }
        int i, size = arrSize,k=0;
        if(carryNew)
        {
            size = arrSize+4;
        }
        int finalSumArray[size];
        if(carryNew)
        {
            finalSumArray[0] = 0;
            finalSumArray[1] = 0;
            finalSumArray[2] = 0;
            finalSumArray[3] = 1;
            i = 4;
            arrSize = arrSize+4;
        }
        else
        {   int finalSumArray[arrSize];
            i=0;
        }
        while (i<arrSize)
        {
            finalSumArray[i] = sum[k];
            i++;
            k++;
        }
            
        printf("%d (",n1);
        for (int i = 0; i < temparrSize; i++)
        {
            printf("%d",tempArr1[i]);
            if(((i+1)%4) == 0)
            {
                printf(" ");
            }
        }
        printf(") + %d ( ",n2);
        for (int i = 0; i < temparrSize; i++)
        {
            printf("%d",tempArr2[i]);
            if(((i+1)%4) == 0)
            {
                printf(" ");
            }
        }

        printf(") = ");
        for(int i =0;i<arrSize;i=i+4)
        {
            dec = getDec(finalSumArray[i],finalSumArray[i+1],finalSumArray[i+2],finalSumArray[i+3]);
            printf("%d",dec);
        }

        printf(" (");
        for(int i=0;i<arrSize;i++)
            {
                printf("%d",finalSumArray[i]);
                if(((i+1)%4) == 0)
                {
                    printf(" ");
                }
            }
        printf(")");
        printf("\n");
        testCases--;
    }

}