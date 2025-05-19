// https://vjudge.net/contest/713089#problem/G 

#include <stdio.h>
#include <stdlib.h>

unsigned int factorial(int n) {
    if (n < 0) {
        return 0;
    }
    unsigned int resultado = 1;
    for (int i = 1; i <= n; ++i) {
        resultado *= i;
    }
    return resultado;
}

unsigned int potencia(unsigned int base, unsigned int exponente) {
    unsigned int resultado = 1;

    for (unsigned int i = 0; i < exponente; ++i) {
        resultado *= base;
    }

    return resultado;
}

void evaluate(){
    int a;
    scanf("%d", &a);
    int n = a*2;
    while (factorial(n) < potencia(a, n))
    {
        n++;
    }
    printf("%d\n", n);
}

int main(){
    
    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; i++){
        evaluate();
    }

    return 0;
}