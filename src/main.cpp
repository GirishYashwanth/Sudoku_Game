#include "Sudoku.h"
#include <iostream>
using namespace std;

int main() {
    Sudoku game;
    int choice;

    while (true) {
        cout << "\nSudoku Game Menu:\n";
        cout << "1. Play Game\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid input.\n"; continue;
        }

        if (choice == 1) {
            game.generatePuzzle();
            game.playGame();
            cout << "\nSolution:\n";
            game.solve();
            game.printBoard();
        } else if (choice == 2) {
            cout << "Exiting game.\n"; break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
