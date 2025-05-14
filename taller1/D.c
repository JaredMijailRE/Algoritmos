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
    struct D* notis;
};

void event1(int appNum, struct notiList* list) {
    struct D d = { .app = appNum, .read = false };
    list->notis[list->last++] = d;  
}


void event2(int appNum, struct notiList* list)
{
    for( int i = list->topTrue; i < list->len; i++){
        if(list->notis[i].app == appNum){
            list->notis[i].read = true;
        }
    }
};

void event3(int readNoti, struct notiList* list)
{
    for( int i = list->topTrue; i < readNoti; i++){
        list->notis[i].read = true;
    }
    list->topTrue = readNoti;

};

void countNoti(struct notiList list){
    int count = 0;
    for( int i = list.topTrue; i < list.last; i++){
        if(!list.notis[i].read){
            count++;
        }
    }
    printf("%i\n", count);
}


int main(){
    int n; // applications
    int k; // events
    scanf("%d %d", &n, &k);

    struct notiList list;
    struct D noti[k];
    list.last = 0;
    list.topTrue = 0;
    list.notis = noti;
    list.len = k;

    for(uint8_t i = 0; i < k; i++){
        uint8_t eventType;
        int appNumber;
        scanf("%hhu %i", &eventType, &appNumber);

        switch (eventType)
        {
        case 1:
            event1(appNumber, &list);
            break;
        case 2:
            event2(appNumber, &list);
            break;
        case 3:
            event3(appNumber, &list);
            break;
        }

        countNoti(list);

    }
    return 0;
}