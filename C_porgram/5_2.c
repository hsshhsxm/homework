#include <stdio.h>

#define NUM 15

int findNo(int *a, int begin, int end, int val){
    int No;
    int mid;
    while(1){
        mid = (end + begin) / 2;
        //printf("current:begin:%d, end:%d, mid:%d, val:%d\n",a[begin],a[end],a[mid],val);
        if(val > a[begin] || val < a[end]){
            No = -2;
            break;
        }
        if(val == a[begin]){
            No = begin;
            break;
        }
        if(val == a[end]){
            No = end;
            break;
        }

        if(val > a[mid]){
            end = mid - 1;
        } else if(val < a[mid]){
            begin = mid + 1;
        } else{
            No = mid;
            break;
        }

    }
    return No + 1;
}


int main(){
    int a[NUM] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    int toFind;
    printf("输入查找的数:");
    scanf("%d",&toFind);
    int No = findNo(a, 0, NUM - 1, toFind);
    if(No == -1)
        printf("无此数\n");
    else 
        printf("该数是第%d个元素的值\n",No);
    return 0;
}