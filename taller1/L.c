// https://vjudge.net/contest/713089#problem/L
#include <stdio.h>

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int can_clean(long long k_workers, int num_places, const long long trash_amounts[]) {
    long long trash_carried_over = 0;

    for (int i = 0; i < num_places; ++i) {
        long long current_day_trash = trash_amounts[i] + trash_carried_over;

        if (current_day_trash == 0) {
            trash_carried_over = 0;
            continue;
        }

        if (k_workers == 0) { 
             if (current_day_trash > 0) return 0;
             else {
                trash_carried_over = 0;
                continue;
             }
        }

        if (i == num_places - 1) {
            if (current_day_trash > k_workers) {
                return 0; 
            }
            trash_carried_over = 0; 
        } else { 
            long long min_amount_to_move;
            min_amount_to_move = max(0LL, 2LL * (current_day_trash - k_workers));
            
            if (min_amount_to_move > current_day_trash) {
                return 0; 
            }
            
            trash_carried_over = min_amount_to_move;
        }
    }
    return 1; 
}

int main() {
    int n;
    scanf("%d", &n);

    long long t[n]; 
    long long total_initial_trash = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &t[i]);
        total_initial_trash += t[i];
    }

    if (total_initial_trash == 0) {
        printf("0\n");
        return 0;
    }

    long long low = 1; 
    long long high = total_initial_trash + 1; 

    high = total_initial_trash; 

    long long ans = high; 

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (can_clean(mid, n, t)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%lld\n", ans);

    return 0;
}