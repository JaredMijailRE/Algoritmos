// https://vjudge.net/contest/713089#problem/H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    uint8_t t;
    scanf("%hhu", &t);

    int *N_arr = (int *)malloc(sizeof(int) * t);
    uint16_t *K_arr = (uint16_t *)malloc(sizeof(uint16_t) * t);

    int max_overall_N = 0;
    for (uint8_t i = 0; i < t; i++) {
        scanf("%d %hu", &N_arr[i], &K_arr[i]);
        if (N_arr[i] > max_overall_N) {
            max_overall_N = N_arr[i];
        }
    }

    bool *is_prime = NULL;
    int *prime_cumulative_count = NULL;

    if (max_overall_N > 0) {
        is_prime = (bool *)malloc((max_overall_N + 1) * sizeof(bool));
        prime_cumulative_count = (int *)malloc((max_overall_N + 1) * sizeof(int));

        for (int i = 0; i <= max_overall_N; i++) is_prime[i] = true;
        if (max_overall_N >= 0) is_prime[0] = false;
        if (max_overall_N >= 1) is_prime[1] = false;

        for (int p = 2; (long long)p * p <= max_overall_N; p++) {
            if (is_prime[p]) {
                for (long long i = (long long)p * p; i <= max_overall_N; i += p)
                    is_prime[i] = false;
            }
        }

        prime_cumulative_count[0] = 0;
        if (max_overall_N >= 1) prime_cumulative_count[1] = 0;
        for (int i = 2; i <= max_overall_N; i++) {
            prime_cumulative_count[i] = prime_cumulative_count[i - 1];
            if (is_prime[i]) {
                prime_cumulative_count[i]++;
            }
        }
    } else { 
        prime_cumulative_count = (int *)malloc( ( (max_overall_N > 1 ? max_overall_N : 2) +1) * sizeof(int));
        for(int i=0; i <= (max_overall_N > 1 ? max_overall_N : 2) ; ++i) prime_cumulative_count[i] = 0;
    }


    for (uint8_t test_idx = 0; test_idx < t; test_idx++) {
        int current_N = N_arr[test_idx];
        uint16_t current_K = K_arr[test_idx];
        long long count_k_frequent_ranges = 0;

        if (current_N < 2) { 
            printf("0\n");
            continue;
        }
        
        int H_ptr = 2; 
        for (int L = 2; L <= current_N; L++) {
            if (H_ptr < L) {
                H_ptr = L;
            }

            int primes_at_L_minus_1 = (L - 1 >= 0 && L - 1 <= max_overall_N) ? prime_cumulative_count[L - 1] : 0;

            while (H_ptr <= current_N && 
                   ( (H_ptr <= max_overall_N ? prime_cumulative_count[H_ptr] : 0) - primes_at_L_minus_1 < current_K) ) {
                H_ptr++;
            }

            if (H_ptr <= current_N) {
                count_k_frequent_ranges += (long long)(current_N - H_ptr + 1);
            } else {
                break;
            }
        }
        printf("%lld\n", count_k_frequent_ranges);
    }

    free(N_arr);
    free(K_arr);
    if(is_prime) free(is_prime);
    if(prime_cumulative_count) free(prime_cumulative_count);

    return 0;
}