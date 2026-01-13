/*server.c*/

#include "networking.h"

int y = 2;
int x = 2;
int oy,ox;

int mx = 5;
int my = 5;

int health = 10;

char map[20][50] = {
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

/* setup */
void setup() {
  printf("\033[48;5;0m");     // background black
  printf("\033[38;5;255m");   // foreground white
  printf("\033[?1049h");      // alternate screen buffer mode
}

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
  printf("\033[2J");  // clear
  printf("\033[H");   // home
  for (int i = 0; i < (sizeof(map) / sizeof(map[0])); i++) {
    for (int j = 0; j < (sizeof(map[0])); j++) {
      if (i == y && j == x) {
        printf("A");
      }
      else if (i == oy && j == ox) {
        printf("B");
      }
      else if (i == my && j == mx) {
        printf("M");
      }
      else {
        printf("%c", map[i][j]);
      }
    }
    printf("\n");
  }
}

/* termios stuff */
struct termios orig_term;
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_term);
    struct termios raw = orig_term;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
    printf("\033[?1049l");
}
int kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
}
int getch() {
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1) return c;
    return 0;
}
void move(int dy, int dx) {
  if (map[y+dy][x+dx] == ' ' || map[y+dy][x+dx] == 'B') {
    y+=dy;
    x+=dx;
  }
}
void tickMonster() {
  int monsterFacing = rand()%4;

  switch (monsterFacing) {
    case 0: // face right
      if (map[my][mx + 1] == ' ') {
        mx++;
      }
      break;
    case 1: // face up
      if (map[my-1][mx] == ' ') {
        my--;
      }
      break;
    case 2: // face left
      if (map[my][mx - 1] == ' ') {
        mx--;
      }
      break;
    case 3: // face down
      if (map[my+1][mx] == ' ') {
        my++;
      }
      break;
  }
}
void handleKeyboard() {
  if (kbhit()) {
    char c = getch();
    if (c == 'w') move(-1,0);
    if (c == 's') move(1,0);
    if (c == 'a') move(0,-1);
    if (c == 'd') move(0,1);
    if (c == 27) exit(0); // ESC
  }
}
void serverLogic(int client_socket){
  // init
  write(client_socket, map, sizeof(map));
  printMap();

  // loop
  while (1) {
    handleKeyboard();
    tickMonster();

    write(client_socket, &y, sizeof(y));
    write(client_socket, &x, sizeof(x));
    write(client_socket, &my, sizeof(my));
    write(client_socket, &mx, sizeof(mx));
    read(client_socket, &oy, sizeof(oy));
    read(client_socket, &ox, sizeof(ox));

    printMap();

    // usleep(10000);
  }
}

int main(int argc, char *argv[] ) {
  srand(time(NULL));
  int listen_socket = server_setup();
  char* mapPath = "map.txt";
  if(argc>1){mapPath=argv[1]; setMap(mapPath);}

  int client_socket = server_tcp_handshake(listen_socket);
  printf("server connected to client.\n");
  close(listen_socket);
  enableRawMode();
  serverLogic(client_socket);
  close(client_socket);
  disableRawMode();
  exit(0);
}
