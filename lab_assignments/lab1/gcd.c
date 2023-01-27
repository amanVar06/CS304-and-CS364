#include<stdio.h>

//finding gcd using extended eculedian algorithm
int findGcd(int m, int a) {
    //x*m + a*y = 1
    //we need to find x and y
    //gcd(a,m) = 1 (must) where m = 26
    //using recursion

    if(m%a == 0) return a;
    return findGcd(a, m % a);
}

int main(int argc, char const *argv[])
{
    printf("GCD\n");
    int ans = findGcd(91, 39);
    printf("%d\n", ans);
    return 0;
}
