# Minesweeper by Itamar Shaked
My own version of a classic game I'm obsessed with in the terminal.

## Clone and Play
To clone and play the game, clone it using:
```
git clone https://github.com/itamar-skd/Minesweeper
```

## Building with CMake
This project was made using CMake. To build it, type the following from the repository directory:
```bash
mkdir build && cd build
cmake .. && make
```

Executables are generated in `Minesweeper/build/bin` by default.

## Running the Game
After compiling the project, the game can be played through:
```bash
cd bin
./minesweeper
```
To get a list of useful arguments and a how-to-play, I highly recommend running the executable with the `--help` argument for the first time playing.

## Introduction to Minesweeper
If you're unfamiliar with minesweeper, here's a quick rundown:<br/>
Minesweeper is a 2D thinking game. A game board of cells is generated, where each cell could contain a mine. Your job as the player is to discover all the mines and reveal all "safe" (mine-less) cells.<br/>
The player can perform one of the following for each cell:
1. Reveal its contents (left-click). This should **only** be done if the player is sure the cell does not contain a mine.
2. Flag it (right-click). This should be done if the player suspects the cell contains a mine. Flagging a cell does not reveal its contents and does not cause the mine to explode.

If the player reveals a cell which has a mine, it's game over.<br/>
If the player reveals all safe cells and flags all mines, they win.<br/><br/>

All safe cells are assigned a number, corresponding to the number of mines in their surrounding 3x3 square. If a cell has two adjacent mines, for example, it'll be shown as "2" on the board.<br/>
Hence, if a cell shows 2 and a player flagged 2 cells adjacent to it, the player should reveal the other adjacent cells (assuming his flag placements are correct.)

```
2 F 1
F 2   <
1     <
  ^ ^ These cells can be revealed
```

## Some behind the scenes
Other than the user interface (which I've implemented using ncurses), the actual game can be mostly separated into two somewhat difficult components to implement:

### 1. Generating the Board
I decided to go for a simple 2D vector with as many elements as the area of the desired matrix. In order to not mess with out-of-bounds logic everywhere in my code, I came up with the idea of generating a throwaway out-of-bounds object to mess with.<br/>
The real problem was with generating the mines. My approach to this was to generate a vector of all indices in the matrix, shuffle it using the fast and efficient algorithm library, then take the first `--num_bombs` indices to flag as mines. From there, it was as simple as incrementing the number of surrounding bombs parameter for all adjacent cells.

### 2. Moves
Flagging is quite simple. Just set an `is_flag` parameter to true to flag a cell and false to remove the flag.<br/>
The problem starts, however, with revealing a cell's content. See, when you discover a cell that has no adjacent mines, Minesweeper takes it on itself to do the work for you and recursively reveal all adjacent cells. I say recursively because if there is another such cell then of course the same happens there. This is of course not something the player should fear, because it's guaranteed that no mines can be activated using this logic.<br/><br/>
However, a feature not a lot of players are aware of is that clicking a cell that's already been revealed will perform the same task **if and only if** the player flagged a number of cells adjacent to it as the amount of actual mines there actually are next to it (`__num_surrounding_bombs == num selected adjacent flags`)

### 2.1 First move
What most minesweeper players don't know is that the first move has a little more logic to it than the regular move.<br/>
If the player were to click on a cell that has at least 1 surrounding mines, only that one cell will be revealed to the player making the game practically impossible to win without guessing. To deal with this, Minesweeper secretly regenerates the board until the cell the player clicked on first has no surrounding bombs, forcing the recursive reveal feature to activate. I've implemented this by resetting the cells back to zero and recalling the `__init_bombs()` function.
