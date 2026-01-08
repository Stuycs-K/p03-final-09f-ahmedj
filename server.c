#include "networking.h"

char[][]* createMapArray() {
  char[][]* p;
  p = calloc(0, 100)
  return
}
char map[10][11] = ;

void setMap(char * path) {
  // read mapPath into array
  FILE * mapFD = fopen(path, "r");

  for (int i = 0; i < 10; i++) {
    fgets(map[i], 11, mapFD);
  }

  fclose(mapFD);
}

void printMap() {
  for (int i = 0; i < 10; i++) {
    printf("%s\n", map[i]);
    for (int j = 0; j<10; j++) {
      printf("%s", map[i][j]);
    }
  }
}

void serverLogic(int client_socket){
  // do stuff
}

int main(int argc, char *argv[] ) {
  // int listen_socket = server_setup();

  char* mapPath = "map.txt";
  if(argc>1){mapPath=argv[1];}

  setMap(mapPath);
  printMap();

  // while (1) {
  //   int client_socket = server_tcp_handshake(listen_socket);
  //   printf("server connected to client.\n");
  //   close(listen_socket);
  //   serverLogic(client_socket);
  //   close(client_socket);
  //   exit(0);
  // }
}
