#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <map>

int main() {
    int alto, ancho;
    if (!(std::cin >> alto >> ancho)) {
        std::cout << "No" << std::endl;
        return 0;
    }
    std::vector<std::string> laberinto(alto);
    for (int i = 0; i < alto; ++i) {
        std::cin >> laberinto[i];
    }
    std::string ordenes;
    std::cin >> ordenes;
    std::pair<int, int> posJugador = {-1, -1}, posEnemigo = {-1, -1};
    for (int f = 0; f < alto; ++f) {
        for (int c = 0; c < ancho; ++c) {
            if (laberinto[f][c] == 'P') posJugador = {f, c};
            else if (laberinto[f][c] == 'G') posEnemigo = {f, c};
        }
    }
    if (posJugador.first == -1 || posEnemigo.first == -1) {
        std::cout << "No" << std::endl;
        return 0;
    }
    std::vector<std::pair<int, int>> desplazamientos = {{-1,0},{1,0},{0,-1},{0,1}};
    std::map<char, std::pair<int, int>> movJugador = {
        {'U', {-1, 0}}, {'D', {1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}
    };
    std::vector<std::pair<int, int>> recorridoJugador;
    std::set<int> posicionesClave;
    int fJ = posJugador.first, cJ = posJugador.second;
    recorridoJugador.push_back({fJ, cJ});
    posicionesClave.insert(fJ * ancho + cJ);
    for (char mov : ordenes) {
        int df = movJugador[mov].first, dc = movJugador[mov].second;
        int nf = fJ + df, nc = cJ + dc;
        if (!(0 <= nf && nf < alto && 0 <= nc && nc < ancho)) {
            nf = (nf + alto) % alto;
            nc = (nc + ancho) % ancho;
        }
        if (laberinto[nf][nc] != '#') {
            fJ = nf;
            cJ = nc;
        }
        recorridoJugador.push_back({fJ, cJ});
        posicionesClave.insert(fJ * ancho + cJ);
    }
    int totalCeldas = alto * ancho;
    std::vector<int> pasos(totalCeldas, -1);
    std::queue<int> cola;
    int fE = posEnemigo.first, cE = posEnemigo.second;
    int inicioIdx = fE * ancho + cE;
    pasos[inicioIdx] = 0;
    cola.push(inicioIdx);
    int hallados = 0;
    if (posicionesClave.count(inicioIdx)) ++hallados;
    while (!cola.empty() && hallados < (int)posicionesClave.size()) {
        int actual = cola.front(); cola.pop();
        int r = actual / ancho, c = actual % ancho;
        int dist = pasos[actual];
        for (auto [df, dc] : desplazamientos) {
            int nr = r + df, nc = c + dc;
            if (0 <= nr && nr < alto && 0 <= nc && nc < ancho) {
                int nuevoIdx = nr * ancho + nc;
                if (laberinto[nr][nc] != '#' && pasos[nuevoIdx] == -1) {
                    pasos[nuevoIdx] = dist + 1;
                    cola.push(nuevoIdx);
                    if (posicionesClave.count(nuevoIdx)) ++hallados;
                }
            }
        }
    }
    for (size_t t = 0; t < recorridoJugador.size(); ++t) {
        int idx = recorridoJugador[t].first * ancho + recorridoJugador[t].second;
        if (pasos[idx] != -1 && pasos[idx] <= (int)t) {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }
    std::cout << "No" << std::endl;
    return 0;
}
