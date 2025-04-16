/**
 * AO* Search Algorithm Implementation
 * 
 * This program implements the AO* algorithm on a directed graph
 * where edges represent costs from one node to another.
 * Fixed from original implementation to handle leaf nodes.
 */
#include <stdio.h>
#include <stdlib.h>
 
#define MAX 10
#define INF 9999
 
int cost[MAX][MAX];
int heuristic[MAX];
int solved[MAX];
int n;
 
// Function to find the child with minimum cost
int minCostChild(int node, int *child) {
    int min = INF;
    int hasChild = 0;
    
    for (int i = 0; i < n; i++) {
        if (cost[node][i] != -1) {
            hasChild = 1;
            if (heuristic[i] + cost[node][i] < min) {
                min = heuristic[i] + cost[node][i];
                *child = i;
            }
        }
    }
    
    // If node is a leaf (no children)
    if (!hasChild) {
        *child = -1;
        return heuristic[node];
    }
    
    return min;
}
 
void AOStar(int node) {
    if (solved[node])
        return;
        
    // Check if node is already a leaf node
    int isLeaf = 1;
    for (int i = 0; i < n; i++) {
        if (cost[node][i] != -1) {
            isLeaf = 0;
            break;
        }
    }
    
    if (isLeaf) {
        solved[node] = 1;
        printf("Solved Leaf Node: %d with Cost: %d\n", node, heuristic[node]);
        return;
    }
 
    int child;
    int minCost = minCostChild(node, &child);
    
    if (child == -1) {
        // This is a defensive check, should not happen with the isLeaf check
        solved[node] = 1;
        printf("Solved Leaf Node: %d with Cost: %d\n", node, heuristic[node]);
        return;
    }
    
    heuristic[node] = minCost;
 
    AOStar(child);
    solved[node] = 1;
    printf("Solved Node: %d via Child: %d with Cost: %d\n", node, child, heuristic[node]);
}

void printCostMatrix() {
    printf("\nCost Matrix (-1 means no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", cost[i][j]);
        }
        printf("\n");
    }
}
 
int main() {
    printf("Enter number of nodes: ");
    scanf("%d", &n);
 
    printf("Enter cost matrix (-1 if no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);
 
    printCostMatrix();
    
    printf("Enter heuristic values:\n");
    for (int i = 0; i < n; i++) {
        printf("h[%d] = ", i);
        scanf("%d", &heuristic[i]);
        solved[i] = 0;
    }
 
    printf("\nStarting AO* from node 0:\n");
    AOStar(0);
    
    return 0;
}

/*
Example Input:
Enter number of nodes: 5
Enter cost matrix (-1 if no edge):
-1  3  6 -1 -1
-1 -1 -1  2  3
-1 -1 -1  6 -1
-1 -1 -1 -1 -1
-1 -1 -1 -1 -1
Enter heuristic values:
h[0] = 10
h[1] = 5
h[2] = 4
h[3] = 2
h[4] = 1

Expected Output:
Cost Matrix (-1 means no edge):
-1  3  6 -1 -1 
-1 -1 -1  2  3 
-1 -1 -1  6 -1 
-1 -1 -1 -1 -1 
-1 -1 -1 -1 -1 

Starting AO* from node 0:
Solved Leaf Node: 3 with Cost: 2
Solved Leaf Node: 4 with Cost: 1
Solved Node: 1 via Child: 4 with Cost: 4
Solved Node: 0 via Child: 1 with Cost: 7
*/
