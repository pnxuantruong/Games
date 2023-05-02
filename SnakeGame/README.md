# About

## I created a snake game using Simple DirectMedia Layer (SDL).

Snake Game contains 3 modes:

1. Human Control: which lets you control the snake using key buttons ( w - UP, s - DOWN, a - LEFT, d - RIGHT)

2. Auto Snake: The snake will auto find out path to food by 2 stageries are DFS and A*.

3. Human And Auto Snake: you can compete with computer

Note: Click r to reload screen that stopped.

## How to change mode:

Edit method Start() in file Game.cpp to change between 3 modes (I wrote some hint for that)

Change stagery between DFS and A* in method ChooseDirection() of file SearchMap.cpp 

# Demo:

## Human Control:

![](https://github.com/pnxuantruong/Games/blob/main/SnakeGame/videos/Human.gif)

## DFS:

![](https://github.com/pnxuantruong/Games/blob/main/SnakeGame/videos/DFS.gif)

## AStar:

![](https://github.com/pnxuantruong/Games/blob/main/SnakeGame/videos/AStar.gif)
