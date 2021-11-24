#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W 52
#define MAX 6
#define true 1
#define false 0

void sum_of_subsets(int i, int weight, int total, int include[MAX]);
void find_all_sum_of_subset(int i, int weight, int total, int include[MAX]);
int estimate_sum_of_subsets(int i, int weight, int total, int include[MAX]);
int promising(int i, int weight, int total);
void printSubset(int include[MAX]);

const int w[MAX] = {2, 10, 13, 17, 22, 42};
int back_count = 0;
int all_count = 0;
int tot = 0;
int find_check = false;

int main(void) {
    int include[MAX] = { false };
    srand(time(NULL));
    printf("\tsum_of_subset():\n");
    sum_of_subsets(0, 0, 106, include);
    printf("\tback_count = %d\n\n", back_count);
    printf("\tfind_all_sum_of_subset():\n");
    find_all_sum_of_subset(0, 0, 106, include);
    printf("\tall_count = %d\n\n", all_count);
    printf("\t===== estimate_sum_of_subset():\n");
    for(int i = 0; i < 20; i++) {
        printf("\tseq[%2d] numnodes = %d\n", i + 1, estimate_sum_of_subsets(0, 0, 106, include));
    }
    printf("\tavg = %d\n", tot/20);
    
    return 0;
}

void sum_of_subsets(int i, int weight, int total, int include[MAX]) {
    if(promising(i, weight, total)) {
        back_count++;
        if(weight == W) {
            printSubset(include);
        } else {
            // 들어갔을 때
            include[i] = true;
            sum_of_subsets(i + 1, weight + w[i], total - w[i], include);
            // 안들어갔을 때
            include[i] = false;
            sum_of_subsets(i + 1, weight, total - w[i], include);
            
        }
    }
}

void find_all_sum_of_subset(int i, int weight, int total, int include[MAX]) {
    if(find_check) return;
    all_count++;
    if(weight == W) {
        printSubset(include);
        find_check = true;
    } else {
        if(i < MAX) {
            // 들어갔을 때
            include[i] = true;
            find_all_sum_of_subset(i + 1, weight + w[i], total - w[i], include);
            // 안들어갔을 때
            include[i] = false;
            find_all_sum_of_subset(i + 1, weight, total - w[i], include);
        }
    }
}

int estimate_sum_of_subsets(int i, int weight, int total, int include[MAX]) {
    int
    m = 1, // 각 수준에서 유망한 마디의 개수
    mprod = 1,
    numnodes = 1; // 알고리즘이 만들어 내는 가지친 상태공간트리에서 마디의 개수 추정치
    
    while(m != 0 && i < MAX) {
        mprod = mprod * m;
        if(promising(i, weight, total)) {
            include[i] = rand() % 2;
            if(m != 0 && include[i] == true) {
                weight += w[i];
            }
            numnodes += mprod * 2;
            m = 2; // 유망한 자식 마디개수를 더함
        } else m = 0;
        total -= w[i];
        i++;
    }
    tot += numnodes;
    return numnodes;
}



int promising(int i, int weight, int total) {
    return (weight + total >= W) && (weight == W || weight + w[i] <= W);
}

void printSubset(int include[MAX]) {
    int tot = 0;
    for(int j = 0; j < MAX; j++) {
        if(include[j] == true) {
            tot += w[j];
            printf("\t(%d)", w[j]);
        }
    }
    printf("\n\tweight = %d\n", tot);
}
