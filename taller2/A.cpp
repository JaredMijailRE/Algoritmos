// https://vjudge.net/contest/721278#problem/A

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/A.cpp


#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <tuple>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

// definimos el tipo matrix
using Matrix = vector<vector<char>>;
using u16 = uint_fast16_t;
using point = tuple<u16, u16>;


Matrix getLabyrinth(point *inicio, point *meta){
    u16 height, width;
    point& inicioPunto = *inicio;
    point& metaPunto = *meta;
    cin >> height >> width;
    cin.ignore();
    
    Matrix labyrinth;
    getchar(); // consumimos el salto de linea
    string row;
    for (u16 i = 0; i < height; i++) {
        getline(cin, row);
        labyrinth.push_back(vector<char>(row.begin(), row.end()));
        u16 posInicio = row.find("A");
        u16 posMeta = row.find("B");

        if(posInicio != -1){
            inicioPunto = {i, posInicio};
        }

        if(posMeta != -1){
            metaPunto = {i, posMeta};
        }
    }

    return labyrinth;
}

void solveLabyrinth(point inicio, point meta, Matrix labyrinth) {
    // usamos algoritmo A*
    u16 height = labyrinth.size();
    u16 width = labyrinth[0].size();

    vector<vector<bool>> visited(height, vector<bool>(width, false));
    map<point, pair<point, char>> parent;

    queue<point> q;
    q.push(inicio);
    visited[get<0>(inicio)][get<1>(inicio)] = true;

    vector<tuple<int_fast8_t, int_fast8_t, char>> dirs = {
        {-1, 0, 'U'},
        {1, 0, 'D'},
        {0, -1, 'L'},
        {0, 1, 'R'}
    };

    bool found = false;

    while (!q.empty()) {
        point current = q.front();
        q.pop();

        if (current == meta) {
            found = true;
            break;
        }

        u16 x = get<0>(current);
        u16 y = get<1>(current);

        for (auto [dx, dy, dir] : dirs) {
            u16 nx = x + dx;
            u16 ny = y + dy;

            if (nx < height && ny < width && !visited[nx][ny] && labyrinth[nx][ny] != '#') {
                visited[nx][ny] = true;
                point next = {nx, ny};
                parent[next] = {current, dir};
                q.push(next);
            }
        }
    }

    if (!found) {
        cout << "NO" << endl;
        return;
    }

    // reconstruir camino
    string path;
    point curr = meta;
    while (curr != inicio) {
        auto [prev, dir] = parent[curr];
        path += dir;
        curr = prev;
    }

    reverse(path.begin(), path.end());

    cout << "YES" << endl;
    cout << path.size() << endl;
    cout << path << endl;
}

int main() {
    point inicio, meta;

    Matrix laberinto = getLabyrinth(&inicio, &meta);
    solveLabyrinth(inicio, meta, laberinto);

    return 0;
}