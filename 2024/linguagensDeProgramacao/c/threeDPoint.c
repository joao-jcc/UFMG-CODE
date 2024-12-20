#include <stdio.h>
#include <stdlib.h>

typedef struct ThreeDPointType { 
    int x; 
    int y; 
    int z; 
    } ThreeDPoint;

typedef struct DateType { 
    int day; 
    int month; 
    int year; } Date;

int main() {
    ThreeDPoint *p = (ThreeDPoint*)malloc(sizeof(ThreeDPoint));
    Date *d;
    char a[] = {7, 0, 0, 0, 7, 0, 0, 0, 30, 7, 0, 0};
    p->x = 7;
    p->y = 7;
    p->z = 1822;
    d = (struct ThreeDPoint*)p;
    printf("%d, %d, %d\n", d->day, d->month, d->year);
    d = (struct ThreeDPoint*)a;
    printf("%d, %d, %d\n", d->day, d->month, d->year);
    }