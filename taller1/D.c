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
    struct D* notis;
};

void event1(int appNum, struct notiList* listb){   
    struct notiList list = *listb;
    struct D d;
    d.read = false;
    d.app = appNum;
    list.notis[list.last] = d;
}

void event2(int appNum, struct notiList* listb)
{
    struct notiList list = *listb;
    for( int i = 0; i < list.len; i++){
        if(list.notis[i].app == appNum){
            list.notis[i].read = true;
        }
    }
};

void event3(int readNoti, struct notiList* listb)
{
    struct notiList list = *listb;
    for( int i = 0; i < readNoti; i++){
        list.notis[i].read = true;

    }
};

void countNoti(struct notiList list){
    int count = 0;
    for( int i = 0; i < list.len; i++){
        if(!list.notis[i].read){
            count++;
        }
    }
    printf("%i", count);
}



int main(){
    int n; // applications
    int k; // events
    scanf("%d %d", &n, &k);

    struct notiList list;
    struct D noti[k];
    list.last = 0;
    list.notis = &noti;
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
        }

        countNoti(list);

    }


    return 0;
}