# Interactive Sudoku Solver & Game
#### Video Demo: <YOUR_VIDEO_DEMO_URL_HERE>
#### Description:

This project is an interactive, graphic-based 9x9 Sudoku game and validator built in C++ using Object-Oriented Programming (OOP) principles and the `CMUgraphicsLib` library. Originally adapted from a Snake/Monopoly command-based framework, it has been fully refactored and migrated into a complete Sudoku environment featuring interactive cell selection, real-time board validation, and difficulty-based level loading.

The game is designed to run in a graphical window, offering players a clean dark-themed board division, dynamic highlighting of selected cells, starting clue protection, and instant feedback on placing numbers. It supports 3 difficulty levels (Easy, Medium, Hard) across 9 stages each, reading puzzles and pre-calculated solutions from custom-generated tab-separated text files.

---

## 🎮 Game Features

- **Interactive Cell Selection**: Players can click any cell on the 9x9 grid to select it. The selected cell is highlighted in a distinct background color.
- **Starting Clue Protection**: Starting clues loaded from level files are locked as immutable and cannot be edited or cleared by the player.
- **Keyboard Number Entry**: Selecting an empty cell opens input listening. Players can press `1-9` to enter a value, or `0`/`Backspace`/`Space` to clear a previously entered value.
- **Automatic Checking & Rules Validation**: Placement of numbers is validated in real-time using Sudoku rules (checking for duplicates in the row, column, and 3x3 subgrid block). If a rule is violated, a conflict error is printed in the status bar and the placement is reverted.
- **Pre-Solved Level Database**: Puzzles are generated such that they have exactly one unique solution. The solutions are appended directly underneath the problem block in the same file, keeping file handles unified.
- **Win Detection**: When the board is completely and correctly filled, the console prints `you win` and the status bar displays a congratulations message.
- **Toolbar Actions**:
  - **New Game**: Prompts the user to input a difficulty (1-3) and level (1-9) in the status bar to load the corresponding files.
  - **Reset**: Restores the board to the starting state of the current level, clearing all player-made entries.
  - **Exit**: Safely closes the graphics window and exits the program.

---

## 🛠️ Project Structure & File Contents

Here is a breakdown of the custom C++ files written and modified for this project:

- **[Main.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Main.cpp)**: Contains the main entry point and the core game loop. It instantiates the `ApplicationManager` controller and continuously queries user action clicks, executes the mapped action, and refreshes the graphics buffer.
- **[ApplicationManager.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/ApplicationManager.h) & [ApplicationManager.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/ApplicationManager.cpp)**: Acts as the central controller (Mediator Pattern) managing interactions between the grid model and user input/output interfaces. It registers user click areas and handles execution/deallocation of action objects.
- **[Grid.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Grid.h) & [Grid.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Grid.cpp)**: Manages the 9x9 grid matrix made up of `Cell` objects. It stores the path of the current level file, holds the correct solution grid values (`CellAns`), handles loading/clearing the board, and defines `isValidSudoku()` to check for rule violations.
- **[Cell.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Cell.h) & [Cell.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Cell.cpp)**: Represents an individual Sudoku square. It contains encapsulation fields for its grid coordinates, its current value, and a boolean flag `isGiven` marking whether it is an unmodifiable starting clue.
- **[CellPosition.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/CellPosition.h) & [CellPosition.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/CellPosition.cpp)**: A helper coordinates class. It maps 2D coordinates `(vertical, horizontal)` to cell IDs (1 to 81) and performs bounds validation to ensure clicks land inside valid grid parameters.
- **[Input.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Input.h) & [Input.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Input.cpp)**: Implements input handling from the keyboard and mouse. It tracks last clicked points to determine which cells were selected and captures key presses for numeric input.
- **[Output.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Output.h) & [Output.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Output.cpp)**: Handles rendering of the UI. It instantiates the `CMUgraphicsLib` drawing window, colors cell backgrounds (using normal vs. selected brush styles), centers and draws the clue/user numbers, and outlines the thick 3x3 block subgrid separators.
- **[UI_Info.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/UI_Info.h)**: A header file containing the global configuration struct `UI` which holds window dimensions, button sizes, font styling, and the custom color palette.
- **[Action.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Action.h) & [Action.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Action.cpp)**: Declares the abstract base interface for all executable commands in the game.
- **[NewGame.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/NewGame.h) & [NewGame.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/NewGame.cpp)**: Prompts the player to select the level difficulty and stage. It opens the text file, loads starting numbers, skips the divider, and loads the pre-calculated answers into the grid's solution array.
- **[Reset.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Reset.h) & [Reset.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/Reset.cpp)**: Reloads the original level file to reset user changes while preserving the current puzzle stage.
- **[SelectCell.h](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/SelectCell.h) & [SelectCell.cpp](file:///c:/Users/USER/Desktop/Apps%20by%20me/data/Sudoku/SelectCell.cpp)**: Action that handles grid selection, updates UI highlights, captures typed keys, updates the cell values, and runs the win condition check.

---

## 🧠 Design Decisions & Refactoring Choices

1. **Elimination of the `mutable` Keyword**:
   Initially, the `GetUserAction` function was declared as a `const` member function in `Input`. However, mapping click coordinates requires updating `lastX` and `lastY` inside the `Input` class. Modifying class attributes within a `const` function is illegal in standard C++ unless the variables are marked as `mutable`. We chose to make `GetUserAction` a standard non-const function across both `Input` and `ApplicationManager`. This approach respects C++ const-correctness principles, avoids compiler errors, and eliminates the need to use `mutable`.
2. **Pre-solved Level Formatting**:
   Instead of embedding a resource-heavy solving algorithm inside the game executable, we appended the correct 9x9 solved grid directly to the bottom of each level `.txt` file, separated by a `# Solution` header line. This approach is highly efficient: the starting parser reads the first 81 values and stops, keeping level loading backwards compatible. When needed, the solution parser simply skips forward to read the answers into `CellAns` in one rapid pass.
3. **Layered Separator Overlay**:
   To draw the thick 3x3 block subgrid separators, we draw the standard cells first using thin grid borders, and then perform a separate rendering pass (`DrawGridLines`) to overlay the thick boundaries. This ensures that subsequent cell repaints do not partially crop or overlap the thick border lines.
4. **Stateful Click Registration**:
   Because `GetUserAction()` blocks and consumes the mouse click to identify a `GRID_AREA` action, executing the subsequent `SelectCell` action would normally require a second click to register which cell the user intended to select. To resolve this double-clicking issue, we cache the original coordinates (`lastX`, `lastY`) inside `Input` during the action query, allowing `SelectCell::Execute()` to query and resolve the grid coordinate instantly.

---

## 🚀 Compilation & Execution

Open the project solution file `PT-Project.sln` inside Visual Studio (2019/2022) on Windows. Ensure the build configuration is set to **Debug/x86** or **Release/x86** (as `CMUgraphicsLib` is compiled for 32-bit Windows targets), then press **F5** to compile and run the application.
