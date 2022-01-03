#include "epoch.h"
/* Your code here! */
int hours(time_t t) {
    int h = (int)t/3600;
    return h;
}
int days(time_t t) {
    int d = (int)t/86400;
    return d;
}

int years(time_t t) {
    int y = (int)t/31536000;
    return y;
}