// https://vjudge.net/contest/721278#problem/I

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/I.cpp

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;
    
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    
    if (grid[0][0] == '.') {
        dp[0][0] = 1;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '*') {
                dp[i][j] = 0;
                continue;
            }
            
            if (i > 0) {
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            }
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
            }
        }
    }
    
    cout << dp[n-1][n-1] << endl;
    
    return 0;
}