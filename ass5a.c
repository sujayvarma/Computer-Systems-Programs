#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int process;
    int time;
    struct node *next;
    
};

bool checkBurstZero(int burst[],int p)
{
    //Returns true if all burst values are zero
    for(int i=0;i<p;i++)
    {
        if (burst[i] > 0)
        {
            return false;
        }
    }
    return true;
}

int getSrtfProcess(int arr[], int burst[], int p, int currTime)
{
    int min = 10000, toProcess = -1;
    for(int i =0;i<p;i++)
    {
        if (arr[i]<=currTime)
        {
            if(burst[i]<min && burst[i]>0)
            {
                min = burst[i];
                toProcess = i;
            }
        }
    }

    return toProcess;
}

int main()
{
    int p, testCases;
    printf("Number of test cases:");
    scanf("%d",&testCases);
    while(testCases)
    {
        struct node *front = NULL;
        struct node *rear = NULL;
        printf("Number of Processes (P):");
        scanf("%d",&p);
        int arr[p],burst[p],tempBurst[p];
        for(int i =0;i<p;i++)
        {
            printf("Enter arrival time and burst time of process %d: ",i+1);
            scanf("%d",&arr[i]);
            scanf("%d",&burst[i]);
        }

        for(int i=0;i<p;i++)
        {
            tempBurst[i] = burst[i];//copy burst values in a temp array because we need it in future
        }

        int time =0, toProcess;
        while(!checkBurstZero(burst,p))
        {
            toProcess =  getSrtfProcess(arr,burst,p, time); // get process number which has srtf
            if (toProcess == -1)
            {
                time++;
                continue;
            }
            burst[toProcess]--;
            struct node *tempNode = (struct node *)malloc(sizeof(struct node));
            tempNode->process = toProcess;
            tempNode->time = time +1;
            tempNode->next = NULL;
            //add node to gnatt chart
            if(front == NULL)
            {
                front = tempNode;
                rear = tempNode;
            }
            else
            {
                rear->next=tempNode;
                rear = tempNode;
            }
            
            time++;

        }
        
        int responseTime[p];
        struct node *ptr;

        //Response Time calculation
        for(int i =0;i<p; i++)
        {
            ptr = front;
            while(ptr)
            {
                if (ptr->process == i)
                {
                    responseTime[i] = ptr->time-1 - arr[i];
                    break;
                }
                ptr = ptr->next;
            }
        }



        //Waiting time calculation
        int waitingTime, wTime[p], processedBurst;
        for(int i=0;i<p;i++)
        {
            waitingTime = 0;
            processedBurst = 0;
            ptr = front;
            while(ptr)
            {
                if(ptr->process == i)
                {
                    processedBurst++;
                }
                else if(((ptr->time)-1) < arr[i])
                {
                    ptr = ptr->next;
                    continue;
                }
                else
                {
                    if(processedBurst<tempBurst[i])
                    {
                        waitingTime++;
                    }
                }

                ptr = ptr->next;
            }
            wTime[i] = waitingTime;
        }

        //Completion Time calculation
        int cTime[p],completionTime;
        for(int i=0;i<p;i++)
        {
            ptr = front;
            while(ptr)
            {
                if(ptr->process == i)
                {
                    completionTime = ptr->time;
                }

                ptr = ptr->next;
            }

            cTime[i] = completionTime;
        }

        //Turnaround Time calculation
        int turnAroundTime[p];
        for(int i =0;i<p;i++)
        {
            turnAroundTime[i] = cTime[i] - arr[i];
        }

        //Calculate average of all times
        float avgRT=0, avgWT=0, avgTAT=0,avgCT=0;
        for(int i=0;i<p;i++)
        {
            avgRT += responseTime[i],
            avgWT += wTime[i];
            avgTAT += turnAroundTime[i];
            avgCT += cTime[i];
        }

        avgRT = avgRT/p;
        avgWT = avgWT/p;
        avgTAT = avgTAT/p;
        avgCT = avgCT/p;

        //Print all that is required
        for(int i =0;i<p;i++)
        {
            printf("Process P%d (response, waiting, turnaround and completion time): %d, %d, %d, %d\n",i+1,responseTime[i],wTime[i],turnAroundTime[i],cTime[i]);
        }
        printf("Average response time: %.2f\n",avgRT);
        printf("Average waiting time: %.2f\n",avgWT);
        printf("Average turnaround time: %.2f\n",avgTAT);
        printf("Average completion time: %.2f\n",avgCT);
        testCases--;
    }
    return 0;
}