/**
 * Graph Coloring Problem Implementation
 * 
 * This program solves the graph coloring problem using backtracking.
 * It attempts to color a graph with m colors such that no adjacent
 * vertices have the same color.
 */
#include <stdio.h>
#include <stdbool.h>
 
#define MAX 100
 
int color[MAX];  // Stores the color assigned to each vertex
 
// Function to check if assigning color c to vertex v is valid
bool isSafe(int graph[MAX][MAX], int v, int c, int V) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] == 1 && color[i] == c)
            return false;
    }
    return true;
}
 
// Recursive function to solve graph coloring using backtracking
bool graphColoringUtil(int graph[MAX][MAX], int m, int v, int V) {
    // If all vertices are colored
    if (v == V)
        return true;
 
    // Try different colors for vertex v
    for (int c = 1; c <= m; c++) {
        // Check if assignment of color c to v is valid
        if (isSafe(graph, v, c, V)) {
            color[v] = c;
            
            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, m, v + 1, V))
                return true;
            
            // If assigning color c doesn't lead to a solution, backtrack
            color[v] = 0;
        }
    }
    
    // If no color can be assigned, return false
    return false;
}
 
// Function to print the solution
void printSolution(int m, int V) {
    printf("Coloring of graph with %d colors:\n", m);
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i, color[i]);
}

void printAdjacencyMatrix(int graph[MAX][MAX], int V) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}
 
int main() {
    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
 
    int graph[MAX][MAX];
 
    printf("Enter adjacency matrix (0 or 1) for the graph:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printAdjacencyMatrix(graph, V);
 
    int m;
    printf("Enter number of colors: ");
    scanf("%d", &m);
 
    // Initialize color array to 0 (no color assigned)
    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }
 
    if (!graphColoringUtil(graph, m, 0, V))
        printf("Solution does not exist with %d colors.\n", m);
    else
        printSolution(m, V);
 
    return 0;
}

/*
Example Input:
Enter number of vertices: 4
Enter adjacency matrix (0 or 1) for the graph:
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
Enter number of colors: 3

Expected Output:
Adjacency Matrix:
0 1 1 1 
1 0 1 0 
1 1 0 1 
1 0 1 0 

Coloring of graph with 3 colors:
Vertex 0 ---> Color 1
Vertex 1 ---> Color 2
Vertex 2 ---> Color 3
Vertex 3 ---> Color 2
*/
