# Mastermind – Minigame Project

This project is a classic Mastermind game written in C.

## Features
- Classic color-based Mastermind rules
- Modular design with separate data structures:
  - Peg
  - Code
  - Attempt
  - Game
- Dynamic memory allocation
- Console-based gameplay

## How to compile
```bash
gcc -Wall -Wextra -std=c11 main.c game.c code.c attempt.c peg.c -o mastermind

## How to run
./mastermind

