#include <stdio.h>
#include <math.h>
#include <string.h>

double solution(char str[], double low, double high){
    double n = 10000000;
    double h = (high - low) / n;
    double sum = 0;
    double (*p)(double);
    if(strcmp(str, "sin") == 0)
        p = sin;
    if(strcmp(str, "cos") == 0)
        p = cos;
    if(strcmp(str, "exp") == 0)
        p = exp;
    for(double i = low; i < high; i+= h)
        sum += p(i) * h;
    return sum;
}

int main(){
    int a = 0, b = 1;
    double ssin = solution("sin", a, b);
    double scos = solution("cos", a, b);
    double sexp = solution("exp", a, b);
    printf("sin = %f\ncos = %f\nexp = %f\n",ssin, scos, sexp);
}