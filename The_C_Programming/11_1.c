#include <stdio.h>

#define NL  putchar('\n')
#define PR1(format, value)  printf("value=%format\t", (value))
#define PR(format, value)  printf("value=%" #format "\t", (value))
#define PRINT1(f, x1)  PR(f, x1); NL
#define PRINT2(f, x1, x2)  PR(f, x1); PRINT1(f, x2)


int main()
{
    int i=5;
    float x1=2.5, x2=7.5;
    PR1(d, i);
    PR(d, i);
    PRINT1(d, i);
    PRINT2(f, x1, x2);
    printf("------------------\n");
    printf("value=%format\t", (i));
    printf("value=%d\t", (i));
    printf("value=%d\t", (i)); putchar('\n');
    printf("value=%f\t", (x1)); printf("value=%f\t", (x2)); putchar('\n');

    return 0;
}

