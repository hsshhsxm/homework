#include <stdio.h>

#define COURSENUM 5
#define STUNUM 10

double avgPerStu(int * score, int No){
    double result = 0;
    for(int i = 0; i < COURSENUM; ++i)
        result += score[i * STUNUM + No];
    result /= COURSENUM;
    return result;
}

double avgPerCourse(int * score, int No){
    double result = 0;
    for(int i = 0; i < STUNUM; ++i)
        result += score[No* STUNUM + i];
    result /= STUNUM;
    return result;
}

void findMaxScore(int * score, int* result){
    int Maxi = 0, Maxj = 0, tmpMax = score[0];
    for(int i = 0; i < COURSENUM; ++i){
        for(int j = 0; j < STUNUM; ++j){
            if(score[i * STUNUM + j] > tmpMax){
                tmpMax = score[i * STUNUM + j];
                Maxi = i;
                Maxj = j;
            }
        }
    }
    *result = Maxi;
    *(result+1) = Maxj;
}

double countVariance(int * score){
    double x[STUNUM];
    for(int i = 0; i < STUNUM; ++i)
        x[i] = avgPerStu(score,i);
    double sum1 = 0, sum2 = 0, sumTotal = 0;
    for(int i = 0; i < STUNUM; ++i){
        sum1 += x[i];
        sum2 += x[i] * x[i];
    }
    sumTotal = sum2 / STUNUM + sum1 * sum1 / STUNUM / STUNUM;
    return sumTotal;
}

int main(){
    int score[COURSENUM * STUNUM];
    for(int i = 0; i < COURSENUM * STUNUM; ++i)
            scanf("%d", &score[i]);
    printf("(1)计算每个学生平均分\n");
    for(int i = 0; i < STUNUM; ++i)
        printf("学生%d的平均分为%f\n", i, avgPerStu(score,i));
    printf("(2)计算每门课的平均分\n");
    for(int i = 0; i < COURSENUM; ++i)
        printf("课程%d的平均分为%f\n", i, avgPerCourse(score,i));
    printf("(3)找出所有50个分数中最高的分数所对应的学生和课程\n");
    int result[2];
    findMaxScore(score, result);
    printf("50个分数中最高的分数所对应的学生为%d，课程为%d\n",result[0], result[1]);
    printf("(4)计算平均分方差\n");
    printf("平均分方差为%f\n", countVariance(score));
    return 0;
}