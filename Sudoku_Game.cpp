#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;

const int SIZE = 9;

// ===================== COLORS =====================
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

// ===================== SUDOKU CLASS =====================
class Sudoku {
private:
    vector<vector<int>> board;
    vector<vector<int>> solution;
    vector<vector<bool>> given;
    int mistakes;
    int hintsUsed;

public:
    // Constructor
    Sudoku() : mistakes(0), hintsUsed(0) {
        board.assign(SIZE, vector<int>(SIZE, 0));
        solution.assign(SIZE, vector<int>(SIZE, 0));
        given.assign(SIZE, vector<bool>(SIZE, false));
    }

    // ===== isSafe: checks if number is safe to place =====
    bool isSafe(const vector<vector<int>>& b, int row, int col, int num) {
        for (int x = 0; x < SIZE; x++) {
            if (b[row][x] == num) return false;       // Row check
            if (b[x][col] == num) return false;       // Column check
            int br = 3 * (row / 3) + x / 3;
            int bc = 3 * (col / 3) + x % 3;
            if (b[br][bc] == num) return false;       // 3x3 box check
        }
        return true;
    }

    // ===== Backtracking Solver =====
    bool solveSudoku(vector<vector<int>>& b) {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (b[row][col] == 0) {
                    for (int num = 1; num <= SIZE; num++) {
                        if (isSafe(b, row, col, num)) {
                            b[row][col] = num;
                            if (solveSudoku(b)) return true;
                            b[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    // ===== Load Puzzle =====
    void loadPuzzle(int difficulty) {
        mistakes  = 0;
        hintsUsed = 0;

        vector<vector<int>> easy = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };

        vector<vector<int>> medium = {
            {0, 0, 0, 2, 6, 0, 7, 0, 1},
            {6, 8, 0, 0, 7, 0, 0, 9, 0},
            {1, 9, 0, 0, 0, 4, 5, 0, 0},
            {8, 2, 0, 1, 0, 0, 0, 4, 0},
            {0, 0, 4, 6, 0, 2, 9, 0, 0},
            {0, 5, 0, 0, 0, 3, 0, 2, 8},
            {0, 0, 9, 3, 0, 0, 0, 7, 4},
            {0, 4, 0, 0, 5, 0, 0, 3, 6},
            {7, 0, 3, 0, 1, 8, 0, 0, 0}
        };

        vector<vector<int>> hard = {
            {0, 0, 0, 0, 0, 0, 0, 1, 2},
            {0, 0, 0, 0, 3, 5, 0, 0, 0},
            {0, 0, 0, 6, 0, 0, 0, 7, 0},
            {7, 0, 0, 0, 0, 0, 3, 0, 0},
            {0, 0, 0, 4, 0, 0, 8, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 2, 0, 0, 0, 0},
            {0, 8, 0, 0, 0, 0, 0, 4, 0},
            {0, 5, 0, 0, 0, 0, 6, 0, 0}
        };

        if      (difficulty == 1) board = easy;
        else if (difficulty == 2) board = medium;
        else                      board = hard;

        // Generate solution
        solution = board;
        solveSudoku(solution);

        // Mark pre-filled cells as given
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                given[r][c] = (board[r][c] != 0);
    }

    // ===== Print Board =====
    void printBoard() {
        cout << "\n";
        cout << BOLD << CYAN;
        cout << "    1 2 3   4 5 6   7 8 9\n";
        cout << "   +---------+---------+---------+\n";
        cout << RESET;

        for (int r = 0; r < SIZE; r++) {
            cout << BOLD << CYAN << " " << r + 1 << " |" << RESET;
            for (int c = 0; c < SIZE; c++) {
                if (c == 3 || c == 6) cout << CYAN << " |" << RESET;
                if (board[r][c] == 0) {
                    cout << " .";
                } else if (given[r][c]) {
                    cout << BLUE << BOLD << " " << board[r][c] << RESET;
                } else {
                    cout << GREEN << " " << board[r][c] << RESET;
                }
            }
            cout << CYAN << " |" << RESET << "\n";
            if (r == 2 || r == 5)
                cout << BOLD << CYAN << "   +---------+---------+---------+\n" << RESET;
        }
        cout << BOLD << CYAN << "   +---------+---------+---------+\n" << RESET;
        cout << "\n";
        cout << YELLOW << "  [Blue = Given]  [Green = Your Input]  [. = Empty]\n" << RESET;
        cout << "  Mistakes: " << RED << mistakes << "/3" << RESET;
        cout << "   Hints Used: " << YELLOW << hintsUsed << RESET << "\n\n";
    }

    // ===== Enter Number =====
    bool enterNumber(int row, int col, int num) {
        row--; col--;  // Convert to 0-indexed

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cout << RED << "  Error: Row and Column must be between 1 and 9.\n" << RESET;
            return false;
        }
        if (given[row][col]) {
            cout << RED << "  Error: This cell is pre-filled and cannot be changed.\n" << RESET;
            return false;
        }
        if (num < 1 || num > 9) {
            cout << RED << "  Error: Number must be between 1 and 9.\n" << RESET;
            return false;
        }
        if (board[row][col] != 0) {
            cout << RED << "  Error: Cell already filled. Erase it first.\n" << RESET;
            return false;
        }

        if (solution[row][col] != num) {
            mistakes++;
            // Wrong number is NOT placed on board — only mistake is counted
            cout << RED << "  Wrong number! Mistakes: " << mistakes << "/3\n" << RESET;
            if (mistakes >= 3)
                cout << RED << BOLD << "  You have made 3 mistakes! Game Over.\n" << RESET;
            return false;
        }

        board[row][col] = num;
        cout << GREEN << "  Correct!\n" << RESET;
        return true;
    }

    // ===== Erase Cell =====
    bool eraseCell(int row, int col) {
        row--; col--;
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cout << RED << "  Error: Row and Column must be between 1 and 9.\n" << RESET;
            return false;
        }
        if (given[row][col]) {
            cout << RED << "  Error: Cannot erase a pre-filled cell.\n" << RESET;
            return false;
        }
        if (board[row][col] == 0) {
            cout << YELLOW << "  Cell is already empty.\n" << RESET;
            return false;
        }
        board[row][col] = 0;
        cout << YELLOW << "  Cell erased successfully.\n" << RESET;
        return true;
    }

    // ===== Give Hint =====
    void giveHint() {
        vector<pair<int,int>> emptyCells;
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                if (!given[r][c] && board[r][c] == 0)
                    emptyCells.push_back({r, c});

        if (emptyCells.empty()) {
            cout << YELLOW << "  No empty cells remaining!\n" << RESET;
            return;
        }

        int idx = rand() % emptyCells.size();
        int r = emptyCells[idx].first;
        int c = emptyCells[idx].second;
        board[r][c] = solution[r][c];
        given[r][c]  = true;
        hintsUsed++;
        cout << GREEN << "  Hint: Row " << r+1 << ", Col " << c+1
             << " has been filled with " << solution[r][c] << "\n" << RESET;
    }

    // ===== Auto Solve =====
    void autoSolve() {
        // Fill only user-empty cells, mark them as given so they show in blue
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++) {
                board[r][c]  = solution[r][c];
                given[r][c]  = true;
            }
        cout << GREEN << BOLD << "  Puzzle has been solved automatically!\n" << RESET;
    }

    // ===== Check Board =====
    void checkBoard() {
        int wrong     = 0;
        bool incomplete = false;
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++) {
                if (board[r][c] == 0)
                    incomplete = true;
                else if (board[r][c] != solution[r][c])
                    wrong++;
            }

        if (wrong > 0)
            cout << RED << "  " << wrong << " incorrect cell(s) found!\n" << RESET;
        else if (incomplete)
            cout << YELLOW << "  Everything correct so far! Keep going.\n" << RESET;
        else
            cout << GREEN << BOLD << "  Perfect! All cells are correct!\n" << RESET;
    }

