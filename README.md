# Mine-Sweeper

A feature-rich Minesweeper game for Windows, written in C, with enhanced Unicode graphics and colored console output.  
This project is modular and extensible, making use of clear separation between game logic, UI, and data management.

![Startup Screen](https://github.com/Kebabist/Mine-Sweeper/assets/83098161/b201b64e-e129-4617-b4ac-6971d2d79ac9)
![Main Menu](https://github.com/Kebabist/Mine-Sweeper/assets/83098161/59057d05-abc3-4973-a6ef-be8065703fe7)
![MineField](https://github.com/Kebabist/Mine-Sweeper/assets/83098161/1ba2bb66-bba5-49cd-ac19-2435f0297ff4)
![Lose event](https://github.com/Kebabist/Mine-Sweeper/assets/83098161/d2a250ce-47bd-4eed-a1a4-f23560f3526f)
![Win event](https://github.com/Kebabist/Mine-Sweeper/assets/83098161/22b4a608-5a90-4593-896b-6e000fbfe76a)

---

## Features

- **Classic Minesweeper Gameplay**: Fully functional game board, random bomb placement, win/loss detection, and automatic cell revealing.
- **Unicode & Colorful UI**: Uses Unicode symbols and ANSI colors for a visually appealing experience.
- **Animated Welcome Screen**: Eye-catching intro animation using Unicode and color codes.
- **Player Profiles**: Track wins, losses, and play time (partially implemented, see notes).
- **Keyboard Navigation**: Interact with the board and menus via keyboard controls.
- **Cheat & Debug**: Includes hidden commands for debugging or exploring the board's layout.
- **Modular Structure**: Logic, UI, and data handling are separated for easy extension and maintenance.

---

## Getting Started

### Prerequisites

- **Operating System**: Windows is recommended (uses Windows-specific console APIs).
- **Compiler**: Any standard C compiler (e.g., GCC, MSVC).
- **Unicode/UTF-8**: Console must support Unicode (see below).

### Unicode Setup

For the best experience, enable Unicode/UTF-8 in your console:

- **Windows**:
  1. Go to _Control Panel_ → _Region and Language_.
  2. Under _Administrative_ → _Language for non-Unicode programs_, click _Change system locale_.
  3. Enable _Beta: Use Unicode UTF-8 for worldwide language support_.
  4. Restart your computer.

- **Mac/Linux**:  
  This game is primarily designed for Windows, but if porting, ensure your terminal supports UTF-8 and install suitable Unicode fonts.

### Fullscreen Console

- For optimal visuals, run your console window in fullscreen (Press `F11`).

---

## How to Build & Run

1. Clone this repository:
   ```sh
   git clone https://github.com/Kebabist/Mine-Sweeper.git
   ```
2. Open the project in your IDE or use the command line:

   ```sh
   cd Mine-Sweeper/Takhribchi
   gcc Source.cpp -o minesweeper -std=c99 -lwinmm
   .\minesweeper.exe
   ```

   - (Adjust the compile command for your compiler/toolchain.)

---

## Project Structure

- **Source.cpp**: Entry point, handles game initialization and main loop.
- **Game_logic.h**: Core game logic (board creation, bomb placement, cell uncovering, win/loss checks).
- **MyPrint.h**: UI rendering, menu, and welcome animation.
- **Macros.h**: Color and Unicode symbol definitions for console output.
- **Structs.h**: Data structures for board, cell, and player profiles.
- **RWFile.h**: Functions for (partial) file I/O, such as saving and loading profiles.
- **Functions_inc.h**: Declarations of all major functions.
- **Header.h**: General include guard.

---

## Known Issues / TODO

- **File I/O**: Saving/loading of player profiles is incomplete and needs further work.
- **Cross-Platform**: Currently optimized for Windows. Porting to other systems may require adjustments.
- **Some logic snippets**: Parts of the game logic code are adapted from other sources. Attribution or further refactoring may be required.

---

## Credits

- Portions of the logic are based on community code snippets.  
- Main development by [Kebabist](https://github.com/Kebabist).

---

## License

This project is for educational and personal use. See `LICENSE` for details.

---

## Feedback & Contributions

Suggestions, bug reports, and contributions are welcome! Please open an issue or pull request.
