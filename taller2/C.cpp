// https://vjudge.net/contest/721278#problem/C

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/C.cpp

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> components;

void dfs(int u, int comp) {
    visited[u] = true;
    components[u] = comp;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, comp);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n + 1);
    visited.resize(n + 1, false);
    components.resize(n + 1);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    int numComponents = 0;
    vector<int> representatives;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, numComponents);
            representatives.push_back(i);
            numComponents++;
        }
    }
    
    cout << numComponents - 1 << endl;
    
    for (int i = 1; i < numComponents; i++) {
        cout << representatives[0] << " " << representatives[i] << endl;
    }
    
    return 0;
}