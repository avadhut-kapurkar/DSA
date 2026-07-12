#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Node;

int cmp(const void *a, const void *b) {
    Node *x = (Node *)a;
    Node *y = (Node *)b;
    if (x->val < y->val) return -1;
    if (x->val > y->val) return 1;
    return 0;
}

int* arrayRankTransform(int* arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;
    if (arrSize == 0) return NULL;

    Node *nodes = (Node *)malloc(arrSize * sizeof(Node));
    int *ans = (int *)malloc(arrSize * sizeof(int));

    for (int i = 0; i < arrSize; i++) {
        nodes[i].val = arr[i];
        nodes[i].idx = i;
    }

    qsort(nodes, arrSize, sizeof(Node), cmp);

    int rank = 1;
    ans[nodes[0].idx] = rank;

    for (int i = 1; i < arrSize; i++) {
        if (nodes[i].val != nodes[i - 1].val)
            rank++;
        ans[nodes[i].idx] = rank;
    }

    free(nodes);
    return ans;
}