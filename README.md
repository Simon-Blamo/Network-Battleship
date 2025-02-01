# Network BattleShip Game

This project is a networked, multiplayer Battleship game implemented in C++. It consists of a server `(server.cpp)` that manages game states and client connections, and a client `(client.cpp)` that allows players to interact with the game. The game uses a grid system `(grid.h)` for tracking the positions of ships and a specialized network packet structure `(network_packet.h)` for communication between the server and clients.

## File Specifics

**network_packet.h:** Contains the definition of the network_packet struct, which is used to communicate game-related data (like player actions and game state updates) between the server and clients.

**grid.h:** Defines the grid, oceanGrid, and targetGrid classes used to manage the game board for each player. It includes functions for initializing the grid, placing ships, updating grid states, and printing the grid to the console.

**server.cpp**: Implements the Battleship game server. It sets up a network socket, listens for incoming client connections, and handles incoming and outgoing game data.

**client.cpp**: Implements the Battleship game client. It connects to the server, processes user input, and handles communication with the server.

## Getting Started

1. Clone the repository:

   `git clone https://github.com/TCNJ-degoodj/battleship-Simon-Blamo.git`
2. Navigate to the Battleship directory:

   `cd battleship-Simon-Blamo`
3. Compile program:

   `make`
4. Run program:

   Server:`./server`

   Client: `./client`

## Gameplay

- Start the server first, then connect clients.
- Players place their ships on their ocean grid at the start of the game.
- Players take turns to attack by specifying coordinates on the target grid.
- The game continues until all ships of a player are sunk.

## Dependencies

- Linux
- C++ Standard Library
- POSIX Threads

<!---([![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/gU0jDd6v)) ---
