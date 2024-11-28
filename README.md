# Mahjong_Agreg
This project is a Mahjong Game in C Raylib (still a work in progress). The object is too pratice C programming and to produce clear code (instead of the fastest one).

# TODO (don't hesitate to contribute)
## Logic of the Game (`logic/`)
- [ ] Write the logic of the game
    - [ ] Tile Implementation
    - [ ] Hand Implementation
    - [ ] All the rules with tests
    - [ ] complete game
    - [ ] Expert Program (AI) that computes probability

## Visuals(`visuals/`)
- [ ] Pretty print a game -> complete game in the terminal
- [ ] Client Side Rendering (Raylib)
- [ ] Try to compile with wasm

## Cryptographic(`crypto/`)
- [ ] basic elgamal (or RSA) cryptographics primitive
- [ ] implement an idea of protocol to prepare the cards at the beggining

## Server-Client for Multiplayer(`client/`)
- [ ] write basic client for multiplayers
- [ ] use cryptographic primitive to have no server (only peer to peer)
- [ ] Test connection when the program is compiled with wasm
- [ ] Implement basic server that connect people together.

## Combine Everything for the complete game(`game/`)
- [ ] Complete game loop
    - [ ] Handshake to define the map of tiles to cryptographic values
    - [ ] Games logic in action with communication

# Dependency between part of the project
- game depends on
    - visuals
    - client
    - logic
- visuals depends on
    - logic
- client depends on
    - crypto
- crypto depends on nothing
- logic depends on nothing
