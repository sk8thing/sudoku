# Description
Sudoku game and solver made using [SDL2](https://www.libsdl.org/index.php) library and backtracking for the sudoku generator/solver part.
## Running the game
Start by cloning the repository
```
git clone https://github.com/sk8thing/sudoku.git
```
Download the executable from the release tab and put it inside the ***/bin*** folder, ***next to the required dlls***.
If you want to compile it yourself I suggest using the CMake scripts inside the ***/cmake*** folder along with the CMakeLists example.
After all that you can run the executable
```
./path/to/bin/sudoku.exe
```
## Controls
ARROW_UP/DOWN/LEFT/RIGHT - move cursor\
1-9 - set value\
RCTRL - clear value\
RSHIFT - resets the board and generates a new one\
RALT - solves the sudoku
## Backtracking
In order to generate/solve the sudoku a backtracking algorithm is used.
The algorithm goes through every single possible candidate to the solution and checks whether it leads to a valid solution or not.
If it doesn't, then it gets eliminated and the algorithm goes back and checks the rest of the candidates.
After generating a valid sudoku board, a random number of values is removed from it.
## Screenshots
![1](https://user-images.githubusercontent.com/101511232/166741103-b27350c2-b8d2-47a9-b266-f8e09ba1bf91.png)
![2](https://user-images.githubusercontent.com/101511232/166741210-dfa4594c-bee7-4c70-8dd3-b02706589262.png)
![3](https://user-images.githubusercontent.com/101511232/166741271-c14a97aa-1aa1-434a-b96f-d6912bbd21e8.png)
