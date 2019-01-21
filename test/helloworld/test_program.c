#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char* argv[]){
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n%d\n", a+b, a*b);
    return 0;
}
