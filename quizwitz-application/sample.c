#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int lower = 1, upper = 20, count = 10, j, num, q[10];
    srand(time(0));
    for (j = 0; j < 10; j++) {
        num = (rand() % (upper - lower + 1)) + lower;
        q[j] = num;
    }
    for (j = 0; j < 10; j++) {
        printf("%d ", q[j]);
    }
    printf("\n");
    return 0;
}
