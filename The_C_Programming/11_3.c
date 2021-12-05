#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char * argv[])
{
    if(argc == 3){
        long n = atol(argv[1]);
        long x = atol(argv[2]);
        long result = pow(n,x);
        printf("%ld\n", result);
    }
    else if(argc < 3)
        printf("no enough arguments\n");
    else 
        printf("too many arguments\n");
    return 0;
}