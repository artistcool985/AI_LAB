/**
 * Tic-Tac-Toe Game (Two Player, Non-AI)
 * 
 * This program implements a simple 2-player Tic-Tac-Toe game
 * where humans play against each other.
 */
#include <stdio.h>
 
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
    
    return ' ';  // No winner yet
}
 
// Function to check if the board is full
int isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}
 
// Function to handle player move
void playerMove(char player) {
    int row, col;
    printf("Player %c, enter row and column (0-2): ", player);
    scanf("%d %d", &row, &col);
    
    // Check if the move is valid
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = player;
    } else {
        printf("Invalid move, try again!\n");
        playerMove(player);
    }
}
 
// Function to initialize the board
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}
 
int main() {
    initializeBoard();
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Player 1: X, Player 2: O\n");
    printBoard();
 
    char winner = ' ';
    for (int turn = 0; turn < 9; turn++) {
        if (turn % 2 == 0) {
            playerMove('X');
        } else {
            playerMove('O');
        }
        printBoard();
 
        winner = checkWinner();
        if (winner != ' ') {
            printf("Player %c wins!\n", winner);
            break;
        }
        if (isFull()) {
            printf("It's a draw!\n");
            break;
        }
    }
 
    return 0;
}
