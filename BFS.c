/**
 * Breadth-First Search implementation
 * 
 * This program implements the BFS algorithm on a graph represented 
 * as an adjacency matrix.
 */
#include <stdio.h>
 
#define MAX 100
 
int visited[MAX];
int adj[MAX][MAX];
int n;
 
// BFS function
void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    
    visited[start] = 1;
    queue[rear++] = start;
 
    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
 
        for (int i = 0; i < n; i++) {
            if (adj[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}
 
// Function to print adjacency matrix
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
    int edges, src, u, v;
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &n, &edges);
 
    // Initialize adjacency matrix to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
        visited[i] = 0;
    }
 
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;  // Undirected graph
    }
 
    printAdjacencyMatrix();
 
    printf("Enter source node for BFS: ");
    scanf("%d", &src);
 
    printf("BFS Traversal: ");
    BFS(src);
    
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
Enter source node for BFS: 0

Expected Output:
Adjacency Matrix:
0 1 1 0 0 
1 0 1 1 0 
1 1 0 0 1 
0 1 0 0 1 
0 0 1 1 0 

BFS Traversal: 0 1 2 3 4
*/
