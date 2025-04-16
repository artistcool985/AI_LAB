/**
 * Cryptarithmetic Problem Solver
 * 
 * This program solves cryptarithmetic problems (letter-to-digit assignments)
 * using backtracking. For example, in the puzzle "SEND + MORE = MONEY",
 * each letter represents a digit, and the goal is to find the digit assignment
 * that makes the equation true.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 10  // Max 10 unique letters (0-9 digits)

char word1[20], word2[20], result[20];
char uniqueLetters[MAX];
int numLetters = 0;
int usedDigits[10], charDigit[26]; // 'A' to 'Z'

// Helper to get the numeric value of a word
int getValue(char *word) {
    int val = 0;
    for (int i = 0; word[i]; i++) {
        val = val * 10 + charDigit[word[i] - 'A'];
    }
    return val;
}

// Check if assignment is valid
bool isValid() {
    // No leading zeros
    if (charDigit[word1[0] - 'A'] == 0 || charDigit[word2[0] - 'A'] == 0 || charDigit[result[0] - 'A'] == 0)
        return false;

    int val1 = getValue(word1);
    int val2 = getValue(word2);
    int val3 = getValue(result);
    return (val1 + val2 == val3);
}

// Backtracking function
bool solve(int index) {
    if (index == numLetters) {
        if (isValid()) {
            printf("\nSolution Found:\n");
            for (int i = 0; i < numLetters; i++) {
                printf("%c = %d\n", uniqueLetters[i], charDigit[uniqueLetters[i] - 'A']);
            }
            int val1 = getValue(word1);
            int val2 = getValue(word2);
            int val3 = getValue(result);
            printf("\n%d + %d = %d\n", val1, val2, val3);
            return true;
        }
        return false;
    }

    for (int d = 0; d <= 9; d++) {
        if (!usedDigits[d]) {
            usedDigits[d] = 1;
            charDigit[uniqueLetters[index] - 'A'] = d;

            if (solve(index + 1))
                return true;

            // Backtrack
            usedDigits[d] = 0;
        }
    }
    return false;
}

// Get unique characters
void extractUniqueLetters() {
    int seen[26] = {0};
    char allWords[60];
    sprintf(allWords, "%s%s%s", word1, word2, result);
    for (int i = 0; allWords[i]; i++) {
        char ch = allWords[i];
        if (!seen[ch - 'A']) {
            seen[ch - 'A'] = 1;
            uniqueLetters[numLetters++] = ch;
        }
    }
}

int main() {
    // Initialize arrays
    for (int i = 0; i < 10; i++) {
        usedDigits[i] = 0;
    }
    
    for (int i = 0; i < 26; i++) {
        charDigit[i] = -1;
    }
    
    printf("Enter first word (UPPERCASE): ");
    scanf("%s", word1);
    printf("Enter second word (UPPERCASE): ");
    scanf("%s", word2);
    printf("Enter result word (UPPERCASE): ");
    scanf("%s", result);

    extractUniqueLetters();

    if (numLetters > 10) {
        printf("Too many unique letters (>10), can't assign unique digits.\n");
        return 0;
    }
    
    printf("Trying to solve: %s + %s = %s\n", word1, word2, result);
    printf("Number of unique letters: %d\n", numLetters);

    if (!solve(0))
        printf("\nNo solution found.\n");

    return 0;
}

/*
Example Input:
Enter first word (UPPERCASE): SEND
Enter second word (UPPERCASE): MORE
Enter result word (UPPERCASE): MONEY

Expected Output:
Trying to solve: SEND + MORE = MONEY
Number of unique letters: 8

Solution Found:
S = 9
E = 5
N = 6
D = 7
M = 1
O = 0
R = 8
Y = 2

9567 + 1085 = 10652
*/
