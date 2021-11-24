/** Header **/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** Const variable **/
#define MAX 5       // Item의 개수
#define W 9         // 주어진 문제의 가방 용량
#define true 1
#define false 0
#define maximum(x,y) (((x) > (y)) ? (x) : (y))

#define dpMAX 3
#define dpW 30

const int dpp[dpMAX + 1] = {0, 50, 60, 140};
const int dpw[dpMAX + 1] = {0, 5, 10, 20};

const int p[MAX + 1] = {0, 20, 30, 35, 12, 3};   // item.Profit
const int w[MAX + 1] = {0, 2, 5, 7, 3, 1};       // item.Weight

int P[dpMAX + 1][dpW + 1] = {0};

/** Struct variable **/
typedef struct node{
    int level;
    int profit;
    int weight;
    int bound;
    void *next;
} node;

typedef struct queue{
    node *front;    // 맨 앞(꺼낼 위치)
    node *rear;     // 맨 뒤(보관할 위치)
    int count;      // 보관 개수
} queue;

typedef struct priority_queue{
    node **heap;
    int count;
} priority_queue;

/** Common variable **/
int totalweight = 0;
int maxprofit = 0;

/** Common function **/
void _pause(void);
float bound(node *u);

void _pause(void) {
    printf("\tPress any key ...\n");
    getchar();
}

float bound(node *u) {
    int j, totweight;
    float _bound;
    
    if(u->weight >= W) return false;
    else {
        _bound = u->profit;
        j = u->level + 1;
        totweight = u->weight;
        while(j <= MAX && totweight + w[j] <= W) {  // 가능한 한 많은 아이템을 취한다.
            totweight = totweight + w[j];
            _bound = _bound + p[j++];
        }
        if(j <= MAX)
            _bound = _bound + (W - totweight) * p[j] / w[j];
        return _bound;
    }
}

/** DFS_knapsack **/
int numbest;
int bestset[MAX + 1];
int promising(int i, int profit, int weight);
void DFS_knapsack(int i, int profit, int weight, int include[MAX + 1]);
int promising(int i, int profit, int weight) {
    int totweight;
    float _bound;
    if(weight >= W) return false;   // 자식 마디로 확장할 수 있을 때만 마디는 유망하다.
    else {                          // 자식 마디에 쓸 공간이 남아 있어야 한다.
        _bound = profit;
        totweight = weight;
        while(i <= MAX && totweight + w[i] <= W) {  // 가능한 한 많은 아이템을 취한다.
            totweight = totweight + w[i];
            _bound = _bound + p[i++];
        }
        if(i <= MAX)
            _bound = _bound + (W - totweight) * p[i]/w[i];
        return _bound > maxprofit;
    }
}

// 깊이우선탐색
void DFS_knapsack(int i, int profit, int weight, int include[MAX + 1]) {
    if(weight <= W && profit > maxprofit) {                 // 지금까지는 이 집합이 최고이다.
        maxprofit = profit;
        numbest = i;                                        // numbest를 고려한 아이템의 개수로
        memcpy(bestset, include, (MAX + 1) * sizeof(int));  // 놓고, bestset을 이 해답으로 놓는다.
        printf("\tSelect Item: ");
        for(int i = 1; i <= MAX; i++) {
            if(bestset[i] == true)
                printf("\ti%d(%d, %d)", i, w[i], p[i]);
        }
        printf("\n\tprofit: %d\n\n", profit);
    }
    if(promising(i + 1, profit, weight)) {
        include[i + 1] = true;  // w[i + 1] 포함
        DFS_knapsack(i + 1, profit + p[i + 1], weight + w[i + 1], include);
        include[i + 1] = false; // w[i + 1] 비포함
        DFS_knapsack(i + 1, profit, weight, include);
    }
}
/** BFS_knapsack **/
void init_q(queue *q);
void enqueue(node *v, queue *q);
node *dequeue(queue *q);
int q_is_empty(queue *q);
void BFS_knapsack(queue *q, node *v);
void init_q(queue *q) {
    q->front = q->rear = NULL;  // front와 rear를 NULL로 설정
    q->count = 0;               // 보관 개수를 0으로 설정
}

