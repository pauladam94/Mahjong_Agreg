# Metal Mahjong ![](./data/Logo_Mental_Mahjong2.svg)
This project is a Mahjong Game in C Raylib (still a work in progress). The object is too pratice C programming and to produce clear code (instead of the fastest one). This project is going to use the [mental poker](https://en.wikipedia.org/wiki/Mental_poker) algorithm to assure that no player can cheat and without any third party server.



# TODO (don't hesitate to contribute)
## Logic of the Game (`logic/`)
- [ ] remove the loaded of textures from `logic/tile.c` this should be in
visuals only
- [ ] Write the logic of the game
    - [x] Tile Implementation
    - [x] Hand Implementation
    - [ ] All the rules with tests
    - [ ] Complete game
    - [ ] Expert Program (AI) that computes probability

## Visuals(`visuals/`)
- [ ] Create an abstraction layer between the GUI and the code that does
something with it, to be able to test the GUI.
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

## Put everything on a website(`website`)
- [ ] compile to wasm and make work a wasm executable compiled with wasm

# Dependency between part of the project
- `website/` depends on `game/`
- `game/` depends on
    - `visuals/`
    - `client/`
    - `logic/`
- visuals depends on
    - `logic/`
- client depends on
    - `crypto/`
- `crypto/` depends on nothing
- `logic/` depends on nothing
