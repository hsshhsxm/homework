#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	double a;
	printf("a = ");
	scanf("%lf",&a);
	double x1 = 1;
	double x2 = (double)1 / 2 * (x1 + a / x1);
	double minus = fabs(x2 - x1);
	while(minus > 1e-5){
		x1 = x2;
		x2 = (double)1 / 2 * (x1 + a / x1);
		minus = fabs(x2 - x1);
	}
	printf("sqrt(a) = %f\n",x2);
	return 0;
}
