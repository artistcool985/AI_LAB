/**
 * Depth-Limited Search implementation
 * 
 * This program implements the DLS algorithm on a graph represented 
 * as an adjacency matrix.
 */
#include <stdio.h>
 
#define MAX 100
 
int adj[MAX][MAX];
int n;
 
int DLS(int src, int target, int limit) {
    if (src == target) {
        printf("%d ", src);
        return 1;
    }
    if (limit <= 0)
        return 0;
 
    printf("%d ", src);
 
    for (int i = 0; i < n; i++) {
        if (adj[src][i]) {
            if (DLS(i, target, limit - 1))
                return 1;
        }
    }
    return 0;
}
 
void printAdjacencyMatrix() {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int edges, u, v, src, target, limit;
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &n, &edges);
 
    // Initialize adjacency matrix to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
 
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;  // Undirected graph
    }
 
    printAdjacencyMatrix();
 
    printf("Enter source, target and depth limit: ");
    scanf("%d %d %d", &src, &target, &limit);
 
    printf("DLS Path: ");
    if (!DLS(src, target, limit))
        printf("\nTarget not reachable within depth limit\n");
 
    return 0;
}

/*
Example Input:
Enter number of nodes and edges: 5 6
Enter edges (u v):
0 1
0 2
1 2
1 3
2 4
3 4
Enter source, target and depth limit: 0 4 2

Expected Output:
Adjacency Matrix:
0 1 1 0 0 
1 0 1 1 0 
1 1 0 0 1 
0 1 0 0 1 
0 0 1 1 0 

DLS Path: 0 1 3 4
*/
