#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int length;
//char path = "";

struct node{
    int val;
    struct node *l, *r;
    
};

struct node *insertNode(struct node *node, int key)
{
    if (node == NULL) 
    {
        struct node *tempNode = (struct node *)malloc(sizeof(struct node));
        tempNode->val = key;
        tempNode->l = tempNode->r = NULL;
        return tempNode;
    }

    if (key < node->val)
        node->l = insertNode(node->l, key);
    else
        node->r = insertNode(node->r, key);
    return node;
    
}

int traverseTreeLength(struct node *node, int key)
{
    int diff = (node->val) - key;
    if (diff % 2 == 0)
    {
        length = length + node->val;
        if (node->l)
        {
            return traverseTreeLength(node
            ->l, key);
        }
        else
        {
        }
        return length;
        
    }

    else
    {
        length = length + node->val;
        if (node->r)
        {
            return traverseTreeLength(node
            ->r, key);
        }
        else
        {
        }
        return length;
    }
    
}

int traverseTreePath(struct node *node, int key)
{
    int diff = (node->val) - key;
    if (diff % 2 == 0)
    {
        if (node->l)
        {
            printf("%d ->", node->val);
            return traverseTreePath(node
            ->l, key);
        }
        else
        {
            printf("%d", node->val);
        }
        return 0;
        
    }

    else
    {
        if (node->r)
        {
            printf("%d ->", node->val);
            return traverseTreePath(node
            ->r, key);
        }
        else
        {
            printf("%d", node->val);
        }
        return 0;
    }
    
}

int main()
{
    int nodeCount, value, key, testCase;
    
    struct node * root = NULL;
    printf("Number of test cases:");
    scanf("%d",&testCase);
    while (testCase)
    {
        printf("Number of elements:");
        scanf("%d", &nodeCount);
        while(nodeCount)
        {
            scanf("%d", &(value));
            root = insertNode(root, value);
            nodeCount--;
        }
        
        if(root)
        {
            printf("k=");
            scanf("%d", &key);
            length = traverseTreeLength(root, key);
            printf("\nSum of the path = %d\n", length);
            printf("Path = ");
            traverseTreePath(root, key);
        }

        testCase--;
    }
}