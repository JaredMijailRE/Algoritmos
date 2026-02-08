// https://vjudge.net/contest/721278#problem/E

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/E.cpp

#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int from, to;
    long long weight;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }
    
    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);
    
    for (int iter = 0; iter < n; iter++) {
        bool changed = false;
        for (const Edge& e : edges) {
            if (dist[e.from] + e.weight < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.weight;
                parent[e.to] = e.from;
                changed = true;
            }
        }
        if (!changed) break;
    }
    
    int cycle_start = -1;
    for (const Edge& e : edges) {
        if (dist[e.from] + e.weight < dist[e.to]) {
            cycle_start = e.to;
            break;
        }
    }
    
    if (cycle_start == -1) {
        cout << "NO" << endl;
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        cycle_start = parent[cycle_start];
    }
    
    vector<int> cycle;
    int v = cycle_start;
    while (true) {
        cycle.push_back(v);
        v = parent[v];
        if (v == cycle_start) break;
    }
    
    cout << "YES" << endl;
    for (int i = cycle.size() - 1; i >= 0; i--) {
        cout << cycle[i];
        if (i > 0) cout << " ";
    }
    cout << endl;
    
    return 0;
}