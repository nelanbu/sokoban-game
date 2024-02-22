# Sokoban Puzzle Game

## Overview
This project is an implementation of the Sokoban game in C++, focusing on the use of classes, stacks, queues, and linked lists to manage game state and logic. Sokoban, meaning 'warehouse keeper' in Japanese, is a classic puzzle game where the player aims to move boxes to designated locations in a maze-like setting by pushing them around, adhering to specific game rules. This project is part of the Data Structures course at METU.

## Features

- **Sokoban Game Logic:** Implements the Sokoban game with levels represented as 6x8 block puzzles. The game logic includes moving the player and boxes within the game constraints.

- **Game State Management:** Utilizes classes to encapsulate the game's state, including player position, box positions, and target locations. The game state updates according to player actions (move up, down, left, right).

- **Movement and Rules Enforcement:** Includes methods to move the player in all four directions while ensuring moves adhere to Sokoban's rules: boxes can only be pushed, not pulled; only one box can be moved at a time; the player cannot move through walls or boxes.

- **Dynamic Puzzle Representation:** Features a text-based user interface for game interaction, with different ASCII characters representing the player, boxes, walls, empty spaces, and target locations.

- **StackQueue Implementation:** A mixed StackQueue template class that supports operations like `push_front`, `pop_front`, and `pop_rear`, demonstrating an advanced data structure for managing elements.

- **Linked List Integration:** Enhances the StackQueue class with a doubly-linked list, allowing for dynamic storage and manipulation of game states, including undo and replay functionalities.
