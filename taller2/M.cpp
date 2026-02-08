#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
const int MAXX = 11;

vector<int> adj[MAXN];
long long dp[MAXN][3][MAXX];
int n;
long long m;
int k, x;

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    vector<long long> temp_dp_less_k(x + 1, 0);
    temp_dp_less_k[0] = 1;
    vector<long long> temp_dp_equal_k(x + 1, 0);
    temp_dp_equal_k[0] = 1;
    vector<long long> temp_dp_greater_k(x + 1, 0);
    temp_dp_greater_k[0] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        vector<long long> new_temp_less_k(x + 1, 0);
        vector<long long> child_total_ways(x + 1, 0);
        for (int i = 0; i <= x; ++i) {
            child_total_ways[i] = (dp[v][0][i] + dp[v][1][i] + dp[v][2][i]) % MOD;
        }
        for (int i = 0; i <= x; ++i) {
            if (temp_dp_less_k[i] == 0) continue;
            for (int j = 0; i + j <= x; ++j) {
                new_temp_less_k[i + j] = (new_temp_less_k[i + j] + temp_dp_less_k[i] * child_total_ways[j]) % MOD;
            }
        }
        temp_dp_less_k = new_temp_less_k;
        vector<long long> new_temp_equal_k(x + 1, 0);
        for (int i = 0; i <= x; ++i) {
            if (temp_dp_equal_k[i] == 0) continue;
            for (int j = 0; i + j <= x; ++j) {
                new_temp_equal_k[i + j] = (new_temp_equal_k[i + j] + temp_dp_equal_k[i] * dp[v][0][j]) % MOD;
            }
        }
        temp_dp_equal_k = new_temp_equal_k;
        vector<long long> new_temp_greater_k(x + 1, 0);
        vector<long long> child_total_ways_no_k(x + 1, 0);
        for (int i = 0; i <= x; ++i) {
            child_total_ways_no_k[i] = (dp[v][0][i] + dp[v][2][i]) % MOD;
        }
        for (int i = 0; i <= x; ++i) {
            if (temp_dp_greater_k[i] == 0) continue;
            for (int j = 0; i + j <= x; ++j) {
                new_temp_greater_k[i + j] = (new_temp_greater_k[i + j] + temp_dp_greater_k[i] * child_total_ways_no_k[j]) % MOD;
            }
        }
        temp_dp_greater_k = new_temp_greater_k;
    }
    for (int i = 0; i <= x; ++i) {
        dp[u][0][i] = (temp_dp_less_k[i] * (k - 1)) % MOD;
    }
    for (int i = 0; i < x; ++i) {
        dp[u][1][i + 1] = temp_dp_equal_k[i];
    }
    dp[u][1][0] = 0;
    for (int i = 0; i <= x; ++i) {
        dp[u][2][i] = (temp_dp_greater_k[i] * (m - k)) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> k >> x;
    dfs(1, 0);
    long long ans = 0;
    for (int i = 0; i <= x; i++) {
        ans = (ans + dp[1][0][i]) % MOD;
        ans = (ans + dp[1][1][i]) % MOD;
        ans = (ans + dp[1][2][i]) % MOD;
    }
    cout << ans << endl;
    return 0;
}