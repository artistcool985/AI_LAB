/**
 * N-Queens Problem Implementation
 * 
 * This program solves the N-Queens problem using backtracking.
 * The 'board' array stores the column position of the queen in each row.
 */
#include <stdio.h>
#include <stdlib.h>
 
int *board;
int N; 
int solutionCount = 0;
 
// Function to check if a queen can be placed at board[row][col]
int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check if same column or diagonal attack is possible
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0;
    }
    return 1;
}
 
// Function to print the chessboard
void printSolution() {
    printf("Solution %d:\n", solutionCount + 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i] == j ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}
 
// Recursive function to solve N-Queens using backtracking
void solve(int row) {
    if (row == N) {
        printSolution();
        solutionCount++;
        return;
    }
 
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;   // Place queen in this column
            solve(row + 1);     // Recur for next row
        }
    }
}
 
int main() {
    printf("Enter the value of N (size of chessboard): ");
    scanf("%d", &N);
    
    // Check if N is valid
    if (N <= 0) {
        printf("Invalid board size.\n");
        return 1;
    }
    
    // Allocate memory for the board
    board = (int *)malloc(N * sizeof(int));
    if (board == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    // Initialize board with -1 (no queen placed)
    for (int i = 0; i < N; i++) {
        board[i] = -1;
    }
 
    solve(0);  // Start from the first row
 
    printf("Total number of solutions: %d\n", solutionCount);
 
    free(board);  // Free allocated memory
    return 0;
}

/*
Example Input:
Enter the value of N (size of chessboard): 4

Expected Output:
Solution 1:
. Q . . 
. . . Q 
Q . . . 
. . Q . 

Solution 2:
. . Q . 
Q . . . 
. . . Q 
. Q . . 

Total number of solutions: 2
*/
