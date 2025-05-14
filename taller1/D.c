// https://vjudge.net/contest/713089#problem/D

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

struct D
{
    int app;
    bool read;
};

struct notiList
{
    int last;
    int len;
    int topTrue;
    struct D *notis;
};

int main()
{
    int n; // applications
    int k; // events
    scanf("%d %d", &n, &k);

    struct notiList list;
    struct D noti[k];
    list.last = 0;
    list.topTrue = 0;
    list.notis = noti;
    list.len = k;

    for (uint8_t i = 0; i < k; i++)
    {
        uint8_t eventType;
        int appNumber;
        scanf("%hhu %d", &eventType, &appNumber);

        switch (eventType)
        {
        case 1:
        {
            struct D d = {.app = appNumber, .read = false};
            list.notis[list.last++] = d;
            break;
        }

        case 2:
            for (int i = list.topTrue; i < list.len; i++)
            {
                if (list.notis[i].app == appNumber)
                {
                    list.notis[i].read = true;
                }
            }
            break;

        case 3:
            list.topTrue = appNumber;
            break;
        }

        int count = 0;
        for (int i = list.topTrue; i < list.last; i++)
        {
            if (!list.notis[i].read)
            {
                count++;
            }
        }
        printf("%i\n", count);
    }
    return 0;
}