// https://vjudge.net/contest/713089#problem/H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){

    uint8_t t;
    scanf("%hhu", &t);

    // alocamos memoria suficiente
    int *N = malloc(sizeof(int) * t);
    int *K = malloc(sizeof(uint16_t) * t);

    // guardamos las inputs
    int maxN = 0;
    for(uint8_t i = 0; i < t; i++){
        scanf("%d %hu", &N[i], &K[i]);
        if(N[i]>maxN){
            maxN = N[i];
        }

    }

    // calculamos los numeros primos y cuantos habian

    int N = 100; // o el valor que necesites
    int size = maxN / 3 + 5;
    int *prime_count = malloc((size) * sizeof(uint16_t));
    int *primes = malloc((size) * sizeof(int)); 
    int prime_index = 0;
    
    bool *is_prime = malloc((maxN + 1) * sizeof(bool));
    for (int i = 0; i <= N; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    
    prime_count[0] = 0;
    prime_count[1] = 0;
    
    // Criba + llenar prime_count[] y primes[]
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes[prime_index++] = i; // Guardamos el primo
            prime_count[i] = prime_count[i - 1] + 1;
            for (int j = i * 2; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
        
    }
    
    





    free(N);
    free(K);
    free(prime_count);
    free(primes);
    free(is_prime);

    return 0;
}