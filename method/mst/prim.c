//
//  prim.c
//  MinimumSpanningTree
//
//  Created by 김병준 on 2019/12/08.
//  Copyright © 2019 김병준. All rights reserved.
//

#include <stdio.h>
#define MAX 10
#define INF 987654321
#define true 1
#define false -1

// W = 이음선의 가중치(존재O=가중치, 존재X=INF, i==j = 0)
const int W[MAX][MAX] = {
    {0, 32, INF, 17, INF, INF, INF, INF, INF, INF},
    {32, 0, INF, INF, 45, INF, INF, INF, INF, INF},
    {INF, INF, 0, 18, INF, INF, 5, INF, INF, INF},
    {17, INF, 18, 0, 10, INF, INF, 3, INF, INF},
    {INF, 45, INF, 10, 0, 28, INF, INF, 25, INF},
    {INF, INF, INF, INF, 28, 0, INF, INF, INF, 6},
    {INF, INF, 5, INF, INF, INF, 0, 59, INF, INF},
    {INF, INF, INF, 3, INF, INF, 59, 0, 4, INF},
    {INF, INF, INF, INF, 25, INF, INF, 4, 0, 12},
    {INF, INF, INF, INF, INF, 6, INF, INF, 12, 0}
};

/*
    일정 시간복잡도: (n-1) + (n-1)^2 = 0(n^2)
    프림 알고리즘이 신장트리를 구축하는 것은 확실하다.
    그러나 필연적으로 최소비용이 되는지에 대한 증명을 할 필요가 있다.
 
    * 정의
    1. 비방향 그래프 G=(V, E)가 있다고 하자.
    2. E의 부분집합 F에다 최소비용 신장트리가 되도록 이음선을 추가할 수 있으면 F는 유망하다(Promising)고 한다.
 
    * 보조정리
    3. 그렇다면 F를 E의 유망한 부분집합, Y를 F에 속한 이음선으로 연결된 마디의 집합일 때
    4. Y에 속한 마디를 V-Y에 속한 마디로 연결하는 이음선 중에 가중치가 최소인 이음선을 e라 하면 F U {e}는 유망하다를 증명하시오.
 
    증명(Optimality Proof):
    F는 유망하므로 다음관계가 성립하는 이음선의 집합 F'가 반드시 존재하고
                            F <= F'
    (V, F')는 최소비용 신장트리가 된다. 만약 e <= F'라면 다음 관계가 성립한다.
                        F U {e} <= F'
    이는 F U {e}가 유망하다는 것을 의미한다.
 
    그렇지 않으면(e <= F')가 아니면 (V, F')는 신장트리이므로 F U {e}는 정확하게 하나의 순환경로를 포함하게 되고,
    e는 반드시 그 순환경로 상에 한 이음선이 되어야 한다.
    Y에 속한 마디에서 V - Y에 속한 마디를 연결하는 어떤 다른 이음선 e' <= F'도 그 순환 경로 상에 반드시 속해있게 된다.
    F' U {e}에서 e'를 제거하면 순환경로는 없어지게 되며, 다시 신장트리가 된다.
    그런데 e는 Y에 속한 한 마디에서 V - Y에 속한 마디를 연결하는 이음선 중에 가중치가 최소인 이음선이기 때문에
    e의 가중치는 e'의 가중치보다 반드시 작거나 같아야 한다.
    그래서 다음은 최소비용 신장트리가 된다.
                        F' U {e} - {e'}
    결론적으로 e'는 F에 절대로 속할 수 없으므로(F에 속한 이음선들은 Y에 속한 마디들만 연결하므로)
                    F U {e} <= F' U {e} - {e'}
    위 식이 성립된다. 따라서 F U {e}는 유망하고, 그래서 증명이 완료된다.
 
    
*/
void prim(int n) {
    int i;
    int vnear;
    int min;
    int nearest[MAX];
    int distance[MAX];
    
    for(i = 2; i <= n; i++) {   // n - 1회 반복
        nearest[i] = n;         // 처음 시작은 시작점으로 준 마디와 연결되어있음
        distance[i] = W[n][i];
    }
    
    for(int j = 1; j <= n-1; j++) { // n - 1회 반복
        min = INF;
        for(i = 2; i <= n; i++) {
            if(0 <= distance[i] <= min) {   // 만약 최솟값보다 가까운 마디가 존재한다면
                min = distance[i];          // 최솟값을 해당 마디로의 거리로 설정
                vnear = i;                  // 가장 가까운 마디를 해당 마디로 설정
            }
        }
        
        // vnear와 트리를 연결하는 이음선 e를 Y에 추가한다.
        distance[vnear] = false;            // 해당 이음선을 추가하면 현재 vnear 마디는 더이상 탐색할 필요가 없으므로 false 처리
        for(i = 2; i <= n; i++) {           // Y에 속하지 않은 각 마디에 대하여
            if(W[i][vnear] < distance[i]) { // 갱신한 트리에서 인접한 마디에 대한 거리 갱신한다.
                distance[i] = W[i][vnear];  // n - 1회 반복
                nearest[i] = vnear;
            }
        }
    }
}
