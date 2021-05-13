#include <stdio.h>

struct Student{
    int No;
    char name[10];
    int colleageNo;
    int grade;
    int score[10];
    double avgScore;
}s[10];

int main()
{
    for(int i = 0; i < 10; ++i){
        scanf("%d%s%d%d",&s[i].No,s[i].name,&s[i].colleageNo,&s[i].grade);
        for(int j = 0; j < 10; ++j){
            scanf("%d",&s[i].score[j]);
            s[i].avgScore += s[i].score[j];
        }
        s[i].avgScore /= 10;
    }
    int maxI = 0;
    int maxScore = s[0].avgScore;
    for(int i = 1; i < 10; ++i){
        if(s[i].avgScore > maxScore){
            maxScore = s[i].avgScore;
            maxI = i;
        }
    }
    printf("每个学生10门课总平均成绩:\n");
    for(int i = 0; i < 10; ++i)
        printf("姓名:%s, 平均成绩:%.2f\n", s[i].name, s[i].avgScore);
    printf("总平均成绩最高分的学生信息:\n");
    printf("学号:%d 姓名:%s 院系代码:%d 年级:%d\n",s[maxI].No,s[maxI].name,s[maxI].colleageNo,s[maxI].grade);
    printf("10门课的成绩:");
    for(int i = 0; i < 10; ++i)
        printf("%d ",s[maxI].score[i]);
    printf("\n");
    printf("总平均成绩:%.2f\n",s[maxI].avgScore);
    for(int i = 0; i < 10; ++i){
        if(s[i].avgScore == maxScore && i != maxI){
            printf("----------\n");
            printf("学号:%d 姓名:%s 院系代码:%d 年级:%d\n",s[i].No,s[i].name,s[i].colleageNo,s[i].grade);
            printf("10门课的成绩:");
            for(int j = 0; j < 10; ++j)
                printf("%d ",s[i].score[j]);
            printf("\n");
            printf("总平均成绩:%.2f\n",s[i].avgScore);
        }
    }
    return 0;
}

