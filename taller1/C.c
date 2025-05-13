// https://vjudge.net/contest/713089#problem/C
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(){
    uint8_t n;
    uint8_t k;
    scanf("%hhu %hhu", &n, &k);
    uint8_t maxMinutes = 4 * 60;
    maxMinutes -= k;
    uint8_t numExcercise = 0;


    uint16_t total = 0;
    for(uint8_t i = 1; i <= n; i++){
        total += 5 * i;
        if(total <= maxMinutes){
            numExcercise++;
        } else {
            break;
        }
    }

    printf("%hhu\n", numExcercise);

    return 0;
}