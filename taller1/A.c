// https://vjudge.net/contest/713089#problem/A
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void minPush(uint8_t arr[], uint8_t j, uint8_t newElem) {

    while (j > 0 && arr[j - 1] > newElem) {
        arr[j] = arr[j - 1];
        j--;
    }

    arr[j] = newElem;
}

void game(){

uint8_t n;
scanf("%hhu", &n);
uint16_t size = 2 * n;
uint8_t arr[size];

for(uint16_t i = 0; i < size)
    uint8_t e;
    scanf("%hhu", e);
    minPush(arr, i, e)
}

int main(){
    uint8_t n;

    scanf("%hhu", &n);  

    for(uint8_t i = 0; i < n; i++){
        game();
    }
    return 0;
}