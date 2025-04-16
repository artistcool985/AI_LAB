/**
 * A* Search Algorithm Implementation
 * 
 * This program implements the A* algorithm on a graph represented 
 * as an adjacency matrix, with heuristic values for each node.
 */
#include <stdio.h>
#include <stdlib.h>
 
#define MAX 100
#define INF 9999
 
int n;
int adj[MAX][MAX];
int h[MAX];  // Heuristic values
 
int visited[MAX];
 
int findMinF(int open[], int f[]) {
    int min = INF, index = -1;
    for (int i = 0; i < n; i++) {
        if (open[i] && f[i] < min) {
            min = f[i];
            index = i;
        }
    }
    return index;
}
 
void AStar(int start, int goal) {
    int open[MAX] = {0}, closed[MAX] = {0};
    int g[MAX], f[MAX], parent[MAX];
 
    for (int i = 0; i < n; i++) {
        g[i] = INF;
        f[i] = INF;
        parent[i] = -1;
    }
 
    g[start] = 0;
    f[start] = h[start];
    open[start] = 1;
 
    while (1) {
        int current = findMinF(open, f);
        if (current == -1) {
            printf("No path found.\n");
            return;
        }
 
        if (current == goal) {
            printf("A* Path: ");
            int path[MAX], idx = 0;
            while (current != -1) {
                path[idx++] = current;
                current = parent[current];
            }
            for (int i = idx - 1; i >= 0; i--)
                printf("%d ", path[i]);
            printf("\n");
            return;
        }
 
        open[current] = 0;
        closed[current] = 1;
 
        for (int i = 0; i < n; i++) {
            if (adj[current][i] && !closed[i]) {
                int temp_g = g[current] + adj[current][i];
                if (temp_g < g[i]) {
                    parent[i] = current;
                    g[i] = temp_g;
                    f[i] = g[i] + h[i];
                    open[i] = 1;
                }
            }
        }
    }
}

void printAdjacencyMatrix() {
    printf("\nAdjacency Matrix (with costs):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] == 0)
                printf("0 ");
            else
                printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}
 
int main() {
    int edges, u, v, cost, start, goal;
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &n, &edges);
 
    // Initialize adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
 
    printf("Enter edges with cost (u v cost):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &cost);
        adj[u][v] = cost;
        adj[v][u] = cost; // For undirected graph
    }
 
    printAdjacencyMatrix();
 
    printf("Enter heuristic values:\n");
    for (int i = 0; i < n; i++) {
        printf("h[%d] = ", i);
        scanf("%d", &h[i]);
    }
 
    printf("Enter start and goal nodes: ");
    scanf("%d %d", &start, &goal);
 
    AStar(start, goal);
 
    return 0;
}

/*
Example Input:
Enter number of nodes and edges: 5 7
Enter edges with cost (u v cost):
0 1 2
0 2 5
1 2 1
1 3 4
2 3 2
2 4 5
3 4 1
Enter heuristic values:
h[0] = 7
h[1] = 5
h[2] = 3
h[3] = 1
h[4] = 0
Enter start and goal nodes: 0 4

Expected Output:
Adjacency Matrix (with costs):
0 2 5 0 0 
2 0 1 4 0 
5 1 0 2 5 
0 4 2 0 1 
0 0 5 1 0 

A* Path: 0 1 2 3 4
*/
