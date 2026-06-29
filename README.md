# 🎮 Sudoku Game — C++ OOP

A fully interactive **console-based Sudoku Game** built in **C++** using **Object-Oriented Programming (OOP)** concepts. Developed as part of the **C++ Internship at CodeAlpha**.

---

## 📌 About

This project is a complete Sudoku Game implemented in C++ where the player can solve puzzles of varying difficulty levels directly in the terminal. The game features a backtracking algorithm to validate and auto-solve puzzles, user input handling, hints, mistake tracking, and a clean board display.

The project was built to demonstrate core C++ OOP concepts including classes, encapsulation, constructors, and member functions — all applied to a real-world game scenario.

---

## 🚀 Features

- ✅ **3 Difficulty Levels** — Easy, Medium, Hard
- ✅ **User Input** — Enter numbers row and column wise
- ✅ **Mistake Tracking** — Up to 3 mistakes allowed (Game Over after 3)
- ✅ **Hint System** — Get a random correct cell filled automatically
- ✅ **Erase Cell** — Remove a previously entered number
- ✅ **Check Board** — Verify if current entries are correct
- ✅ **Auto Solve** — Backtracking algorithm solves the puzzle instantly
- ✅ **New Game** — Start fresh with any difficulty anytime
- ✅ **Color Output** — Blue for given cells, Green for user input
- ✅ **Input Validation** — Invalid inputs handled gracefully

---

## 🧠 OOP Concepts Used

| Concept | Where Used |
|---|---|
| **Class** | `class Sudoku` — all game logic encapsulated |
| **Encapsulation** | Private members: `board`, `solution`, `given`, `mistakes`, `hintsUsed` |
| **Constructor** | `Sudoku()` initializes all members |
| **Member Functions** | `loadPuzzle()`, `enterNumber()`, `giveHint()`, `checkBoard()`, `autoSolve()`, `printBoard()` |
| **Data Hiding** | Board data is private, accessed only through public methods |

---

## 🔧 Algorithm

The game uses a **Backtracking Algorithm** to:
- Generate the correct solution for every puzzle
- Validate user inputs against the solution
- Auto-solve the puzzle on demand

```
isSafe()     → Checks row, column, and 3x3 box for conflicts
solveSudoku() → Recursively fills cells using backtracking
```

---

## 🖥️ How to Run

### Option 1 — OnlineGDB (Easiest)
1. Go to [onlinegdb.com](https://onlinegdb.com)
2. Set language to **C++**
3. Paste the code from `sudoku_game.cpp`
4. Click **Run**

### Option 2 — Local Machine
```bash
g++ -o sudoku sudoku_game.cpp -std=c++11
./sudoku
```

---

## 🎮 How to Play

```
1. Select difficulty: 1 (Easy), 2 (Medium), 3 (Hard)
2. Board is displayed — dots (.) are empty cells
3. Choose an action from the menu:
   1 → Enter a number (provide Row, Column, Number)
   2 → Erase a cell   (provide Row, Column)
   3 → Get a hint     (auto-fills one correct cell)
   4 → Check board    (verifies all entries so far)
   5 → Auto solve     (solves entire puzzle instantly)
   6 → New game       (restart with new difficulty)
   0 → Exit
```

### Sample Board
```
    1 2 3   4 5 6   7 8 9
   +---------+---------+---------+
 1 | 5 3 . | . 7 . | . . . |
 2 | 6 . . | 1 9 5 | . . . |
 3 | . 9 8 | . . . | . 6 . |
   +---------+---------+---------+
 4 | 8 . . | . 6 . | . . 3 |
 5 | 4 . . | 8 . 3 | . . 1 |
 6 | 7 . . | . 2 . | . . 6 |
   +---------+---------+---------+
 7 | . 6 . | . . . | 2 8 . |
 8 | . . . | 4 1 9 | . . 5 |
 9 | . . . | . 8 . | . 7 9 |
   +---------+---------+---------+

[Blue = Given]  [Green = Your Input]  [. = Empty]
Mistakes: 0/3   Hints Used: 0
```

---

## 📁 Project Structure

```
sudoku-game-cpp/
│
├── sudoku_game.cpp     # Main source code
└── README.md           # Project documentation
```

---

## 🛠️ Technologies Used

- **Language:** C++ (C++11)
- **Paradigm:** Object-Oriented Programming (OOP)
- **Algorithm:** Backtracking (Recursive)
- **IDE/Platform:** OnlineGDB / VS Code / Code::Blocks

---

## 🎓 Internship

This project was developed as part of the:

> **C++ Programming Internship — CodeAlpha**
> Intern: Hamza Asif


---

## 👤 Author

**Hamza Asif**
- GitHub: [hamza93-ai](https://github.com/hamza93-ai)
- LinkedIn: [linkedin.com/in/hamza-asif-b84523325](https://linkedin.com/in/hamza-asif-b84523325)

---
