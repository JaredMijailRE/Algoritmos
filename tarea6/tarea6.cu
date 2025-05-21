#include <stdio.h>
#define N 27  // 3^3
#define ALFABETO "ABC"
#define ALFABETO_LEN 3
#define CADENA_LEN 3

__global__ void generar_cadenas_cuda(char *resultados) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    const char *alfabeto = ALFABETO;
    int id = idx; 

    for (int i = CADENA_LEN - 1; i >= 0; i--) {
        resultados[idx * (CADENA_LEN + 1) + i] = alfabeto[id % ALFABETO_LEN];
        id /= ALFABETO_LEN;
    }

    resultados[idx * (CADENA_LEN + 1) + CADENA_LEN] = '\0';
}


int main() {
    char *d_resultados;
    char h_resultados[N * (CADENA_LEN + 1)];

    // Reservar memoria en GPU
    cudaMalloc((void **)&d_resultados, sizeof(char) * N * (CADENA_LEN + 1));

    // Lanzar kernel
    generar_cadenas_cuda<<<1, N>>>(d_resultados);

    // Copiar resultados a la CPU
    cudaMemcpy(h_resultados, d_resultados, sizeof(char) * N * (CADENA_LEN + 1), cudaMemcpyDeviceToHost);

    // Imprimir resultados
    printf("Cadenas generadas en GPU:\n");
    for (int i = 0; i < N; i++) {
        printf("%s\n", &h_resultados[i * (CADENA_LEN + 1)]);
    }

    // Liberar memoria
    cudaFree(d_resultados);
    return 0;
}
