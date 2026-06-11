#define MOD 1000000007LL

typedef struct Node {
    int v;
    struct Node *next;
} Node;

long long modPow(long long a, long long b) {
    long long res = 1;
    
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        
        a = (a * a) % MOD;
        b >>= 1;
    }
    
    return res;
}

int countNodes(int** edges, int edgesSize) {
    int mx = 0;
    
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][0] > mx) mx = edges[i][0];
        if (edges[i][1] > mx) mx = edges[i][1];
    }
    
    return mx;
}

int assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize) {
    int n = countNodes(edges, edgesSize);

    Node **adj = (Node **)calloc(n + 1, sizeof(Node *));
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        Node *a = (Node *)malloc(sizeof(Node));
        a->v = v;
        a->next = adj[u];
        adj[u] = a;

        Node *b = (Node *)malloc(sizeof(Node));
        b->v = u;
        b->next = adj[v];
        adj[v] = b;
    }

    int *depth = (int *)calloc(n + 1, sizeof(int));
    int *vis = (int *)calloc(n + 1, sizeof(int));
    int *queue = (int *)malloc((n + 5) * sizeof(int));

    int front = 0, rear = 0;
    queue[rear++] = 1;
    vis[1] = 1;

    int maxDepth = 0;

    while (front < rear) {
        int u = queue[front++];

        if (depth[u] > maxDepth)
            maxDepth = depth[u];

        for (Node *cur = adj[u]; cur; cur = cur->next) {
            int v = cur->v;

            if (!vis[v]) {
                vis[v] = 1;
                depth[v] = depth[u] + 1;
                queue[rear++] = v;
            }
        }
    }

    long long ans = modPow(2, maxDepth - 1);

    free(depth);
    free(vis);
    free(queue);

    for (int i = 1; i <= n; i++) {
        Node *cur = adj[i];
        while (cur) {
            Node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(adj);

    return (int)ans;
}