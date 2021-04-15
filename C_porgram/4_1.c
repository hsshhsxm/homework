#include <stdio.h>

int main(){
    int x, a=6, b=9, c=25;
    printf("a+b>c&&b==c:%d\n",a+b>c&&b==c);
    printf("a||b+c&&b-c:%d\n",a||b+c&&b-c);
    printf("a&b&&b^c:%d\n",a&b&&b^c);
    printf("x=a&&-b>>3&&~0:%d\n",x=a&&-b>>3&&~0);
    printf("!(a|b)||c<<2:%d\n",!(a|b)||c<<2);
    return 0;
}