void enqueue(node *v, queue *q) {
    if (q_is_empty(q))      //큐가 비어있을 때
        q->front = v;
    else q->rear->next = v; // 큐가 비어있지 않을 때
    q->rear = v;            // 맨 뒤를 now로 설정
    q->count++;             // 보관 개수를 1 증가
}

node *dequeue(queue *q) {
    node *temp;
    if (q_is_empty(q)) return NULL;
    
    temp = q->front;        //맨 앞의 노드를 now에 기억
    q->front = temp->next;  //맨 앞은 now의 다음 노드로 설정
    q->count--;             //보관 개수를 1 감소
    printf("\t----- dequeue() -----\n\tLevel:%d\n\tProfit:%d\n\tWeight:%d\n\tBound:%d\n\n", temp->level, temp->profit, temp->weight, temp->bound);
    return temp;
}

int q_is_empty(queue *q) {
    return q->count == 0;
}

void BFS_knapsack(queue *q, node *v) {
    node *u;
    v->level = v->profit = v->weight = 0;
    v->bound = bound(v);
    enqueue(v, q);
    
    while(!q_is_empty(q)) {
        v = dequeue(q);
        u = malloc(sizeof(node));
        u->level = v->level + 1;            // u를 v의 자식마디로 놓음
        u->profit = v->profit + p[u->level]; // u를 다음 아이템을 포함하는
        u->weight = v->weight + w[u->level]; // 자식마디로 놓음
        u->bound = bound(u);
        if(u->weight <= W && u->profit > maxprofit)
            maxprofit = u->profit;
        if(u->bound > maxprofit)
            enqueue(u, q);
        
        u = malloc(sizeof(node));
        u->level = v->level + 1;
        u->weight = v->weight;    // u를 다음 아이템을 포함하지 않는
        u->profit = v->profit;    // 자식마디로 놓음
        u->bound = bound(u);
        if(u->bound > maxprofit)
            enqueue(u, q);
    }
}

/** BF_knapsack **/
void init_priority_q(priority_queue *p_q);
int pq_is_empty(priority_queue *p_q);
void insert(priority_queue *p_q, node *v);
node *delete(priority_queue *p_q);
void BF_knapsack(priority_queue *p_q, node *v);
int get_parent(int i);
int get_left(int i);
int get_right(int i);

void init_priority_q(priority_queue *p_q) {
    p_q->heap = calloc(1024, sizeof(node *));
    p_q->count = 0;
}

int pq_is_empty(priority_queue *p_q) {
    return p_q->count == 0;
}

int get_parent(int i) {
    return i / 2;
}

int get_left(int i) {
    return i * 2;
}

int get_right(int i) {
    return i * 2 + 1;
}

void insert(priority_queue *p_q, node *v) {
    int index;
    node *temp;
    p_q->heap[++p_q->count] = v;
    index = get_parent(p_q->count);
    while (index > 0) {
        if(p_q->heap[get_left(index)] != NULL)
            if (p_q->heap[index]->bound < p_q->heap[get_left(index)]->bound) {
                temp = p_q->heap[index];
                p_q->heap[index] = p_q->heap[get_left(index)];
                p_q->heap[get_left(index)] = temp;
            }
        if(p_q->heap[get_right(index)] != NULL)
            if (p_q->heap[index]->bound < p_q->heap[get_right(index)]->bound) {
                temp = p_q->heap[index];
                p_q->heap[index] = p_q->heap[get_right(index)];
                p_q->heap[get_right(index)] = temp;
            }
        index = get_parent(index);
    }
}

node *delete(priority_queue *p_q) {
    int i, tempNo;
    
    node *answer = p_q->heap[1];            // 부모 노드를 가져옴
    p_q->heap[1] = p_q->heap[p_q->count--]; // 마지막 노드를 가져옴
    
    printf("\t----- delete() -----\n\tLevel:%d\n\tProfit:%d\n\tWeight:%d\n\tBound:%d\n\n", answer->level, answer->profit, answer->weight, answer->bound);
    
    tempNo = p_q->count;    // Heap 화
    p_q->count = 0;
    for (i = 1; i <= tempNo; i++)
        insert(p_q, p_q->heap[i]);
    
    return answer;
}


