// https://vjudge.net/contest/713089#problem/F

#include <stdio.h>
#include <stdlib.h>

int higher_bound_search(int A[], int N, int x) {
    int lo = 0, hi = N - 1, pos = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] <= x) {
            if (A[mid] == x) pos = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return pos;
}

int main() {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;
    
    int *A = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int qi = 0; qi < Q; qi++) {
        int x;
        scanf("%d", &x);
        int ans = higher_bound_search(A, N, x);
        printf("%d\n", ans);
    }

    free(A);
    return 0;
}