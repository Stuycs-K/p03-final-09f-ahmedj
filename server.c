#include "networking.h"

void serverLogic(int client_socket){
  while (1) {
    // do stuff
  }
}

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();

  while (1) {
    int client_socket = server_tcp_handshake(listen_socket);
    printf("server connected to client.\n");
    close(listen_socket);
    serverLogic(client_socket);
    close(client_socket);
    exit(0);
  }
}
