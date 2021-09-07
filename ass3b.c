#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char name[100];
    int roll;
    struct node *next;
    
};
int main()
{
    int N,n,roll;
    printf("Number of test cases:");
    scanf("%d", &N);
    while(N)
    {
        struct node * front = NULL;
        struct node * rear = NULL;
        printf("\nNumber of students:");
        
        scanf("%d", &n);
        //create circular queue while storing the input
        while(n)
        {
            
            char name1[100];
            printf("\nName: ");
            scanf("%s", name1);
            printf("Roll: ");
            scanf("%d",&roll);
            struct node *tempNode = (struct node *)malloc(sizeof(struct node));
            strcpy(tempNode->name, name1);
            tempNode->roll = roll;
            tempNode->next = NULL;
      

            if(front == NULL) 
            {
                front = tempNode;
                rear = tempNode;
                
            }
            else
            {
                rear->next=tempNode;
                rear = rear->next;
                rear->next = front;
            }
            
            n--;
        }

        char key;
        int cmp,tempRoll,swapped;
        char tempName[100];

        printf("Sorting key? ('N' for name/ 'R' for roll number):");
        scanf(" %c",&key);
        struct node *t1 = front;
        struct node *last = front;

        //actual sorting
        switch (key)
        {
        case 'N':
        //sorting by Name
            while(t1->next!=front)
            {
                struct node* t2=t1->next;
                while(t2!=front)
                {
                    if (strcmp(t1->name,t2->name)>0) //swap 
                   {
                       tempRoll = t2->roll;
                       strcpy(tempName , t2->name);
                       strcpy(t2->name, t1->name);
                       t2->roll = t1->roll;
                       strcpy(t1->name, tempName);
                       t1->roll = tempRoll;
                   }
                    t2=t2->next;
                }
                t1=t1->next;
            }
            
            break;

        case 'R':
        //sorting by Roll
            while(t1->next!=front)
            {
                struct node* t2=t1->next;
                while(t2!=front)
                {
                    if (t1->roll > t2->roll)//swap
                   {
                       tempRoll = t2->roll;
                       strcpy(tempName , t2->name);
                       strcpy(t2->name, t1->name);
                       t2->roll = t1->roll;
                       strcpy(t1->name, tempName);
                       t1->roll = tempRoll;
                   }
                    t2=t2->next;
                }
                t1=t1->next;
            }
            break;
        
        default:
            break;
        }

        struct node * t = front;
        do 
        {
            printf("\nName: %s ",t->name);
            printf("Roll: %d",t->roll);
            t = t->next;
        }while(t!=front);
        printf("\n");
        

        N--;
    }

    return 0;
}