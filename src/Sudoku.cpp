#include "Sudoku.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Sudoku::Sudoku() {
    srand(time(0));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = solution[i][j] = 0;
}

void Sudoku::printBoard() {
    cout << "\n    ";
    for (int col = 1; col <= 9; col++) {
        cout << col << " ";
        if (col % 3 == 0 && col != 9) cout << " ";
    }
    cout << "\n";

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0)
            cout << "   ------+-------+------\n";

        cout << i + 1 << " | ";
        for (int j = 0; j < 9; j++) {
            cout << (board[i][j] == 0 ? '.' : '0' + board[i][j]) << " ";
            if ((j + 1) % 3 == 0 && j != 8)
                cout << "| ";
        }
        cout << "\n";
    }
}

bool Sudoku::findEmpty(int &row, int &col) {
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (solution[row][col] == 0)
                return true;
    return false;
}

bool Sudoku::isSafe(int row, int col, int num) {
    for (int x = 0; x < 9; x++)
        if (solution[row][x] == num || solution[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (solution[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool Sudoku::solveBoard() {
    int row, col;
    if (!findEmpty(row, col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            solution[row][col] = num;
            if (solveBoard()) return true;
            solution[row][col] = 0;
        }
    }
    return false;
}

bool Sudoku::solve() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            solution[i][j] = board[i][j];

    if (solveBoard()) {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                board[i][j] = solution[i][j];
        return true;
    }
    return false;
}

void Sudoku::fillBox(int row, int col) {
    int num;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            do {
                num = rand() % 9 + 1;
            } while (!isSafe(row + i, col + j, num));
            solution[row + i][col + j] = num;
        }
}

void Sudoku::fillDiagonalBoxes() {
    for (int i = 0; i < 9; i += 3)
        fillBox(i, i);
}

void Sudoku::removeDigits(int count) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = solution[i][j];

    while (count) {
        int i = rand() % 9;
        int j = rand() % 9;
        if (board[i][j] != 0) {
            board[i][j] = 0;
            count--;
        }
    }
}

void Sudoku::generatePuzzle() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = solution[i][j] = 0;

    fillDiagonalBoxes();
    solveBoard();
    removeDigits(40);
}

bool Sudoku::isComplete() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j] == 0 || board[i][j] != solution[i][j])
                return false;
    return true;
}

void Sudoku::playGame() {
    int row, col, num;

    cout << "\nSudoku Puzzle:\n";
    printBoard();

    while (true) {
        cout << "\nEnter row (1-9) or 0 to view solution and quit: ";
        if (!(cin >> row) || row < 0 || row > 9) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid row.\n"; continue;
        }
        if (row == 0) break;

        cout << "Enter column (1-9): ";
        if (!(cin >> col) || col < 1 || col > 9) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid column.\n"; continue;
        }

        cout << "Enter number to place (1-9): ";
        if (!(cin >> num) || num < 1 || num > 9) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid number.\n"; continue;
        }

        row--; col--;
        if (board[row][col] != 0) {
            cout << "This cell is pre-filled.\n"; continue;
        }

        if (solution[row][col] == num) {
            board[row][col] = num;
            cout << "Correct move.\n";
            printBoard();

            if (isComplete()) {
                cout << "🎉 Congratulations! You completed the puzzle!\n";
                break;
            }

        } else {
            cout << "Incorrect move.\n";
        }
    }

    cout << "\nFinal Board:\n";
    printBoard();
}
