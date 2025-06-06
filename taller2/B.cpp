// // https://vjudge.net/contest/721278#problem/B

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/B.cpp

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


Matrix getBuilding() {
    u16 height, width;
    cin >> height >> width;

    Matrix building(height, vector<char>(width));
    string row;
    for (u16 i = 0; i < height; i++) {
        cin >> row;  // leemos exactamente m caracteres
        for (u16 j = 0; j < width; j++) {
            building[i][j] = row[j];
        }
    }
    return building;
}

void occupyRoom(Matrix &building, u16 x, u16 y){
    u16 height = building.size();
    u16 width = building[0].size();

    // Direcciones: arriba, abajo, izquierda, derecha
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    // Usamos BFS para ocupar todo el cuarto
    queue<point> q;
    q.push({x, y});
    building[x][y] = '#';

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = cx + dx[dir];
            int ny = cy + dy[dir];

            if (nx >= 0 && nx < height && ny >= 0 && ny < width && building[nx][ny] == '.') {
                building[nx][ny] = '#';
                q.push({nx, ny});
            }
        }
    }
}

void countRooms(Matrix &building){
    u16 height = building.size();
    u16 width = building[0].size();

    uint_fast8_t roomCounter = 0;
    for (u16 i = 0; i < height; i++) {
        for (u16 j = 0; j < width; j++) {
            if (building[i][j] == '.'){
                roomCounter += 1;
                occupyRoom(building, i, j);
            }
        }
    }
    cout << static_cast<int>(roomCounter) << endl;
}




int main() {
    
    Matrix building = getBuilding();
    countRooms(building);

    return 0;
}