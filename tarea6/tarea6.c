#include <stdio.h>

#define ALFABETO "ABC"
#define LONG_ALFABETO 3

void generar_cadenas(int n, char *prefijo) {
    if (n == 0) {
        printf("%s\n", prefijo);
        return;
    }

    for (int i = 0; i < LONG_ALFABETO; i++) {
        char nuevo_prefijo[LONG_ALFABETO];  
        sprintf(nuevo_prefijo, "%s%c", prefijo, ALFABETO[i]);
        generar_cadenas(n - 1, nuevo_prefijo);
    }
}

int main() {
    int n = 3;  
    printf("Cadenas de longitud %d generadas:\n", n);
    generar_cadenas(n, "");

    return 0;
}