    // ===== Win Check =====
    bool isWon() {
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                if (board[r][c] == 0 || board[r][c] != solution[r][c])
                    return false;
        return true;
    }

    bool isGameOver() { return mistakes >= 3; }
};

// ===================== SAFE INPUT =====================
int safeInt(const string& prompt, int mn, int mx) {
    int val;
    while (true) {
        cout << prompt << flush;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (val >= mn && val <= mx) return val;
            cout << RED << "  Invalid input! Enter a number between " << mn << " and " << mx << ".\n" << RESET;
        } else {
            if (cin.eof()) {
                // End of input stream — exit gracefully
                cout << CYAN << "\n  Input ended. Goodbye.\n" << RESET;
                exit(0);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "  Invalid input! Enter a number between " << mn << " and " << mx << ".\n" << RESET;
        }
    }
}

// ===================== SHOW MENU =====================
void showMenu() {
    cout << BOLD << CYAN;
    cout << "\n  ================================\n";
    cout << "           SUDOKU GAME\n";
    cout << "  ================================\n" << RESET;
    cout << "  1. Enter a number\n";
    cout << "  2. Erase a cell\n";
    cout << "  3. Get a hint\n";
    cout << "  4. Check the board\n";
    cout << "  5. Auto solve\n";
    cout << "  6. New game\n";
    cout << "  0. Exit\n";
    cout << BOLD << CYAN << "  ================================\n" << RESET;
}

