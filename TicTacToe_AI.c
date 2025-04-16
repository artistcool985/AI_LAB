/**
 * Tic-Tac-Toe Game with AI (using Minimax algorithm)
 * 
 * This program implements a Tic-Tac-Toe game where a human player
 * plays against an AI that uses the Minimax algorithm.
 * Fixed from original implementation to correctly propagate values.
 */
#include <stdio.h>
#include <limits.h>
 
char board[3][3];
 
// Function to print the current state of the board
void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}
 
// Function to check if a player has won
char checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
    }
    
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    
    // Check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
 
    return ' ';
}
 
// Function to check if the board is full
int isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}
 
// Function to evaluate the board
int evaluate() {
    char winner = checkWinner();
    if (winner == 'O') return +10;
    if (winner == 'X') return -10;
    return 0;
}
 
// Minimax function
int minimax(int depth, int isMaximizing) {
    int score = evaluate();
    
    // If Maximizer or Minimizer has won, return score
    if (score == 10 || score == -10)
        return score;
        
    // If there are no more moves and no winner, it's a tie
    if (isFull())
        return 0;
        
    // If this is the maximizer's move
    if (isMaximizing) {
        int best = INT_MIN;
        
        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = 'O';
                    
                    // Call minimax recursively and choose max value
                    int val = minimax(depth + 1, 0);
                    best = (best > val) ? best : val;
                    
                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    // If this is the minimizer's move
    else {
        int best = INT_MAX;
        
        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = 'X';
                    
                    // Call minimax recursively and choose min value
                    int val = minimax(depth + 1, 1);
                    best = (best < val) ? best : val;
                    
                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}
 
// Function for AI move using Minimax
void aiMove() {
    int bestVal = INT_MIN;
    int row = -1, col = -1;
 
    // Traverse all cells, evaluate minimax function for all empty cells
    // And find the cell with optimal value
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty
            if (board[i][j] == ' ') {
                // Make the move
                board[i][j] = 'O';
                
                // Compute evaluation function for this move
                int moveVal = minimax(0, 0);
                
                // Undo the move
                board[i][j] = ' ';
                
                // If the value of the current move is better than the best value
                // then update best
                if (moveVal > bestVal) {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    
    printf("AI chooses position: %d %d\n", row, col);
    board[row][col] = 'O';
}
 
// Function for player move
void playerMove() {
    int row, col;
    printf("Enter row and column (0-2): ");
    scanf("%d %d", &row, &col);
    
    // Check if the move is valid
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = 'X';
    } else {
        printf("Invalid move, try again!\n");
        playerMove();
    }
}
 
// Function to initialize the board
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}
 
// Main function
int main() {
    initializeBoard();
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("You are X, AI is O\n");
    printBoard();
 
    while (1) {
        playerMove();
        printBoard();
        
        char winner = checkWinner();
        if (winner == 'X') {
            printf("You win!\n");
            break;
        }
        
        if (isFull()) {
            printf("It's a draw!\n");
            break;
        }
 
        printf("AI's turn...\n");
        aiMove();
        printBoard();
        
        winner = checkWinner();
        if (winner == 'O') {
            printf("AI wins!\n");
            break;
        }
        
        if (isFull()) {
            printf("It's a draw!\n");
            break;
        }
    }
 
    return 0;
}

/*
Example Input:
Enter row and column (0-2): 0 0
Enter row and column (0-2): 1 1
Enter row and column (0-2): 0 2

Expected Output (partial):
Welcome to Tic-Tac-Toe!
You are X, AI is O

   |   |   
---|---|---
   |   |   
---|---|---
   |   |   

[After first player move]
 X |   |   
---|---|---
   |   |   
---|---|---
   |   |   

AI's turn...
AI chooses position: 0 1

 X | O |   
---|---|---
   |   |   
---|---|---
   |   |   

...
[Game continues until someone wins or it's a draw]
*/
