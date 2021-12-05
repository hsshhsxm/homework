#include <stdio.h>
#include "poweri.h"

int main(){
    int n11=3, n12=10, n21=4, n22=11, n31=5, n32=12;
    printf("3^10 = %lld\n4^10 = %lld\n5^12 = %lld\n", poweri(n11,n12), poweri(n21, n22), poweri(n31, n32));
    return 0;
}