// ===================== MAIN =====================
int main() {
    srand(static_cast<unsigned int>(time(0)));
    Sudoku game;
    bool running = true;

    cout << BOLD << CYAN << "\n  ==============================\n";
    cout << "      SUDOKU GAME - C++ OOP\n";
    cout << "  ==============================\n" << RESET;

    cout << "\n  Select Difficulty:\n";
    cout << "  1. Easy\n";
    cout << "  2. Medium\n";
    cout << "  3. Hard\n";
    int diff = safeInt("  Your choice: ", 1, 3);
    game.loadPuzzle(diff);

    while (running) {
        game.printBoard();
        showMenu();

        int choice = safeInt("  Choice: ", 0, 6);

        switch (choice) {
            case 1: {
                int r = safeInt("  Row    (1-9): ", 1, 9);
                int c = safeInt("  Column (1-9): ", 1, 9);
                int n = safeInt("  Number (1-9): ", 1, 9);
                game.enterNumber(r, c, n);
                if (game.isWon()) {
                    game.printBoard();
                    cout << GREEN << BOLD;
                    cout << "\n  *** Congratulations! You solved the puzzle! ***\n" << RESET;
                    running = false;
                } else if (game.isGameOver()) {
                    game.printBoard();
                    cout << RED << BOLD;
                    cout << "\n  *** Game Over! You made 3 mistakes! ***\n" << RESET;
                    running = false;
                }
                break;
            }
            case 2: {
                int r = safeInt("  Row    (1-9): ", 1, 9);
                int c = safeInt("  Column (1-9): ", 1, 9);
                game.eraseCell(r, c);
                break;
            }
            case 3:
                game.giveHint();
                break;
            case 4:
                game.checkBoard();
                break;
            case 5:
                game.autoSolve();
                break;
            case 6: {
                cout << "\n  Select Difficulty:\n";
                cout << "  1. Easy\n  2. Medium\n  3. Hard\n";
                int d = safeInt("  Your choice: ", 1, 3);
                game.loadPuzzle(d);
                break;
            }
            case 0:
                cout << CYAN << "\n  Thank you for playing! Goodbye.\n" << RESET;
                running = false;
                break;
        }
    }

    return 0;
}