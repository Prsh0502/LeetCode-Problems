#include <stdlib.h>
#include <stdbool.h>

// Helper DFS function to traverse the component and collect its nodes
void dfs(int u, int n, int adj[50][50], bool* visited, int* componentNodes, int* componentSize) {
    visited[u] = true;
    componentNodes[(*componentSize)++] = u;
    
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v, n, adj, visited, componentNodes, componentSize);
        }
    }
}

int countCompleteComponents(int n, int** edges, int edgesSize, int* edgesColSize) {
    int adj[50][50] = {0};
    int deg[50] = {0};
    
    // 1. Build the adjacency matrix and record degrees
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][v] = 1;
        adj[v][u] = 1;
        deg[u]++;
        deg[v]++;
    }
    
    bool visited[50] = {false};
    int completeComponentCount = 0;
    
    // 2. Iterate through all nodes to find connected components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int componentNodes[50];
            int componentSize = 0;
            
            // Collect all vertices belonging to this component
            dfs(i, n, adj, visited, componentNodes, &componentSize);
            
            // 3. Verify if the component is complete
            bool isComplete = true;
            for (int j = 0; j < componentSize; j++) {
                int node = componentNodes[j];
                if (deg[node] != componentSize - 1) {
                    isComplete = false;
                    break;
                }
            }
            
            if (isComplete) {
                completeComponentCount++;
            }
        }
    }
    
    return completeComponentCount;
}