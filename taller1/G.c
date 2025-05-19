// https://vjudge.net/contest/713089#problem/G 

#include <stdio.h>
#include <math.h>

void evaluate() {
    unsigned int a;
    scanf("%u", &a);


    unsigned int n = a * 2;
    long double loga = logl(a);

    long double sum_log = 0.0L;
    for (unsigned int i = 1; i <= n; ++i) {
        sum_log += logl(i);
    }

    while (sum_log < (long double)n * loga) {
        ++n;
        sum_log += logl(n);
    }

    printf("%u\n", n);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        evaluate();
    }
    return 0;
}
