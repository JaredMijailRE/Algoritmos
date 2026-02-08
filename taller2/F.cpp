// https://vjudge.net/contest/721278#problem/F

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/F.cpp

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 1e18;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
    
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }
    
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }
    
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF) {
            cout << -1 << "\n";
        } else {
            cout << dist[a][b] << "\n";
        }
    }
    
    return 0;
}