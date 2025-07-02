#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku {
    int board[9][9];
    int solution[9][9];

public:
    Sudoku();
    void generatePuzzle();
    bool solve();
    void printBoard();
    void playGame();

private:
    bool isSafe(int row, int col, int num);
    bool findEmpty(int &row, int &col);
    void fillDiagonalBoxes();
    void fillBox(int row, int col);
    void removeDigits(int count);
    bool solveBoard();
    bool isComplete();
};

#endif