void BF_knapsack(priority_queue *p_q, node *v) {
    node *u;
    v->level = v->profit = v->weight = 0;
    v->bound = bound(v);
    insert(p_q, v);
    while(!pq_is_empty(p_q)) {  // 최고의 한계값을 가진 마디 제거
        v = delete(p_q);
        if(v->bound > maxprofit) {  // 마디가 아직 유망한지 검사
            u = malloc(sizeof(node));
            u->level = v->level + 1;
            u->profit = v->profit + p[u->level]; // u를 다음 아이템을 포함하는
            u->weight = v->weight + w[u->level]; // 자식마디로 놓음
            if(u->weight <= W && u->profit > maxprofit)
                maxprofit = u->profit;
            u->bound = bound(u);
            if(u->bound > maxprofit) {
                insert(p_q, u);
            }
            
            u = malloc(sizeof(node));
            u->level = v->level + 1;
            u->weight = v->weight;    // u를 다음 아이템을 포함하지 않는
            u->profit = v->profit;    // 자식마디로 놓음
            u->bound = bound(u);
            if(u->bound > maxprofit) {
                insert(p_q, u);
            }
        }
    }
}

void DP_Knapsack(void) {
    int i, j;
    for(i = 1; i <= dpMAX; i++) {
        for(j = 1; j <= dpW; j++) {
            if(dpw[i] > j) {
                P[i][j] = P[i - 1][j];
            } else {
                printf("계산\n");
                P[i][j] = maximum(dpp[i] + P[i-1][j-dpw[i]], P[i-1][j]);
            }
            printf("\tP[%d][%d] = %d\n", i, j, P[i][j]);
        }
    }
}
int main(void) {
    while (1) {
        int select_num = 0;
        clock_t s_time, e_time;
        double res_time;
        printf("\t1. DFS_knapsack()\n");
        printf("\t2. BFS_knapsack()\n");
        printf("\t3. BF_knapsack()\n");
        printf("\t4. DP_knapsack()\n");
        printf("\t0. Exit\n");
        printf("\tInput Number: ");
        scanf("%d", &select_num);
        getchar();
        totalweight = 0;
        maxprofit = 0;
        switch (select_num) {
            case 0:
                return 0;
            case 1: // Solve Knapsack Problem by using Dynmaic Programming.
                printf("\n\t========== DFS_knapsack() ==========\n\n");
                int include[MAX + 1] = {0};
                s_time = clock();
                DFS_knapsack(0, 0, 0, include);
                e_time = clock();
                res_time = (double)e_time - (double)s_time;
                printf("\tBest set: ");
                for(int i = 1; i <= MAX; i++) {
                    if(bestset[i] == true)
                        printf("\ti%d(%d, %d)", i, w[i], p[i]);
                }
                printf("\n\tmaxprofit: %d\n", maxprofit);
                printf("\tperformance time : %fms\n\n\n", res_time);
                _pause();
                break;
            case 2: // Solve Knapsack Problem by using Dynmaic Programming.
                printf("\n\t========== BFS_knapsack() ==========\n\n");
                node *v1 = malloc(sizeof(node));
                queue *q = malloc(sizeof(queue));
                init_q(q);
                s_time = clock();
                BFS_knapsack(q, v1);
                e_time = clock();
                res_time = (double)e_time - (double)s_time;
                printf("\tmaxprofit: %d\n", maxprofit);
                printf("\tperformance time : %fms\n\n\n", res_time);
                _pause();
                break;
            case 3:
                printf("\n\t========== BF_knapsack() ==========\n\n");
                node *v2 = malloc(sizeof(node));
                priority_queue *p_q = malloc(sizeof(priority_queue));
                init_priority_q(p_q);
                s_time = clock();
                BF_knapsack(p_q, v2);
                e_time = clock();
                res_time = (double)e_time - (double)s_time;
                printf("\tmaxprofit: %d\n", maxprofit);
                printf("\tperformance time : %fms\n\n\n", res_time);
                _pause();
                break;
            case 4:
                printf("\n\t========== DP_knapsack() ==========\n\n");
                s_time = clock();
                DP_Knapsack();
                e_time = clock();
                res_time = (double)e_time - (double)s_time;
                _pause();
                break;
            default:
                break;
        }
    }
    return 0;
}
