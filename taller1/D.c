// https://vjudge.net/contest/713089#problem/D

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int *notifApp = malloc((k + 1) * sizeof(int));
    int *next = malloc((k + 1) * sizeof(int));
    bool *read = calloc(k + 1, sizeof(bool));

    int *head = calloc(n + 1, sizeof(int));
    int *tail = calloc(n + 1, sizeof(int));

    int unread = 0;
    int lastClear = 0;
    int t = 0;

    for (int ev = 0; ev < k; ev++)
    {
        uint8_t type;
        int x;
        scanf("%hhu %d", &type, &x);

        switch (type){
        case 1:
            t++;
            notifApp[t] = x;
            next[t] = 0;
            if (tail[x])
            {
                next[tail[x]] = t;
            }
            else
            {
                head[x] = t;
            }
            tail[x] = t;
            unread++;
        break;

        case 2:
            int cur = head[x];
            while (cur)
            {
                if (!read[cur])
                {
                    read[cur] = true;
                    unread--;
                }
                cur = next[cur];
            }

            head[x] = tail[x] = 0;
        break;

        case 3:
            while (lastClear < x)
            {
                lastClear++;
                if (lastClear <= t && !read[lastClear])
                {
                    read[lastClear] = true;
                    unread--;
                }
            }
        break;}

        printf("%d\n", unread);
    }

    free(notifApp);
    free(next);
    free(read);
    free(head);
    free(tail);
    return 0;
}
