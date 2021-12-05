#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int a;
    int b;
    struct Node * next;    
} node;

void printList(node * head){
    while(head){
        printf("a = %d, b = %d\n",head->a,head->b);
        head = head->next;
    }
        
}

int main()
{
    node *tmp1, *tmp2, *tmp3;
    node * head;
    for(int i = 0; i < 10; ++i){
        tmp1 = (node *)malloc(sizeof(node));
        tmp1->a = i;
        tmp1->b = 20 - i;
        if(i == 0)
            head = tmp1;
        else 
            tmp2->next = tmp1;
        tmp2 = tmp1;
    }
    printf("origin list:\n");
    printList(head);
    tmp1 = head;
    tmp2 = head->next;
    tmp1->next = NULL;
    while(tmp2){
        tmp3 = tmp2->next;
        tmp2->next = tmp1;
        tmp1 = tmp2;
        tmp2 = tmp3;
    }
    head = tmp1;
    printf("changed list:\n");
    printList(head);
    return 0;
}

