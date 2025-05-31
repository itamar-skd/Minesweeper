# Minesweeper
My own version of a classic game I'm obsessed with in the terminal.

# Clone and Play
To clone and play the game, clone it using:
```
git clone https://github.com/itamar-skd/Minesweeper
```

# Building with CMake
This project was made using CMake. To build it, type the following from the repository directory:
```bash
mkdir build && cd build
cmake .. && make
```

Executables are generated in `Minesweeper/build/bin` by default.

# Running the Game
After compiling the project, the game can be played through:
```bash
cd bin
./minesweeper
```
To get a list of useful arguments and a how-to-play, I highly recommend running the executable with the `--help` argument for the first time playing.

# Introduction to Minesweeper
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
