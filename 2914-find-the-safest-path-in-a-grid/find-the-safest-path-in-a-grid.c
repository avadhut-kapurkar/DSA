#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x, y;
} Node;

typedef struct {
    int x, y, val;
} HeapNode;

int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

void swap(HeapNode *a, HeapNode *b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

void push(HeapNode *heap, int *sz, HeapNode node) {
    int i = (*sz)++;
    heap[i] = node;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].val >= heap[i].val) break;
        swap(&heap[p], &heap[i]);
        i = p;
    }
}

HeapNode pop(HeapNode *heap, int *sz) {
    HeapNode res = heap[0];
    heap[0] = heap[--(*sz)];
    int i = 0;
    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;
        if (l < *sz && heap[l].val > heap[largest].val) largest = l;
        if (r < *sz && heap[r].val > heap[largest].val) largest = r;
        if (largest == i) break;
        swap(&heap[i], &heap[largest]);
        i = largest;
    }
    return res;
}

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int total = n * n;

    int **dist = (int **)malloc(n * sizeof(int *));
    bool **vis = (bool **)malloc(n * sizeof(bool *));
    int **best = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dist[i] = (int *)malloc(n * sizeof(int));
        vis[i] = (bool *)calloc(n, sizeof(bool));
        best[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dist[i][j] = -1;
            best[i][j] = -1;
        }
    }

    Node *q = (Node *)malloc(total * sizeof(Node));
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                dist[i][j] = 0;
                q[rear++] = (Node){i, j};
            }
        }
    }

    while (front < rear) {
        Node cur = q[front++];
        for (int k = 0; k < 4; k++) {
            int nx = cur.x + dirs[k][0];
            int ny = cur.y + dirs[k][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[cur.x][cur.y] + 1;
                q[rear++] = (Node){nx, ny};
            }
        }
    }

    HeapNode *heap = (HeapNode *)malloc(total * sizeof(HeapNode));
    int hsz = 0;
    best[0][0] = dist[0][0];
    push(heap, &hsz, (HeapNode){0, 0, dist[0][0]});

    while (hsz > 0) {
        HeapNode cur = pop(heap, &hsz);
        int x = cur.x, y = cur.y;
        if (vis[x][y]) continue;
        vis[x][y] = true;
        if (x == n - 1 && y == n - 1) {
            int ans = cur.val;
            for (int i = 0; i < n; i++) {
                free(dist[i]);
                free(vis[i]);
                free(best[i]);
            }
            free(dist);
            free(vis);
            free(best);
            free(q);
            free(heap);
            return ans;
        }
        for (int k = 0; k < 4; k++) {
            int nx = x + dirs[k][0];
            int ny = y + dirs[k][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny]) {
                int val = dist[nx][ny];
                if (cur.val < val) val = cur.val;
                if (val > best[nx][ny]) {
                    best[nx][ny] = val;
                    push(heap, &hsz, (HeapNode){nx, ny, val});
                }
            }
        }
    }

    return 0;
}