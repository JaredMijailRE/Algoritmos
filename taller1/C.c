// https://vjudge.net/contest/713089#problem/C
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(){
    uint8_t n;
    uint8_t k;
    scanf("%hhu %hhu", &n, &k);
    uint8_t maxMinutes = 4 * 60;
    maxMinutes =- k;
    uint8_t i = maxMinutes / 5;
    if(i > n){
        i = n;
    }
    printf("%hhu", i);

    return 0;
}