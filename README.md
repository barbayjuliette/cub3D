# Cub3D

## Introduction
This project is inspired by the world-famous Wolfenstein 3D game. 
We have to create our first raycaster, using MiniLibx (a simple X-Window programming API created by 42).

## Description

We have to create a simple version of the game. The player needs to be able to walk around the maze. 
Different textures have to be rendered depending on which direction the player is facing.
Wall collision is also implemented.

### Parsing

The program takes one argument, a *.cub file which contains all the information for the game: the 4 textures, floor and ceiling color and the map with the player direction.
The information in this file has to follow a strict format. If it doesn't an error message will be returned.
See example in test.cub;

- 1 = Wall
- 0 = Empty space
- If there are spaces, they are replaced with a wall.
- N/S/W/E: Player position
- If we want to put spaces in the texture path, we have to put the whole path inside quotation marks:
-   WE "./path to the west texture" ✔️
-   WE ./path to the west texture ❌

We validate the map, texture, and color to make sure they are valid. If they are not, an appropriate error message is returned.

### Game
We used raycasting to render the maze on the screen.

The left and right arrow keys of the keyboard allow the player to look left and right in the maze (Rotate in a circle).
The W / A keys and UP / DOWN keys allow the player to move forwards / backwards.
The S and D keys allow the player to move right and left.

To quit the program:
- Click the cross on the window
- ESC
The program is closed in a clean way (no memory leak).

## How to run

make
./cub3D test.cub

## Compatibility

The program works for Linux. If using MAC, another Makefile is provided, but a few adjustments have to be made in the code before compiling successfully.
