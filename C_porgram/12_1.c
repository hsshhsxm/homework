#include <stdio.h>

typedef struct Student{
    int No;
    char name[10];
    int score[10];
    double average;
}student;

void sortByNo(student * stu, int num){
    for(int i = 0; i < num - 1; ++i){
        for(int j = 0; j < num - i - 1; ++j){
            if(stu[j].No > stu[j+1].No){
                student tmp;
                tmp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = tmp;
            }
        }
    }
}

int main()
{
    student stu[5];
    for(int i = 0; i < 5; ++i){
        scanf("%d%s",&stu[i].No, stu[i].name);
        int sum = 0;
        for(int j = 0; j < 10; ++j){
            scanf("%d", &stu[i].score[j]);
            sum += stu[i].score[j];
        }
        stu[i].average = (double)sum / 10;
    }
    sortByNo(stu, 5);
    FILE * fp = fopen("stud", "w");
    for(int i = 0; i < 5; ++i){
        fprintf(fp, "%d %s ",stu[i].No, stu[i].name);
        for(int j = 0; j < 10; ++j){
            fprintf(fp, "%d ", stu[i].score[j]);
        }
        fprintf(fp, "%f ", stu[i].average);
    }
    fclose(fp);
    return 0;
}