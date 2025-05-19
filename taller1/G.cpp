// https://vjudge.net/contest/713089#problem/G 

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if(!(cin >> T)) return 0;
    vector<unsigned int> A(T);
    unsigned int max_a = 0;
    for(int i = 0; i < T; i++){
        cin >> A[i];
        if(A[i] > max_a) max_a = A[i];
    }
    size_t n_max = (size_t)max_a * 3 + 10;
    vector<double> sum_log(n_max + 1);
    sum_log[0] = 0.0;
    for(size_t i = 1; i <= n_max; ++i){
        sum_log[i] = sum_log[i-1] + log((double)i);
    }
    for(unsigned int a : A){
        double loga = log((double)a);
        size_t lo = 1, hi = n_max;
        while(lo < hi){
            size_t mid = lo + (hi - lo)/2;
            if(sum_log[mid] < mid * loga)
                lo = mid + 1;
            else
                hi = mid;
        }
        cout << lo << "\n";
    }

    return 0;
}
