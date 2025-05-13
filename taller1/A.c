// https://vjudge.net/contest/713089#problem/A
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void minPush(int arr[], uint16_t current_elements, int newElem)
{
    uint16_t j = current_elements;
    while (j > 0 && arr[j - 1] > newElem)
    {
        arr[j] = arr[j - 1];
        j--;
    }
    arr[j] = newElem;
}

void game()
{
    uint8_t n;
    scanf("%hhu", &n);
    uint16_t size = 2 * n;
    int arr[size];

    for (uint16_t i = 0; i < size; i++)
    {
        int e;
        scanf("%d", &e);
        minPush(arr, i, e);
    }

    long long result = 0;

    for (uint8_t i = 0; i < n; i++)
    {
        result += arr[i * 2];
    }

    printf("%lld\n", result);
}

int main()
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
    {
        game();
    }
    return 0;
}