#include <stdio.h>
#include <cuda_runtime.h>

// merge kernel realiza un sort en un area especifica del array
// recibe un puntero al arreglo de entrada, salida, cantidad de elementos y paso
__global__ void mergeKernel(int *d_src, int *d_dst, int n, int step)
{

    // identificador par subarregloas a funcionar
    int pairIdx = blockIdx.x * blockDim.x + threadIdx.x;
    int left = pairIdx * (2 * step);
    if (left >= n)
        return; // si se sale de la longitud del array, nada que hacer

    // ajuste comienzo y fin sub arreglos
    int mid = left + step;
    int right = left + 2 * step;
    if (mid > n)
        mid = n;
    if (right > n)
        right = n;

    int i = left;
    int j = mid;
    int k = left;

    // funcion sub arreglos
    while (i < mid && j < right)
    {
        if (d_src[i] <= d_src[j])
        {
            d_dst[k++] = d_src[i++];
        }
        else
        {
            d_dst[k++] = d_src[j++];
        }
    }

    while (i < mid)
    {
        d_dst[k++] = d_src[i++];
    }
    while (j < right)
    {
        d_dst[k++] = d_src[j++];
    }
}

int main()
{

    int h_arr[] = {1, 5, 3, 7, 8, 9, 5, 6, 9, -10, 834, 83247, -123, -1, 0};
    int n = sizeof(h_arr) / sizeof(h_arr[0]);

    int *d_src = nullptr;
    int *d_dst = nullptr;
    size_t bytes = n * sizeof(int);
    // alocamos memoria en GPU para los dos arreglos que necesitamos
    cudaMalloc((void **)&d_src, bytes);
    cudaMalloc((void **)&d_dst, bytes);
    // copiamos nuestro array
    cudaMemcpy(d_src, h_arr, bytes, cudaMemcpyHostToDevice);

    int step = 1;
    bool srcIsInput = true;
    int passCount = 0;

    while (step < n)
    {

        int numPairs = (n + (2 * step - 1)) / (2 * step);
        if (numPairs <= 0)
            break;

        int blockSize = 128;
        int gridSize = (numPairs + blockSize - 1) / blockSize;

        int *d_input = (srcIsInput ? d_src : d_dst);
        int *d_output = (srcIsInput ? d_dst : d_src);

        // se llama a nuestro kernel
        mergeKernel<<<gridSize, blockSize>>>(d_input, d_output, n, step);
        cudaGetLastError();

        srcIsInput = !srcIsInput;
        step <<= 1;
        passCount++;
    }

    int *d_result = ((passCount & 1) == 0 ? d_src : d_dst);

    cudaMemcpy(h_arr, d_result, bytes, cudaMemcpyDeviceToHost);
    printf("Sorted array:\n");

    // bucle para imprimir el arreglo
    for (int i = 0; i < n; i++)
    {
        printf("%d ", h_arr[i]);
    }
    printf("\n");

    // liberamos memoria GPU
    cudaFree(d_src);
    cudaFree(d_dst);
    return 0;
}
