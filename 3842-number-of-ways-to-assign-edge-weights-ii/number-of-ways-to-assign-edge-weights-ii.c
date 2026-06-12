#define MOD 1000000007
#define LOG 18

typedef struct Node {
    int to;
    struct Node* next;
} Node;

Node **graph;
int *depth;
int **up;
long long *pow2;

void addEdge(int u, int v) {
    Node *a = (Node*)malloc(sizeof(Node));
    a->to = v;
    a->next = graph[u];
    graph[u] = a;

    Node *b = (Node*)malloc(sizeof(Node));
    b->to = u;
    b->next = graph[v];
    graph[v] = b;
}

void dfs(int u, int p) {
    up[u][0] = p;

    for (int j = 1; j < LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }

    Node *cur = graph[u];
    while (cur) {
        int v = cur->to;

        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        cur = cur->next;
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int t = a;
        a = b;
        b = t;
    }

    int diff = depth[a] - depth[b];

    for (int j = LOG - 1; j >= 0; j--) {
        if (diff & (1 << j))
            a = up[a][j];
    }

    if (a == b) return a;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}

int* assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize,
                       int** queries, int queriesSize, int* queriesColSize,
                       int* returnSize) {

    int n = edgesSize + 1;

    graph = (Node**)calloc(n + 1, sizeof(Node*));

    for (int i = 0; i < edgesSize; i++) {
        addEdge(edges[i][0], edges[i][1]);
    }

    depth = (int*)calloc(n + 1, sizeof(int));

    up = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        up[i] = (int*)calloc(LOG, sizeof(int));
    }

    dfs(1, 1);

    pow2 = (long long*)malloc(n * sizeof(long long));
    pow2[0] = 1;

    for (int i = 1; i < n; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    int *ans = (int*)malloc(sizeof(int) * queriesSize);

    for (int i = 0; i < queriesSize; i++) {

        int u = queries[i][0];
        int v = queries[i][1];

        int p = lca(u, v);

        int len = depth[u] + depth[v] - 2 * depth[p];

        if (len == 0)
            ans[i] = 0;
        else
            ans[i] = (int)pow2[len - 1];
    }

    *returnSize = queriesSize;
    return ans;
}