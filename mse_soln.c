#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int process;
    int time;
    struct node *next;
    
};

int rrqueue[1000];
int rFront,rRear;

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

int processedCount;

int getRRProcess(int arr[], int burst[], int processed[],int p,int time,int q)
{
    //if queue is empty
    if(rRear == -1)
    {
        rFront++;
        for(int i =0;i<p;i++)
        {
            if(arr[i]<=time)
            {
                rRear++;
                rrqueue[rRear] = i;
                processedCount++;
                processed[i] = 1;
            }
        }
    }
    

    int count;
    if(processedCount<p)
    {
        count = 1;
        while(count <= q)
        {
            for(int i=0;i<p;i++)
            {
                if(arr[i]<=time+count && processed[i] == 0)
                {
                    rRear++;
                    rrqueue[rRear] = i;
                    processed[i] = 1;
                    processedCount++;
                }
                
            }
            count++;
        }
    }

    //add front node to rear of queue before deleting;
    if(burst[rrqueue[rFront]]<=q)
    {
        return rrqueue[rFront];
    }
    else
    {
        rRear++;
        rrqueue[rRear] = rrqueue[rFront];
        return rrqueue[rFront];
    }


}

int main()
{
    int p, q;
    struct node *front = NULL;
    struct node *rear = NULL;
    processedCount =-1;
    rFront=-1;
    rRear=-1;
    printf("Enter Number of Processes (P):");
    scanf("%d",&p);
    if(p<4 || p>10)
    {
        printf("Number of processes is out of range. Constraint not satisfied");
        return 0;
    }
    int arr[p],burst[p],tempBurst[p],processed[p],temparr[p];
    for(int i =0;i<p;i++)
    {
        printf("Enter arrival time and burst time of process P%d: ",i);
        scanf("%d",&arr[i]);
        scanf("%d",&burst[i]);
    }

    //Check if at least one process with arrival time = 0
    int checkArrCase =0;
    for(int i =0;i<p;i++)
    {
        if(arr[i] == 0)
        {
            checkArrCase = 1;
        }
    }

    if(checkArrCase == 0)
    {
        printf("No process has arrival time zero. Constraint not satisfied");
        return 0;
    }

    printf("Enter Time Quantum:");
    scanf("%d",&q);

    for(int i=0;i<p;i++)
    {
        tempBurst[i] = burst[i];//copy burst values in a temp array because we need it in future
        temparr[i] = arr[i]; 
    }

    int time =0, toProcess,temp,temp2,tempTime,lastBurst;
    for(int i=0;i<p;i++)
    {
        processed[i] = 0;
    }
       
    
    while(!checkBurstZero(burst,p) )
    {
        toProcess =  getRRProcess(arr, burst,processed, p, time,q); // get process number from Round Robin queue
        rFront++;
        //If CPU remains idle then exit
        if(burst[toProcess] <= 0)
        {
            printf("CPU remains idle. Constraint not satisfied");
            return 0;
        }

        //decide next time increment depending on burst time and quantum
        if(burst[toProcess]>q)
        {
            burst[toProcess] = burst[toProcess]-q;
            lastBurst = burst[toProcess];
            tempTime = q;
        }
        else
        {
            tempTime=burst[toProcess];
            lastBurst = burst[toProcess];
            burst[toProcess] = 0;
        }


        //add node to gnatt chart
        struct node *tempNode = (struct node *)malloc(sizeof(struct node));
        tempNode->process = toProcess;
        tempNode->time = time+tempTime;
        tempNode->next = NULL;
        
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

        time = time+tempTime;
        
    }

    struct node *ptr;
   
    //Completion Time calculation
    int cTime[p],wTime[p],completionTime;
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

    //Turnaround Time and Waiting time calculation
    int turnAroundTime[p];
    for(int i =0;i<p;i++)
    {
        turnAroundTime[i] = cTime[i] - arr[i];
        wTime[i] = cTime[i]-arr[i]-tempBurst[i];
    }

    for(int i=0;i<p;i++)
    {
        if(turnAroundTime[i]<0 || wTime[i]<0)
        {
            printf("CPU remains idle. Constraint not satisfied");
            return 0;
        }
    }

    //print gnatt chart
    printf("\nGnatt chart:\n");
    int lastTime;
    ptr = front;
    printf("0 ->");
    while(ptr)
    {
        printf(" |P%d| <- %d ",ptr->process,ptr->time ); 
        if(ptr->next)
        {
            printf("->");
        }     
        ptr = ptr->next;
    }

    //sort table output based on arrival time
    int minIndex,minVal,sortedarr[p];
    for(int i=0;i<p;i++)
    {
        minIndex = 0;
        minVal = arr[0];
        for(int j=0;j<p;j++)
        {
            if(arr[j]<minVal)
            {
                minIndex = j;
                minVal = arr[j];
            }
        }
        arr[minIndex] = INT_MAX;
        sortedarr[i] = minIndex;
    }

    //print output table
    int count =0;
    printf("\n\nP\tAT\tBT\tTAT\tWT");
    printf("\n__________________________________\n");
    while(count<p)
    {
        int process = sortedarr[count];
        printf("\nP%d\t%d\t%d\t%d\t%d", process, temparr[process], tempBurst[process],turnAroundTime[process], wTime[process]);
        count++;
    }
    printf("\n__________________________________\n");

    //Calculate average WT and TAT
    float avgWT=0, avgTAT=0;
    for(int i=0;i<p;i++)
    {
        avgWT += wTime[i];
        avgTAT += turnAroundTime[i];
    }
    avgTAT=avgTAT/p;
    avgWT = avgWT/p;

    //calculate context switches
    int contextSw =0;
    ptr = front;
    while(ptr)
    {
        if(ptr->next!=NULL)
        {
            if(ptr->process!=ptr->next->process)
            contextSw++;

        }
        ptr = ptr->next;
        
    }
    printf("\n\nAverage Waiting Time: %.2f\n", avgWT);  
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);   
    printf("\nTotal Context Switches: %d\n", contextSw);    

    return 0;
}