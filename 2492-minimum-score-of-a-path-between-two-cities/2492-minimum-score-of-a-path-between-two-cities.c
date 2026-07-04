#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent an edge in the adjacency list
struct Edge {
    int to;
    int weight;
    struct Edge* next;
};

int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    // 1. Build Adjacency List
    struct Edge** adj = (struct Edge**)calloc(n + 1, sizeof(struct Edge*));
    for (int i = 0; i < roadsSize; i++) {
        int u = roads[i][0];
        int v = roads[i][1];
        int w = roads[i][2];

        // Add edge u -> v
        struct Edge* e1 = (struct Edge*)malloc(sizeof(struct Edge));
        e1->to = v;
        e1->weight = w;
        e1->next = adj[u];
        adj[u] = e1;

        // Add edge v -> u
        struct Edge* e2 = (struct Edge*)malloc(sizeof(struct Edge));
        e2->to = u;
        e2->weight = w;
        e2->next = adj[v];
        adj[v] = e2;
    }

    // 2. BFS Setup
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));
    int* queue = (int*)malloc((n + 1) * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = 1;
    visited[1] = true;
    int min_score = 1e9; // Representing infinity

    // 3. BFS Traversal
    while (front < rear) {
        int curr = queue[front++];
        
        struct Edge* edge = adj[curr];
        while (edge != NULL) {
            if (edge->weight < min_score) {
                min_score = edge->weight;
            }
            if (!visited[edge->to]) {
                visited[edge->to] = true;
                queue[rear++] = edge->to;
            }
            edge = edge->next;
        }
    }

    // 4. Free allocated memory to prevent leaks
    for (int i = 1; i <= n; i++) {
        struct Edge* edge = adj[i];
        while (edge != NULL) {
            struct Edge* tmp = edge;
            edge = edge->next;
            free(tmp);
        }
    }
    free(adj);
    free(visited);
    free(queue);

    return min_score;
}