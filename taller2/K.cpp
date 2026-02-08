#include <iostream>
#include <vector>
#include <queue>

int main() {
    int totalMaterias, maxMateriasPorPeriodo;
    std::cin >> totalMaterias >> maxMateriasPorPeriodo;
    std::vector<int> dependencias(totalMaterias + 1);
    for (int idx = 1; idx <= totalMaterias; ++idx) {
        std::cin >> dependencias[idx];
    }
    std::vector<int> longitudCamino(totalMaterias + 1, 0);
    for (int idx = 1; idx <= totalMaterias; ++idx) {
        if (longitudCamino[idx] == 0) {
            std::vector<int> recorrido;
            int actual = idx;
            while (actual != 0 && longitudCamino[actual] == 0) {
                recorrido.push_back(actual);
                actual = dependencias[actual];
            }
            int largo = (actual == 0) ? 0 : longitudCamino[actual];
            for (int i = recorrido.size() - 1; i >= 0; --i) {
                ++largo;
                longitudCamino[recorrido[i]] = largo;
            }
        }
    }
    std::vector<int> entradas(totalMaterias + 1, 0);
    for (int idx = 1; idx <= totalMaterias; ++idx) {
        if (dependencias[idx] != 0) {
            entradas[dependencias[idx]]++;
        }
    }
    using Par = std::pair<int, int>;
    std::priority_queue<Par> cola;
    for (int idx = 1; idx <= totalMaterias; ++idx) {
        if (entradas[idx] == 0) {
            cola.push({longitudCamino[idx], idx});
        }
    }
    int periodos = 0;
    while (!cola.empty()) {
        int tomar = std::min((int)cola.size(), maxMateriasPorPeriodo);
        std::vector<int> seleccionados;
        for (int i = 0; i < tomar; ++i) {
            seleccionados.push_back(cola.top().second);
            cola.pop();
        }
        for (int materia : seleccionados) {
            int siguiente = dependencias[materia];
            if (siguiente != 0) {
                entradas[siguiente]--;
                if (entradas[siguiente] == 0) {
                    cola.push({longitudCamino[siguiente], siguiente});
                }
            }
        }
        ++periodos;
    }
    std::cout << periodos << std::endl;
    return 0;
}

