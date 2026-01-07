#include "networking.h"

void clientLogic(int server_socket){
  while (1) {
    // do stuff
  }
}

// dont touch
int main(int argc, char *argv[] ) {
  // default server ip unless specified
  char* IP = "127.0.0.1";
  if(argc>1){IP=argv[1];}

  int server_socket = client_tcp_handshake(IP);
  printf("client connected to server.\n");
  clientLogic(server_socket);
}
