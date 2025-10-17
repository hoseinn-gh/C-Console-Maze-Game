# Console-Based Maze Game in C

This repository contains the source code for a console-based maze game developed for a university-level Basic Programming course. The project's primary purpose is to serve as a practical demonstration of fundamental and intermediate C programming principles, from data structures and algorithms to low-level file I/O.

## Core Programming Concepts Demonstrated

This project showcases a variety of technical skills and concepts applied in a cohesive application.

* **Data Structures & Management**
    * **Structs:** The application heavily utilizes `struct` to model complex data entities, including `userdef` (for user profiles), `gamesave` (for game history), and `massagedef` (for the messaging system).
    * **Doubly Linked List:** A doubly linked list (`nodedef`) is implemented from scratch to record every player move during a game. This structure is central to the game-replay functionality, allowing for forward and backward traversal of the game's events.

* **File Handling & Persistence**
    * **Binary File I/O:** Employs low-level file operations (`fopen`, `fread`, `fwrite`, `fseek`) to persist all application data. The project uses binary files (`.bin`) for storing structured data (like user profiles and messages) efficiently.
    * **Text File Parsing:** Game maps are loaded from an external text file (`map.txt`), demonstrating text parsing and handling.
    * **Data Integrity:** A safe-update mechanism is implemented for user and message data. Changes are first written to a temporary copy file, which then replaces the original. This ensures that data is not corrupted if the program is interrupted during a write operation.

* **Dynamic Memory Management**
    * Demonstrates the correct use of `calloc` for dynamic memory allocation. This is primarily used for creating nodes in the game-replay linked list and for allocating temporary structures as needed, ensuring efficient and controlled memory usage.

* **Algorithmic Logic**
    * **Password Hashing:** Implements a simple substitution cipher as a 'hashing' mechanism to avoid storing passwords in plain text.
    * **Search and Sort:** Utilizes linear search for retrieving user records from binary files and implements a bubble sort algorithm to organize user messages based on the number of unread messages.
    * **State Management:** The core game loop is an example of a state machine, managing player position, map state (dual-layers), and interactions with various game objects.

* **Modular Design**
    * The codebase is organized into a collection of distinct functions, each responsible for a specific task (e.g., `home_page`, `game`, `massager`, `fileupdater`). This modular approach promotes code reusability, readability, and maintainability.

* **Advanced Console User Interface (UI)**
    * Leverages the `conio.h` library for direct, unbuffered keyboard input (`getch`), creating an interactive and responsive menu-driven system.
    * Uses ANSI escape codes to introduce color and styling to the console output, enhancing the user experience beyond standard text and providing visual feedback for game events and UI elements.

## How To Compile and Run

This game is a standard C project and can be compiled with a C compiler like GCC.

1.  **Prerequisites:**
    * A C compiler (like GCC or MinGW for Windows).
    * The game code (`game.c`).
    * A `map.txt` file in the same directory, containing the maze layouts.

2.  **Compilation:**
    Open your terminal or command prompt and run the following command:
    ```bash
    gcc game.c -o maze_game
    ```

3.  **Execution:**
    Run the compiled executable:
    ```bash
    ./maze_game
    ```
    On Windows, you can simply run:
    ```bash
    maze_game
    ```

---
*This project was developed by Hossein.GH.*
