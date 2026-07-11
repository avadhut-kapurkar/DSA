#include <stdlib.h>
#include <stdbool.h>

void dfs(int node, int** graph, int* size, bool* vis,
         int* vertices, int* degreeSum) {

    vis[node] = true;
    (*vertices)++;
    (*degreeSum) += size[node];

    for (int i = 0; i < size[node]; i++) {
        int nei = graph[node][i];
        if (!vis[nei]) {
            dfs(nei, graph, size, vis, vertices, degreeSum);
        }
    }
}

int countCompleteComponents(int n, int** edges, int edgesSize, int* edgesColSize) {

    int* degree = (int*)calloc(n, sizeof(int));

    // Count degrees
    for (int i = 0; i < edgesSize; i++) {
        degree[edges[i][0]]++;
        degree[edges[i][1]]++;
    }

    // Build adjacency list
    int** graph = (int**)malloc(n * sizeof(int*));
    int* idx = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        graph[i] = (int*)malloc(degree[i] * sizeof(int));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][idx[u]++] = v;
        graph[v][idx[v]++] = u;
    }

    bool* vis = (bool*)calloc(n, sizeof(bool));
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int vertices = 0;
            int degreeSum = 0;

            dfs(i, graph, degree, vis, &vertices, &degreeSum);

            int edgesInComp = degreeSum / 2;
            int required = vertices * (vertices - 1) / 2;

            if (edgesInComp == required)
                ans++;
        }
    }

    // Free memory
    for (int i = 0; i < n; i++)
        free(graph[i]);

    free(graph);
    free(degree);
    free(idx);
    free(vis);

    return ans;
}