#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 8
#define true 1
#define false 0
// jhghj

int col[MAX + 1] = {0};

int promising(int i);
int estimate_n_queens(int n);

int main(void) {
    int
    ret = 0,
    tot = 0;
    srand(time(NULL));
    for(int i = 0; i < 20; i++) {
        ret = estimate_n_queens(MAX);
        tot += ret;
        printf("\tseq[%d]: numnodes = %d\n", i, ret);
    }
    printf("\ttot = %d\tavg = %d\n", tot, tot/20);
    return 0;
}

int estimate_n_queens(int n) {
    int i = 0, j, m = 1;
    int numnodes = 1, mprod = 1;
    int random;

    
    while(m != 0 && i != n) {
        mprod = mprod * m;
        numnodes = numnodes + mprod * n;
        i++;
        m = 0;
        int prom_children[MAX + 1] = {0};
        for(j = 1; j <= n; j++) {
            col[i] = j;
            if(promising(i)) {
                m++;
                prom_children[j] = true;
            }
        }
        if(m != 0) {
            while(1) {
                random = (rand() % MAX) + 1;
                if(prom_children[random] == 1) {
                    j = random;
                    break;
                }
            }
            col[i] = j;
        }
    }
    return numnodes;
}

int promising(int i) {
    int k = 1, Switch = true;
    while(k < i && Switch) {
        if(col[i] == col[k] || abs(col[i] - col[k]) == i - k)
            Switch = false;
        k++;
    }
    return Switch;
    ssss
}
