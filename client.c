/*client.c*/

#include "networking.h"

int y = 1;
int x = 1;
int oy,ox;


char map[20][20] = {
  {"##########"},
  {"#        #"},
  {"#        #"},
  {"#  #     #"},
  {"#  #     #"},
  {"#  ###   #"},
  {"#    #   #"},
  {"#    #   #"},
  {"#        #"},
  {"##########"}
};

void printMap() {
  for (int i = 0; i < (sizeof(map) / sizeof(map[0])); i++) {
    for (int j = 0; j < (sizeof(map[0])); j++) {
      if (i == y && j == x) {
        printf("C");
      }
      else if (i == oy && j == ox) {
        printf("S");
      }
      else {
        printf("%c", map[i][j]);
      }
    }
    printf("\n");
  }
}

void clientLogic(int server_socket){
  // init
  read(server_socket, map, sizeof(map));
  printMap();

  // loop
  while (1) {
    read(server_socket, &oy, sizeof(oy));
    read(server_socket, &ox, sizeof(ox)); 
    write(server_socket, &y, sizeof(y));
    write(server_socket, &x, sizeof(x));

    printMap();
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
