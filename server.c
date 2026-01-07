#include "networking.h"

void getMap(char * path, char map[][] *) {
  // read mapPath into buff
  char buff[BUFFER_SIZE];
  FILE * mapFD = fopen(path, "r");
  fgets(buff, sizeof(buff); mapFD)

  // get width and height of map, create 2d char array
  int w,h;
  sscanf(buff, "%d %d", w, h);
  char mapArray[w][h];

  // fill 2d char array


  // set 
  &mapArray = map;
}

void serverLogic(int client_socket){
  // do stuff
}

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();

  char* mapPath = "map.txt";
  if(argc>1){mapPath=argv[1];}

  while (1) {
    int client_socket = server_tcp_handshake(listen_socket);
    printf("server connected to client.\n");
    close(listen_socket);
    serverLogic(client_socket);
    close(client_socket);
    exit(0);
  }
}
