/*client.c*/

#include "networking.h"

int y = 1;
int x = 1;
int oy,ox;
int mx, my;

int health = 10;
int ohealth;

char map[20][50];

struct PacketOut {
  int y, x;
  int health;
};

struct PacketIn {
  int my, mx;
  int oy, ox;
  int ohealth;
};


/* setup */
void setup() {
  printf("\033[48;5;0m");     // background black
  printf("\033[38;5;255m");   // foreground white
  printf("\033[?1049h");      // alternate screen buffer mode
}

void printMap() {
  for (int i = 0; i < (sizeof(map) / sizeof(map[0])); i++) {
    for (int j = 0; j < (sizeof(map[0])); j++) {
      if (i == y && j == x && health>0) {
        printf("C");
      }
      else if (i == oy && j == ox && ohealth>0) {
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

void printHealth() {
  printf("Player 2 Health : [");
  for (int i = 0; i < health; i++) {
    printf("C");
  }
  for (int i = 0; i < (10-health); i++) {
    printf(" ");
  }
  printf("]\n\n");
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
void handleDamage() {
  if (mx == x && my == y && health > 0) {
    health--;
  }
}
void clientLogic(int server_socket){
  // init
  read(server_socket, map, sizeof(map));
  printMap();

  struct PacketIn  *in  = calloc(1, sizeof(struct PacketIn));
  struct PacketOut *out = calloc(1, sizeof(struct PacketOut));


  // loop
  while (1) {
    handleKeyboard();
    handleDamage();

    if (read(server_socket, in, sizeof(*in)) <= 0) break;

    my = in->my;
    mx = in->mx;
    oy = in->oy;
    ox = in->ox;
    ohealth = in->ohealth;

    out->y = y;
    out->x = x;
    out->health = health;

    if (write(server_socket, out, sizeof(*out)) <= 0) break;


    printf("\033[2J");  // clear
    printf("\033[H");   // home
    printHealth();
    printMap();
  }
  free(in);
  free(out);
}
void end(int sig) {
    disableRawMode();
    exit(0);
}


int main(int argc, char *argv[] ) {
  signal(SIGINT, end);
  signal(SIGTERM, end);
  // default server ip unless specified
  char* IP = "127.0.0.1";
  if(argc>1){IP=argv[1];}

  int server_socket = client_tcp_handshake(IP);
  printf("client connected to server.\n");
  enableRawMode();
  clientLogic(server_socket);
}
