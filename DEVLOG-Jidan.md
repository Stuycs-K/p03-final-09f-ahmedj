# Dev Log:

This document must be updated daily every time you finish a work session.

## Jidan Ahmed

### 2026-01-05 - Brainstorming
Decided on project idea during class and thought about proposal.

### 2026-01-06 - Proposal
Finished writing proposal and started devlog.

### 2026-01-07 - Networking
Added networking between server and client.

### 2026-01-08 - Map
Struggled with getting map to print properly.

### 2026-01-09 - Map
Map is now a 20 x 20 array and prints properly. There is a hardcoded default map.

### 2026-01-10 - Research
Researched how to take in keyboard input using termios.

### 2026-01-11 - Networking, drawing game
Server and client now send each other their coordinates and control coordinates with WASD. There is now a game loop where keyboard input is read and the map is drawn with player locations.

### 2026-01-12 - Maps
Added new ASCII Maps to the game

### 2026-01-12 - Monster
Added a monster that moves around randomly, cannot move through walls. Tested two player functionality with another lab machine.

### 2026-01-13 - Tweaks
Tweaked monster movement code and let server send monster position over to client.

### 2026-01-14 - Health Bars
Both players now have health bars. Touching the monster reduces health. Each player sees own health and not the other's. If players are dead, they are no longer seen in the game.

### 2026-01-15 - Improvements
Used signals to disable raw input mode, calloced struct Packets to send and recieve over socket.
