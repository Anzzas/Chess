# Chess Game
A classic two-player chess implementation where players can make moves, capture pieces, and perform special moves like castling.
## Overview
This is a command-line chess game designed for two human players to play against each other on the same computer. The game follows standard chess rules with a straightforward text-based interface.
## How to Play
Players take turns making moves. The game begins with White's turn, followed by Black.
### Making a Move
Each turn consists of two inputs:

First Selection: Enter the coordinates of the piece you want to move (e.g., "e2")
Second Selection: Enter the coordinates of the destination square (e.g., "e4")

Example move:
```cpp
(White's turn)
First selection: e2
Second selection: e4

(Black's turn)
First selection: e7
Second selection: e5
```

### Special Moves
#### Castling
To castle, enter one of these special commands as your first selection:

oo - Castle kingside (short castling)
oq - Castle queenside (long castling)

Example:
```cpp
(White's turn)
First selection: oo
```

No second selection is needed for castling.
## Features

Full implementation of chess rules
Two-player gameplay (no AI opponent)
Text-based interface with algebraic notation
Support for all special moves:

Castling (kingside and queenside)
En passant capture
Pawn promotion


Check and checkmate detection

## Requirements

lastest C++ version
Command-line terminal

## Board Representation

The chess board uses standard algebraic notation:

Files (columns) are labeled a-h from left to right
Ranks (rows) are labeled 1-8 from bottom to top
White pieces start at ranks 1-2, Black pieces at ranks 7-8
