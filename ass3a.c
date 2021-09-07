#include<stdio.h>
#include<stdlib.h>

struct node{
    int val;
    struct node *next;
    
};

struct node * enqueue(struct node *front,struct node *rear,int num)
{
    struct node *tempNode = (struct node *)malloc(sizeof(struct node));
    tempNode->val = num;
    tempNode->next= NULL;
    if((front == NULL) && (rear == NULL))
    {
        front=tempNode;
        rear=tempNode;
    }
    else
    {
        rear->next=tempNode;
    }
    return front;
}

int main()
{
    int testCases,q,n,num, newQ;
    printf("Number of test cases: ");
    scanf("%d",&testCases);
    while(testCases)
    {
        printf("Number of queues: ");
        scanf("%d",&q);
        newQ=q;
        printf("Number of elements in each queue: ");
        scanf("%d",&n);
        struct node *items[q*2];
        int count = 1, t=0;
        
        while (q)
        {
            struct node * front = NULL;
            struct node * rear = NULL;
            printf("Enter elements of queue %d: ",count);
            for(int i= 0;i<n;i++)
            {
                scanf("%d",&num);
                struct node *tempNode = (struct node *)malloc(sizeof(struct node));
                tempNode->val = num;
                tempNode->next= NULL;

                if((front == NULL) && (rear == NULL))
                {
                    front=tempNode;
                    rear=tempNode;
                }
                else
                {
                    rear->next=tempNode;
                    rear = tempNode;
                }
            }
            //items is an array of nodes which follows the order: front of Q1, rear of Q1, front of Q2, rear of Q2,...
            items[t] = front;
            items[t+1] = rear;
            t=t+2;                        
            count++;
            q--;
            
        }
        struct node *dummyNode = (struct node *)malloc(sizeof(struct node));
        dummyNode->val = 1000000;
        dummyNode->next= NULL;
        testCases--;
        int toDelete = -1,emptyLists = 0, number =0;
        int frontVal[newQ],c,min,first;
        struct node * masterFront = NULL;
        struct node * masterRear = NULL;
        while (emptyLists != newQ)
        {
            c = 0;
            
            for (int i = 0; i < newQ*2; i=i+2)
            {
                struct node * front = items[i];
                if(front!=NULL)
                    frontVal[c] = front->val;//extract front value of each queue
                else
                    {
                        //if front of a queue is NULL it means that queue is empty
                        number ++;
                        //set a high value only for the purpose of evaluating the min
                        frontVal[c] = 1000000;
                        if(number == 1)
                        {
                            first = c+1;
                        }
                    }
                c++;
            }
            if( emptyLists== newQ)//if number of empty queues == number of queues, break the loop
            break;
            min = frontVal[0];
            toDelete = 0;
            //extract smlallest front element among all queues, toDelete+1 is list number whose element is to be deleted in this iteration
            for (int i = 1; i < newQ; i++)
            {
                if(frontVal[i]<min)
                {
                    min = frontVal[i];
                    toDelete=i;
                }
            }
            //create a node which has the smallest element and add it to the master queue
            struct node *tempNode2 = (struct node *)malloc(sizeof(struct node));
            tempNode2->val = min;
            tempNode2->next= NULL;

            if((masterFront == NULL) && (masterRear == NULL))
            {
                masterFront=tempNode2;
                masterRear=tempNode2;
            }
            else
            {
                masterRear->next=tempNode2;
                masterRear = tempNode2;
            }
            
            //update the items array with next element;
            struct node * front = items[toDelete*2];
            if (front->next == NULL)
            {
                front = front->next;
                items[toDelete*2] = front;
                emptyLists++;
            }
            else
            {
                front = front->next;
                items[toDelete*2] = front;
            }
        }
        printf("Master queue: ");
        while (masterFront != NULL)
        {
            printf("%d ", masterFront->val);
            masterFront=masterFront->next;
        }
        
        printf("\nQueue %d is emptied first", first);                                                                                                                
        printf("\nQueue %d is emptied last\n", toDelete+1 );
    }
    return 0;
}