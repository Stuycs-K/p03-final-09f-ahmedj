#include "networking.h"



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

char* mapPath = "map.txt";

int numRows = (sizeof(map) / sizeof(map[0]));
int numCols = sizeof(map[0]);

void setMap(char * path) {
  // read mapPath into array
  FILE * mapFD = fopen(path, "r");
  for (int i = 0; i < numRows; i++) {
    fgets(map[i], numCols+1, mapFD);
  }

  fclose(mapFD);
}

void printMap() {
  for (int i = 0; i < (sizeof(map) / sizeof(map[0])); i++) {
    printf("%s\n", map[i]);
    // for (int j = 0; j < 10; j++) {
    //   printf("%s", map[i][j]);
    // }
  }
}

void serverLogic(int client_socket){
  // do stuff

}

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();
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
