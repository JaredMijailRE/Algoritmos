// IsItaCat.cu
#include <bits/stdc++.h>
#include <cuda_runtime.h>

// Dispositivo: función que comprueba el patrón meow en una cadena
__device__ bool check_meow(const char* text, int len) {
    if (len < 4) return false;

    int stage = 0;  // 0=m, 1=e, 2=o, 3=w
    int i = 0;

    // debe empezar con al menos un 'm'/'M'
    if (!(text[0]=='m' || text[0]=='M')) return false;

    while (i < len) {
        char c = text[i];
        switch (stage) {
            case 0:
                if (c=='m' || c=='M') {
                    ++i;
                } else {
                    // pasamos a fase 'e'
                    if (c=='e' || c=='E') {
                        stage = 1;
                        ++i;
                    } else {
                        return false;
                    }
                }
                break;
            case 1:
                if (c=='e' || c=='E') {
                    ++i;
                } else {
                    // pasamos a fase 'o'
                    if (c=='o' || c=='O') {
                        stage = 2;
                        ++i;
                    } else {
                        return false;
                    }
                }
                break;
            case 2:
                if (c=='o' || c=='O') {
                    ++i;
                } else {
                    // pasamos a fase 'w'
                    if (c=='w' || c=='W') {
                        stage = 3;
                        ++i;
                    } else {
                        return false;
                    }
                }
                break;
            case 3:
                // solo 'w'/'W' hasta el final
                if (c=='w' || c=='W') {
                    ++i;
                } else {
                    return false;
                }
                break;
        }
    }

    // la última fase debe ser la 3 y haber leído todo
    return (stage == 3);
}

__global__ void isCatKernel(const char* texts, const int* offsets, const int* lengths, bool* result) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    const char* my_text = texts + offsets[idx];
    int len = lengths[idx];
    result[idx] = check_meow(my_text, len);
}

int main(){
    int t;
    if (scanf("%d", &t)!=1) return 0;

    // Host arrays
    std::vector<int> h_len(t), h_off(t);
    std::vector<char> h_text; 
    h_text.reserve(t*50 + 1);

    // Leemos cada caso y concatenamos en un solo buffer
    int offset = 0;
    for(int i = 0; i < t; ++i){
        int n; scanf("%d", &n);
        h_len[i] = n;
        h_off[i] = offset;
        // leemos la cadena (sin espacios)
        std::string s;
        scanf("%s", &s[0]);
        // asegurarnos de que s tenga tamaño n
        s.resize(n);
        // copiamos a buffer
        for(char c: s){
            h_text.push_back(c);
        }
        offset += n;
    }

    // Device arrays
    char*   d_text;
    int*    d_off;
    int*    d_len;
    bool*   d_res;

    cudaMalloc(&d_text, h_text.size() * sizeof(char));
    cudaMalloc(&d_off,  t     * sizeof(int));
    cudaMalloc(&d_len,  t     * sizeof(int));
    cudaMalloc(&d_res,  t     * sizeof(bool));

    cudaMemcpy(d_text, h_text.data(), h_text.size() * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_off,  h_off.data(),  t     * sizeof(int),  cudaMemcpyHostToDevice);
    cudaMemcpy(d_len,  h_len.data(),  t     * sizeof(int),  cudaMemcpyHostToDevice);

    // Lanzamos un grid de (t) hilos
    int threads = 256;
    int blocks  = (t + threads - 1) / threads;
    isCatKernel<<<blocks, threads>>>(d_text, d_off, d_len, d_res);

    cudaDeviceSynchronize();

    // Copiamos resultados de vuelta
    std::vector<bool> h_res(t);
    cudaMemcpy(h_res.data(), d_res, t * sizeof(bool), cudaMemcpyDeviceToHost);

    // Imprimimos YES/NO
    for(bool ok: h_res){
        printf("%s\n", ok ? "YES" : "NO");
    }

    // Liberamos
    cudaFree(d_text);
    cudaFree(d_off);
    cudaFree(d_len);
    cudaFree(d_res);

    return 0;
}
