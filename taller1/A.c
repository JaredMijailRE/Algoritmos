// https://vjudge.net/contest/713089#problem/A
#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort (for sorting integers in ascending order)
int compare_integers(const void *a, const void *b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);

    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

void solve() {
    int n;
    // Read n (number of moves)
    scanf("%d", &n);

    int size = 2 * n;
    int a[size]; // Declare array to hold 2n integers

    // Read the 2n integers into the array
    for (int i = 0; i < size; i++) {
        scanf("%d", &a[i]);
    }

    // Sort the array using qsort
    // qsort requires the base address of the array, the number of elements,
    // the size of each element, and a comparison function.
    qsort(a, size, sizeof(int), compare_integers);

    // Calculate the maximum score
    // Use long long to avoid potential overflow, as the score can be large.
    long long max_score = 0;

    // Sum the elements at even indices (0, 2, 4, ...)
    // This corresponds to adding the minimum of each adjacent pair in the sorted array.
    for (int i = 0; i < size; i += 2) {
        // Since the array is sorted, a[i] <= a[i+1].
        // The minimum of the pair (a[i], a[i+1]) is a[i].
        max_score += a[i];
    }

    // Print the result for the current test case
    printf("%lld\n", max_score);
}

int main() {
    int t;
    // Read the number of test cases
    scanf("%d", &t);

    // Process each test case
    while (t--) {
        solve();
    }

    return 0;
}