// https://vjudge.net/contest/721278#problem/J

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/J.cpp

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> price(n), pages(n);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }
    
    vector<int> dp(x + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int w = x; w >= price[i]; w--) {
            dp[w] = max(dp[w], dp[w - price[i]] + pages[i]);
        }
    }
    
    cout << dp[x] << endl;
    return 0;
}