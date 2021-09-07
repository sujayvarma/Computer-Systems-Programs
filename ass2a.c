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

int main()
{
    int num, bits, testCases;
    printf("Number of test cases:");
    scanf("%d",&testCases);
    while(testCases)
    {
        printf("\nBits available?: ");
        scanf("%d",&bits);
        printf("Decimal Number: ");
        scanf("%d",&num);
        int digits = numOfDigits(num);
        if(bits>=(digits*4))
        {
            int arrSize = 4*digits;
            int arr[arrSize];
            int *ptr = &arr[arrSize-4];//pointer to fourth last element
            int ldigit = getLastDigit(num);
            while (num)
            {

                num = num/10;
                /* code */
                intToBinary(ldigit,arr,ptr);
                ptr = ptr-4;
                ldigit = getLastDigit(num);
            }
            printf("\nBCD equivalent: ");
            for (int i = 0; i < arrSize; i++)
            {
                printf("%d",arr[i]);
                if(((i+1)%4) == 0)
                {
                    printf("\t");
                }
            }

        }
        else
        {
            printf("BCD equivalent: cannot be represented");
        }
        testCases--;
    }

}