#include <stdio.h>

void matrix_multiply(const int m, const int n, const int p, 
const double* a, const double* b, double* c){
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < p; ++j){
            *(c + i * p + j) = 0;
            for(int k = 0; k < n; ++k){
                *(c + i * p + j) += (*(a + i * n + k)) * (*(b + k * p + j));
            }
        }
    }
}

int main(){
    double a[2][2];
    double b[2][3];
    a[0][0] = a[0][1] = 1;
    a[1][0] = 2;
    a[1][1] = 0;
    b[0][0] = 0;
    b[0][1] = 2;
    b[0][2] = 3;
    b[1][0] = b[1][1] = 1;
    b[1][2] = 2;
    double c[2][3];
    matrix_multiply(2,2,3,a,b,c);
    printf("%f %f %f\n%f %f %f",c[0][0],c[0][1],c[0][2],c[1][0],c[1][1],c[1][2]);
    return 0;
}