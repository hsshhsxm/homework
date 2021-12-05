#include <stdio.h>
#include <string.h>

typedef struct student
{
    int No;
    char name[10];
    struct student * next;
} stu;

void printList(stu * head){
    while(head){
        printf("No = %d, name = %s\n",head->No, head->name);
        head = head->next;
    }
}

int main()
{
    stu *aHead, *bHead, *tmp;
    stu a1,a2,a3,a4,b1,b2,b3,b4;
    a1.No = 1; strcpy(a1.name, "n1");
    a2.No = 3; strcpy(a2.name, "n2");
    a3.No = 7; strcpy(a3.name, "n3");
    a4.No = 8; strcpy(a4.name, "n4");
    b1.No = 3; strcpy(b1.name, "n2");
    b2.No = 5; strcpy(b2.name, "n5");
    b3.No = 9; strcpy(b3.name, "n6");
    b4.No = 7; strcpy(b4.name, "n3");
    aHead = &a1;
    a1.next = &a2; a2.next = &a3;
    a3.next = &a4; a4.next = NULL;
    bHead = &b1;
    b1.next = &b2; b2.next = &b3;
    b3.next = &b4; b4.next = NULL;
    printf("origin list a:\n");
    printList(aHead);

    stu *pa, *pb, *paf;
    pa = aHead;
    pb = bHead;
    while(pb){
        paf = NULL;
        pa = aHead;
        while(pa){
            if(pa->No == pb->No){
                if(paf == NULL)//头部节点
                    aHead = aHead->next;
                else if(pa->next)//中间节点
                    paf->next = pa->next;
                else //最后一个节点
                    paf->next = NULL;
            }
            paf = pa;
            pa = pa->next;
        }
        pb = pb->next;
    }
    printf("changed list a:\n");
    printList(aHead);
    return 0;
}

