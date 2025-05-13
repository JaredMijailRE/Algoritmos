// https://vjudge.net/contest/713089#problem/B
    #include <stdio.h>
    #include <stdint.h>


void recover(){
    uint8_t n;
    scanf("%hhu", &n);

    for(uint8_t p = 1; p <= 26; p++){
        for(uint8_t s = 1;s <= 26; s++){
            for(uint8_t t = 1; t <= 26; t++){
                if(p+s+t == n){
                    printf("%c%c%c\n", (char)('a' + p - 1), (char)('a' + s - 1), (char)('a' + t - 1));
                    return;
                }
            }
        }
    }
}

int main() {
    uint8_t t;
    scanf("%hhu", &t);

    for (uint8_t i = 0; i < t; i++){
        recover();
    }


    return 0;
}

