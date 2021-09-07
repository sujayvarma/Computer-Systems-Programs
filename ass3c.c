#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

int push(char stack[], int top, char val)
{
    top++;
    stack[top] = val;
    return top;
}

int pop(char stack[], int top)
{
    stack[top] = '$';//$ indicates garbage value
    top --;
    return top;
}

bool checkParanthesis(char input[], int n)
{
    char stack[30];
    int top = -1;
    for(int i =0; i<=n;i++)
    {
        if(input[i] == '(')//push each ( on stack
        {
            top = push(stack, top, input[i]);
        }

        else if(input[i] == ')') //for each ) pop an ( from stack
        {
            top = pop(stack, top);
        }
    }

    if(top == -1) // empty stack means balanced parantheses
    {
        return true;
    }

    return false;
    
}

int precedence(char ch)
{
    if (ch == '+' || ch == '-') // + and - have lowest precedence
    {
        return 1;
    }
    if(ch == '*' || ch == '/') // * and / have next high precedence
    {
        return 2;
    }
    if(ch == '^') // ^ has highest precendece
    {
        return 3;
    }

    return 0;
}

void infixToPostFix(char input[], int n)
{
    char postfix[100],stack[n], ch;
    int k = -1, top = -1;
    for(int i =0; i<=n; i++)
    {
        ch = input[i];
        if (isalnum(ch)) // if alpha num, push on stack
        {
            k++;
            postfix[k] = ch;
        }
        else if(ch == '(') // if (, push on stack
        {
            top = push(stack, top, ch);
        }
        else if(ch == '^')// if ^, push on stack
        {
            top = push(stack, top, ch);
        }
        else if(ch == ')') // if ), push till empty stack or ( is on top of stack
        {
            while(top!=-1 && stack[top]!='(')
            {
                k++;
                postfix[k] = stack[top];
                top = pop(stack, top);
            }
            top = pop(stack, top);
        }
        else
        {
            while(top!=-1 && precedence(ch)<=precedence(stack[top]))// check for precendece and then push/pop accordingly
            {
                k++;
                postfix[k] = stack[top];
                top = pop(stack, top);
            }
            top = push(stack, top, ch);
        }
    }

    //pop remaining elements
    while(top!=-1)
    {
        k++;
        postfix[k] = stack[top];
        top = pop(stack, top);
    }
    //add end char to make it a string
    k++;
    postfix[k] = '\0';

    printf("The Equivalent postfix expression is:\n");
    printf("Postfix Expression: %s", postfix);
}

int main()
{
    char input[30],c;
    printf("Enter Infix expression:\n");
    int k =-1;
    while (c != EOF) {
        c = getchar();
        if(c == '\n')//stop when user hits Enter
        break;
        if (c != ' ') //ignore whitespaces
        {
            k++;
            input[k] = c;
        }
    }
    bool validParam = checkParanthesis(input,k);// check if balanced parantheses
    if ( validParam == true )
    {
        printf("Parentheses are balanced\n");
        infixToPostFix(input, k);
    }
    else
    {
        printf("Parentheses are not balanced.\n");
        printf("Aborting execution.");
    }
    return 0;
}