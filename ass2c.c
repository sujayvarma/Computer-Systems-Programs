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
void onesComplement(int arr[],int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        if(arr[i]==0)
            arr[i] =1;
        else
            arr[i]=0;
    }
    
}
int adder1(int arr1[],int arr2[],int sum[],int arrSize,int nibbleCarry[])
{
    int carry = 0,val;
    for(int i =arrSize-1,k=0; i>=0; i--)
    {
        val = arr1[i]+arr2[i]+carry;
        switch (val)
        {
        case 0:
            sum[i]=0;
            carry=0;
            break;

        case 1:
            sum[i]=1;
            carry=0;
            break;

        case 2:
            sum[i]=0;
            carry=1;
            break;

        case 3:
            sum[i]=1;
            carry=1;
            break;
        
        default:
            break;
        }
        
        if((i)%4 == 0)
        {
            nibbleCarry[k]=carry;
            k++;
        }
        
    }
    return carry;
}

void nibbleAdder(int sum[],int value[],int start)
{
    int val,carry=0;
    for(int i=start+3,k=3;i>=start;i--)
    {
        val = sum[i]+value[k]+carry;
        switch (val)
        {
        case 0:
            sum[i]=0;
            carry=0;
            break;

        case 1:
            sum[i]=1;
            carry=0;
            break;

        case 2:
            sum[i]=0;
            carry=1;
            break;

        case 3:
            sum[i]=1;
            carry=1;
            break;
        
        default:
            break;
        }
        k--;
    }
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
        int arr1[arrSize], arr2[arrSize];

        int *ptr1 = &arr1[arrSize-4];//pointer to fourth last element
        int ldigit = getLastDigit(num1);
        while (num1)
        {

            num1 = num1/10;
            intToBinary(ldigit,arr1,ptr1);
            ptr1 = ptr1-4;
            ldigit = getLastDigit(num1);
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
    
        int nibbleCarry[digits];
        int sum[arrSize];
        onesComplement(arr2,arrSize);
        
        int eoc = adder1(arr1,arr2,sum,arrSize,nibbleCarry);
    
        if(eoc == 1)
        {
            //positive answer
            int val1[]={0,0,0,0};
            int val2[]={1,0,1,0};
            int tempArray[arrSize];
            for(int i =0; i<arrSize;i++)
            {
                tempArray[i]=0;
            }
            tempArray[arrSize-1]=eoc;
            int tempNibbleArray[digits];
            adder1(sum,tempArray,sum,arrSize,tempNibbleArray);
            
            for(int i =0,k=digits-1; i<arrSize; i=i+4)
            {
                if(nibbleCarry[k] == 1)
                {
                    nibbleAdder(sum,val1,i);
                }
                else
                {
                    nibbleAdder(sum,val2,i);
                }
                k--;
            }
            
        }
        else
        {
            //negative answer
            int val1[]={1,0,1,0};
            int val2[]={0,0,0,0};
            //compliment
            for (int i = 0; i < arrSize; i++)
            {
                if(sum[i]==0)
                {
                    sum[i]=1;
                }
                else
                {
                    sum[i]=0;
                }
            }
            
            for(int i =0,k=digits-1; i<arrSize; i=i+4)
            {
                if(nibbleCarry[k] == 1)
                {
                    nibbleAdder(sum,val1,i);
                }
                else
                {
                    nibbleAdder(sum,val2,i);
                }
                k--;
            }
            
        }

        int dec;
        printf("%d (",n1);
        for (int i = 0; i < arrSize; i++)
        {
            printf("%d",arr1[i]);
            if(((i+1)%4) == 0)
            {
                printf(" ");
            }
        }
        printf(") - %d ( ",n2);
        for (int i = 0; i < arrSize; i++)
        {
            printf("%d",arr2[i]);
            if(((i+1)%4) == 0)
            {
                printf(" ");
            }
        }

        printf(") = ");
        if(eoc == 0)
        {
            printf("-");
        }
        for(int i =0;i<arrSize;i=i+4)
        {
            dec = getDec(sum[i],sum[i+1],sum[i+2],sum[i+3]);
            printf("%d",dec);
        }
        printf(" (");
        for(int i=0;i<arrSize;i++)
            {
                printf("%d",sum[i]);
                if(((i+1)%4) == 0)
                {
                    printf(" ");
                }
            }
        printf(")");
        printf("\n");
        testCases--;
    }
        
    return 0;
}