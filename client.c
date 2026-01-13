/*client.c*/

#include "networking.h"

int y = 1;
int x = 1;
int oy,ox;
int mx, my;

int health = 10;

char map[20][50];

/* setup */
void setup() {
  printf("\033[48;5;0m");     // background black
  printf("\033[38;5;255m");   // foreground white
  printf("\033[?1049h");      // alternate screen buffer mode
}

void printMap() {
  printf("\033[2J");  // clear
  printf("\033[H");   // home
  for (int i = 0; i < (sizeof(map) / sizeof(map[0])); i++) {
    for (int j = 0; j < (sizeof(map[0])); j++) {
      if (i == y && j == x) {
        printf("C");
      }
      else if (i == oy && j == ox) {
        printf("D");
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
  if (map[y+dy][x+dx] == ' ' || map[y+dy][x+dx] == 'D') {
    y+=dy;
    x+=dx;
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

void clientLogic(int server_socket){
  // init
  read(server_socket, map, sizeof(map));
  printMap();

  // loop
  while (1) {
    handleKeyboard();

    read(server_socket, &oy, sizeof(oy));
    read(server_socket, &ox, sizeof(ox));
    read(server_socket, &my, sizeof(my));
    read(server_socket, &mx, sizeof(mx));
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
  enableRawMode();
  clientLogic(server_socket);
  disableRawMode();
}
