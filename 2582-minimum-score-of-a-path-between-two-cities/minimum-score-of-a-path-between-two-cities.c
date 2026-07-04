#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int city;
    int dist;
    struct Node *next;
} Node;

void dfs(int u, Node **graph, int *visited, int *ans) {
    visited[u] = 1;

    Node *temp = graph[u];
    while (temp) {
        if (temp->dist < *ans)
            *ans = temp->dist;

        if (!visited[temp->city])
            dfs(temp->city, graph, visited, ans);

        temp = temp->next;
    }
}

int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    Node **graph = (Node **)calloc(n + 1, sizeof(Node*));

    // Build graph
    for (int i = 0; i < roadsSize; i++) {
        int a = roads[i][0];
        int b = roads[i][1];
        int d = roads[i][2];

        Node *node1 = (Node *)malloc(sizeof(Node));
        node1->city = b;
        node1->dist = d;
        node1->next = graph[a];
        graph[a] = node1;

        Node *node2 = (Node *)malloc(sizeof(Node));
        node2->city = a;
        node2->dist = d;
        node2->next = graph[b];
        graph[b] = node2;
    }

    int *visited = (int *)calloc(n + 1, sizeof(int));
    int ans = INT_MAX;

    dfs(1, graph, visited, &ans);

    // Free memory
    for (int i = 1; i <= n; i++) {
        Node *curr = graph[i];
        while (curr) {
            Node *next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph);
    free(visited);

    return ans;
}