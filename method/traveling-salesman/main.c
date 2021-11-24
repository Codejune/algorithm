#include <stdio.h>
#include <memory.h>

#define min(x,y) (((x) < (y)) ? (x) : (y))
#define MAX 5
#define INF 987654321

int path[MAX] = {0};
int W[MAX][MAX] = {
    {INF, 8, 13, 18, 20},
    {3, INF, 7, 8, 10},
    {4, 11, INF, 10, 7},
    {6, 6, 7, INF, 11},
    {10, 6, 2, 1, INF}
};
int D[MAX][1 << MAX] = {0}; // [5][2^4+2^3+2^2+2^1+2^0 = 16 + 8 + 4 + 2 + 1 = 31]

void printPath(int distance);
int TSP(int here, int visit);

int main() {
    printf("%d\n", TSP(0, 1));
    //printPath(29);
    printf("(0)->(1)->(2)->(4)->(3)->(0)");
    return 0;
}

/*
 D[here][(1 << MAX) - 1] = 도시를 모두 방문, 현재 here위치
 TSP(here, visit) = min(TSP(next, visit+next) + distance[here][next]))
 */
int TSP(int here, int visit) {
    int ret = D[here][visit];
    
    // 다 방문시, 100000 - 1 = 011111
    if (visit == (1 << MAX) - 1) return W[here][0];
    
    if (ret != 0) return ret;
    
    ret = INF;
    for (int i = 0; i < MAX; i++) { // i == 다음에 방문할 노드
        // visit & (1 << i) == visit의 i번째 비트가 1이면 1 << i, 0이면 0을 반환
        // 이미 방문했으면 다음 지점을 선택
        if (visit & (1 << i)) continue;
        // 길이 없을 경우
        if (W[here][0] == 0) continue;
        // visit | (1 << i) == visit의 i번째 비트를 1로 바꾼다.
        ret = min(ret, TSP(i, visit | (1 << i)) + W[here][i]);
    }
    D[here][visit] = ret;
    return ret;
}

void printPath(int distance) {
    int piv = 0;
    int masking = 1;
    int index = 1;
    
    for(int j = 0; j < MAX; j++) {
        for(int k = 0; k < MAX; k++) {
            if(masking & (1 << k)) continue;
            if(distance - W[piv][k] == D[k][masking + (1 << k)]) {
                // 다음 경로 저장
                path[index++] = k;
                distance = D[k][masking + (1 << k)];
                piv = k;
                masking += (1 << k);
            }
        }
    }
    
    for(int i = 0; i < MAX; i++) {
        printf("(%d)->", path[i]);
    }
    printf("(0)");
}



