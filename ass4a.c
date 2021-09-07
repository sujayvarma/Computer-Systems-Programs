#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int val;
    struct node *next;
    
};

struct node *mainArray[1000];
int rear;

void getCombination(int arr[], int n)
{
    if (n==1) //only one element remaining
    {
        struct node *tempNode = (struct node *)malloc(sizeof(struct node));
        struct node *head,*ptr2;
        int val = arr[0];
        int num;
        tempNode->val = arr[0];
        tempNode->next=NULL;

        //If first node, add it directly to master list
        if(rear == -1)
        {
            rear = rear +1 ;
            mainArray[rear] = tempNode;
        }
        else
        {
            for(int i=0; i<=rear;i++)
            {
                bool canAdd = true;
                head = mainArray[i];
                ptr2=head;
                do
                {
                    num = ptr2->val;
                    if((num == val )||(num == (val -1))||(num == (val +1)))
                    {
                        canAdd = false;
                        break;
                    }
                    
                    ptr2 = ptr2->next;
                    
                }while (ptr2 != NULL);

                if(canAdd == true)//Indicates this number can be grouped with the existing pair of numbers
                {
                    struct node *headNew = mainArray[i];
                    struct node *headTemp = NULL, *ptr =NULL;
                    
                    //Copy the whole list again and then append the new number to that list
                    while(headNew != NULL)
                    {
                        struct node *newNode = (struct node *)malloc(sizeof(struct node));
                        newNode->val = headNew->val;
                        newNode->next=NULL;
                        if(headTemp == NULL)
                        {
                            headTemp=newNode;
                            ptr = newNode;
                        }
                        else
                        {
                            ptr->next=newNode;
                            ptr = ptr->next;
                        }

                        headNew=headNew->next;
                    }
                    ptr->next=tempNode;
                    rear = rear +1 ;
                    mainArray[rear] = headTemp;                
                    
                }
            }

            //every number is a group in itself eg {5}
            rear = rear +1 ;
            mainArray[rear] = tempNode;
        }
    }

    //For more than one element split the array in two parts i.e. [1,2...n-1 ] and [n] . Recursively call the getCombination method
    else
    {
        int newSize = n-1;
        int newArray[newSize];
        int lastElementArray[1];
        for(int i =0;i<newSize;i++)
        {
            newArray[i] = arr[i];
        }
        lastElementArray[0]=arr[n-1];
        getCombination(newArray,newSize);
        getCombination(lastElementArray,1);
    }
    
}



int main()
{
    rear = -1;
    int totalCombinations, testCases,n;
    printf("Number of test cases:");
    scanf("%d",&testCases);
    while(testCases)
    {
        printf("Number of students (n):");
        scanf("%d",&n);
        int arr[n];

        //Add n students to array
        for (int i = 0; i < n; i++)
        {
            arr[i] = i+1;
        }

        //Get all valid combinations
        getCombination(arr,n);

        //print the output
        struct node *head,*ptr;
        totalCombinations = rear+1;
        printf("Number of ways a compatible batch can be chosen is: %d",totalCombinations);
        int maxLen=0;
        struct node *maxLenHead;
        printf("\nThe sets are:");
        for(int i =0;i<=rear;i++)
        {
            int len =0;
            head = mainArray[i];
            ptr = mainArray[i];
            printf("{");
            while(ptr != NULL)
            {
                printf("%d",ptr->val);
                ptr = ptr->next;
                if(ptr)
                {
                    printf(",");
                }
                len++;
                if(len>maxLen)
                {
                    maxLen=len;
                    maxLenHead = head;
                }
            }
            
            printf("},");
            
        }

        printf("\nLargest batch: ");
        printf("{");
        while(maxLenHead)
        {
            printf("%d", maxLenHead->val);
            maxLenHead=maxLenHead->next;
            if(maxLenHead)
            {
                printf(",");
            }
        }
        printf("}\n");

        testCases--;
    }
}