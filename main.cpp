#include <iostream>
using namespace std;

const int SIZE = 9;

// Function to print the Sudoku board
void printBoard(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

// Check if number exists in row
bool isRowSafe(int board[SIZE][SIZE], int row, int num) {
    for (int col = 0; col < SIZE; col++) {
        if (board[row][col] == num)
            return false;
    }
    return true;
}

// Check if number exists in column
bool isColSafe(int board[SIZE][SIZE], int col, int num) {
    for (int row = 0; row < SIZE; row++) {
        if (board[row][col] == num)
            return false;
    }
    return true;
}

// Check 3x3 subgrid
bool isBoxSafe(int board[SIZE][SIZE], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row + startRow][col + startCol] == num)
                return false;
        }
    }
    return true;
}

// Check whether placing number is valid
bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    return isRowSafe(board, row, num) &&
           isColSafe(board, col, num) &&
           isBoxSafe(board, row - row % 3, col - col % 3, num);
}

// Solve Sudoku using Backtracking
bool solveSudoku(int board[SIZE][SIZE]) {

    int row, col;
    bool emptyFound = false;

    // Find empty cell
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                emptyFound = true;
                break;
            }
        }
        if (emptyFound)
            break;
    }

    // If no empty cell exists
    if (!emptyFound)
        return true;

    // Try numbers 1-9
    for (int num = 1; num <= 9; num++) {

        if (isSafe(board, row, col, num)) {

            board[row][col] = num;

            if (solveSudoku(board))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

int main() {

    int board[SIZE][SIZE] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    cout << "Sudoku Puzzle Solver\n\n";

    if (solveSudoku(board)) {
        cout << "Solved Sudoku:\n\n";
        printBoard(board);
    }
    else {
        cout << "No solution exists.";
    }

    return 0;
}