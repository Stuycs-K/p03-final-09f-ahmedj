/*server.c*/

#include "networking.h"

int y = 2;
int x = 2;
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

char* mapPath = "map.txt";

int numRows = (sizeof(map) / sizeof(map[0]));
int numCols = sizeof(map[0]);

void setMap(char * path) {
  // read mapPath into array
  FILE * mapFD = fopen(path, "r");
  for (int i = 0; i < numRows; i++) {
    fgets(map[i], numCols+1, mapFD);
    if (map[i][strlen(map[i])-1] == '\n') {
      map[i][strlen(map[i])-1] = '\0';
    }
  }

  fclose(mapFD);
}

void printMap() {
  for (int i = 0; i < (sizeof(map) / sizeof(map[0])); i++) {
    for (int j = 0; j < (sizeof(map[0])); j++) {
      if (i == y && j == x) {
        printf("S");
      }
      else if (i == oy && j == ox) {
        printf("P");
      }
      else {
        printf("%c", map[i][j]);
      }
    }
    printf("\n");
  }
}

void serverLogic(int client_socket){
  // init
  write(client_socket, map, sizeof(map));
  printMap();

  // loop
  while (1) {
    write(client_socket, &y, sizeof(y));
    write(client_socket, &x, sizeof(x));
    read(client_socket, &oy, sizeof(oy));
    read(client_socket, &ox, sizeof(ox));    
  }
}

int main(int argc, char *argv[] ) {
  int listen_socket = server_setup();
  char* mapPath = "map.txt";
  if(argc>1){mapPath=argv[1]; setMap(mapPath);}

  
  int client_socket = server_tcp_handshake(listen_socket);
  printf("server connected to client.\n");
  close(listen_socket);
  serverLogic(client_socket);
  close(client_socket);
  exit(0);
}
