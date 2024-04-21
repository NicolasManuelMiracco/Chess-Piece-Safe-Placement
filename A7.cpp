#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int BOARD_SIZE = 8;
const int QUEEN = 1;
const int KNIGHT = 2;
const int BISHOP = 3;
const int PAWN = 4;

void printSolution(vector<vector<int>> &board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++)
            cout << (board[i][j] == QUEEN ? "Q " : (board[i][j] == KNIGHT ? "K " : 
                    (board[i][j] == BISHOP ? "B " : (board[i][j] == PAWN ? "P " : ". "))));
        cout << endl;
    }
    cout << endl;
}

bool isSafeFromQueens(vector<vector<int>> &board, int row, int col) {
    // Check same column and same row
    for (int i = 0; i < BOARD_SIZE; i++)
        if (board[i][col] == QUEEN || board[row][i] == QUEEN)
            return false;

    return true;
}

bool isSafeFromBishop(vector<vector<int>> &board, int row, int col) {
    // Check diagonals
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == QUEEN || board[i][j] == BISHOP)
            return false;

    for (int i = row, j = col; i >= 0 && j < BOARD_SIZE; i--, j++)
        if (board[i][j] == QUEEN || board[i][j] == BISHOP)
            return false;

    for (int i = row, j = col; i < BOARD_SIZE && j >= 0; i++, j--)
        if (board[i][j] == QUEEN || board[i][j] == BISHOP)
            return false;

    for (int i = row, j = col; i < BOARD_SIZE && j < BOARD_SIZE; i++, j++)
        if (board[i][j] == QUEEN || board[i][j] == BISHOP)
            return false;

    return true;
}

bool isSafeFromKnight(vector<vector<int>> &board, int row, int col, int newElement) {
    int knightMoves[][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, 
                            {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

    for (int i = 0; i < BOARD_SIZE; i++) {
        int newRow = row + knightMoves[i][0];
        int newCol = col + knightMoves[i][1];
        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE && 
            ((board[newRow][newCol] == KNIGHT && newElement == QUEEN) || (board[newRow][newCol] == QUEEN && newElement == KNIGHT)))
            return false;
    }

    return true;
}

bool isSafeFromPawn(vector<vector<int>> &board, int row, int col, int newElement) {
    // Check for pawn attacks when putting a pawn
    if (newElement == 4) {
        if (((row - 1) > 0 && (col - 1) > 0 && board[row - 1][col - 1] == QUEEN) || ((row - 1) > 0 && (col + 1) < BOARD_SIZE && board[row - 1][col + 1] == QUEEN))
            return false;
    }
    // Check for pawn attacks when putting a queen
    if (newElement == QUEEN) {
        if (((row + 1) < BOARD_SIZE && (col - 1) > 0 && board[row + 1][col - 1] == PAWN) || ((row + 1) < BOARD_SIZE && (col + 1) < BOARD_SIZE && board[row + 1][col + 1] == PAWN))
            return false;
    }

    return true;
}

bool isSafe(vector<vector<int>> &board, int row, int col, int newElement) {
    if (!isSafeFromQueens(board, row, col)) return false;
    if (!isSafeFromBishop(board, row, col)) return false;
    if (!isSafeFromKnight(board, row, col, newElement)) return false;
    if (!isSafeFromPawn(board, row, col, newElement)) return false;

    return true;
}

bool solveUtil(vector<vector<int>> &board, int row, int queenCount) {
    if (queenCount == 5) { 
        // Find spots for knight, bishop and pawn
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 0 && isSafe(board, i, j, KNIGHT)) {
                    board[i][j] = KNIGHT; // Place knight

                    // Try to place the bishop
                    for (int x = 0; x < BOARD_SIZE; x++) {
                        for (int y = 0; y < BOARD_SIZE; y++) {
                            if (board[x][y] == 0 && isSafe(board, x, y, BISHOP)) {
                                board[x][y] = BISHOP; // Place bishop
                                
                                // Try to place the pawn
                                for (int w = 0; w < BOARD_SIZE; w++) {
                                    for (int z = 0; z < BOARD_SIZE; z++) {
                                        if (board[w][z] == 0 && isSafe(board, w, z, PAWN)) {
                                            board[w][z] = PAWN; // Place pawn
                                            return true;
                                        }
                                    }
                                }
                                // If pawn can't be placed, remove bishop
                                board[x][y] = 0; 
                            }
                        }
                    }

                    // If bishop can't be placed, remove knight
                    board[i][j] = 0; 
                }
            }
        }
        return false; 
    }   

    for (int col = 0; col < BOARD_SIZE; col++) {
        if (isSafe(board, row, col, QUEEN)) {
            board[row][col] = QUEEN; // Place queen

            if (solveUtil(board, row + 1, queenCount + 1)) 
                return true;

            board[row][col] = 0; // If queen can't be placed, remove queen
        }
    }

    return false; 
}

bool solve() {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

    if (solveUtil(board, 0, 0) == false) {
        cout << "Solution does not exist" << endl;
        return false;
    }

    printSolution(board);
    return true;
}

int main() {
    solve();
    return 0;
}