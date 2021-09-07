#include <stdio.h>
#include <stdbool.h>

int tail;
int tailTemp;

void push(int a[], int val)
{
    tail++;
    a[tail] = val;
}
void pushTemp(int a[], int val)
{
    tailTemp++;
    a[tailTemp] = val;
}

int popTemp(int a[])
{
    int val = a[tailTemp];
    tailTemp--;
    return val;
}

int pop(int a[])
{
    int val = a[tail];
    tail--;
    return val;
}

int top(int a[])
{
    if (tail>=0)
    {
        int val = a[tail];
        return val;
    }
    else
    {
        return -1;
    }
    
}

void sortAscending(int a[], int n)
{
    int newArray[n], tempArray[51], tempVal,val;
    newArray[0] = a[0];
    int popCount = 0;
    tailTemp = -1;
    tail = 0;
    bool popFlag = false;
    for(int i = 1;i<n;i++)
    {
        val = a[i];
        popFlag = false;
        while(top(newArray)>val)
        {
            popFlag = true;
            popCount++;
            tempVal = pop(newArray);
            pushTemp(tempArray,tempVal);
        }
        push(newArray, val);
        if(popFlag)
        {
            while(tailTemp!=-1)
            {
                tempVal = popTemp(tempArray);
                push(newArray,tempVal);
            }

        }

    }
    printf("Number of pops: %d",popCount);
}

void sortDescending(int a[], int n)
{
    int newArray[n], tempArray[51], tempVal,val;
    newArray[0] = a[0];
    int popCount = 0;
    tailTemp = -1;
    tail = 0;
    bool popFlag = false;
    for(int i = 1;i<n;i++)
    {
        val = a[i];
        popFlag = false;
        while(top(newArray)<val)
        {
            popFlag = true;
            popCount++;
            tempVal = pop(newArray);
            pushTemp(tempArray,tempVal);
        }
        push(newArray, val);
        if(popFlag)
        {
            while(tailTemp!=-1)
            {
                tempVal = popTemp(tempArray);
                push(newArray,tempVal);
            }

        }

    }
    printf("Number of pops: %d",popCount);
}

int main()
{
    int testCase = 0;
    scanf("%d",&testCase);
    while(testCase)
    {
        testCase--;
        int n;
        scanf("%d",&n);
        if(n>0)
        {
            int a[n];
            for(int i =0;i<n;i++)
            {
                scanf("%d",&a[i]);
            }
            printf("Order (1 for ascending/2 for descending): ");
            int order;
            scanf("%d",&order);
            if(order == 1)
            {
                sortAscending(a,n);
            }
            if(order==2)
            {
                sortDescending(a,n);
            }
        }
    }
    
    return 0;
}