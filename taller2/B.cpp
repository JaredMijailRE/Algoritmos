// // https://vjudge.net/contest/721278#problem/B

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/B.cpp

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;
using Matrix = vector<vector<char>>;
using point = tuple<int, int>;

Matrix getBuilding() {
    int height, width;
    cin >> height >> width;

    Matrix building(height, vector<char>(width));
    string row;
    for (int i = 0; i < height; i++) {
        cin >> row;  
        for (int j = 0; j < width; j++) {
            building[i][j] = row[j];
        }
    }
    return building;
}

void occupyRoom(Matrix &building, int x, int y){
    int height = building.size();
    int width = building[0].size();

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

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
    int height = building.size();
    int width = building[0].size();

    int roomCounter = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (building[i][j] == '.'){
                roomCounter += 1;
                occupyRoom(building, i, j);
            }
        }
    }
    cout << roomCounter << endl;
}

int main() {
    Matrix building = getBuilding();
    countRooms(building);
    return 0;
}
