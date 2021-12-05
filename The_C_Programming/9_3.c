#include <stdio.h>

typedef struct {
  int id;
  char name[20];
  char introduction[65535];
  char memo[65535];
} student_t;

#define STUDENT_NUM  5

int main(){
    student_t stu[STUDENT_NUM]={{5, "n5"}, {19, "n19"}, {2, "n2"}, {30, "n30"}, {21, "n21"}};
    student_t* pstu[STUDENT_NUM];
    for(int i = 0; i < STUDENT_NUM; ++i)
        *(pstu+i) = stu+i;
    for(int i = 0; i < STUDENT_NUM - 1; ++i)
        for(int j = 0; j < STUDENT_NUM - 1 - i; ++j)
            if((*(pstu+j))->id > (*(pstu+j+1))->id){
                student_t* tmp = *(pstu+j);
                *(pstu+j) = *(pstu+j+1);
                *(pstu+j+1) = tmp;
            }
    for(int i = 0; i < STUDENT_NUM; ++i)
        printf("id:%d name:%s\n", (*(pstu+i))->id,  (*(pstu+i))->name);
    return 0;
}