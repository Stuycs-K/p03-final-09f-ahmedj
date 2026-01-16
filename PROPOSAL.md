# Final Project Proposal

## Group Members:

Jidan Ahmed

# Intentions:

Create a multiplayer game where players exist on the same map and see each other.

# Intended usage:

A host player runs the server program with the path to a "map" file to start a game.
Another guest player runs the client program, with an optional server ip, to join the same game with the same map.

Players can move around the map with WASD.

# Technical Details:

I will have 2 programs, a server that sends the map initially and host's location continually to the client over a socket. The client sends back the guest's location to the host. Both players can see each other on the map. There is also a monster and player health. The monsters coordinates are sent from the server to the client. Both players send their health amounts to the other player.

The map file made of spaces and characters in a text file. It is read by the server program and converted to a 2d array. The array is sent to the client over the socket.

The game is viewed through ASCII in the terminal.

The terminal is manipulated using termios to read raw keyboard inputs.

I will be breaking up the project into file reading, terminal manipulation and controls, networking then optional features

# Intended pacing:
1/6/26 - Set up socket and client program
1/8/26 - Create map system and server program
1/10/26 - See game in terminal
1/12/26 - Control players
1/14/26 - Optional features
1/16/26 - Finishing touches

