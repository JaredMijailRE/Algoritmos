// https://vjudge.net/contest/721278#problem/G

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/G.cpp

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    vector<int> tails;
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(tails.begin(), tails.end(), arr[i]);
        
        if (it == tails.end()) {
            tails.push_back(arr[i]);
        } else {
            *it = arr[i];
        }
    }
    
    cout << tails.size() << endl;
    
    return 0;
}