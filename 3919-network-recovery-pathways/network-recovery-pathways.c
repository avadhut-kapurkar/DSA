#include <stdlib.h>
#include <stdbool.h>

int findMaxPathScore(int** edges, int edgesSize, int* edgesColSize, bool* online, int onlineSize, long long k) {
    int n = onlineSize;
    int* head = (int*)malloc(n * sizeof(int));
    int* in_degree = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) head[i] = -1;

    int* to = (int*)malloc(edgesSize * sizeof(int));
    int* next = (int*)malloc(edgesSize * sizeof(int));
    int* cost = (int*)malloc(edgesSize * sizeof(int));

    int max_cost = -1;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int c = edges[i][2];
        to[i] = v;
        cost[i] = c;
        next[i] = head[u];
        head[u] = i;
        in_degree[v]++;
        if (c > max_cost) {
            max_cost = c;
        }
    }

    int* topo = (int*)malloc(n * sizeof(int));
    int topo_idx = 0;
    int* q = (int*)malloc(n * sizeof(int));
    int head_q = 0, tail_q = 0;

    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q[tail_q++] = i;
        }
    }

    while (head_q < tail_q) {
        int u = q[head_q++];
        topo[topo_idx++] = u;
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];
            if (--in_degree[v] == 0) {
                q[tail_q++] = v;
            }
        }
    }

    long long* dist = (long long*)malloc(n * sizeof(long long));
    int low = 0, high = max_cost;
    int ans = -1;
    long long INF = 1000000000000000000LL;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        for (int i = 0; i < n; i++) {
            dist[i] = INF;
        }
        dist[0] = 0;

        for (int i = 0; i < n; i++) {
            int u = topo[i];
            if (dist[u] == INF) continue;
            if (u != 0 && u != n - 1 && !online[u]) continue;

            for (int e = head[u]; e != -1; e = next[e]) {
                int v = to[e];
                if (cost[e] >= mid) {
                    if (dist[u] + cost[e] < dist[v]) {
                        dist[v] = dist[u] + cost[e];
                    }
                }
            }
        }

        if (dist[n - 1] <= k) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    free(head);
    free(in_degree);
    free(to);
    free(next);
    free(cost);
    free(topo);
    free(q);
    free(dist);

    return ans;
}