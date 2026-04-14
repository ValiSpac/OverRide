#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char msg[180];
  int msg_len;

  char username[40];
} user_t;

void shell(void) {
  char buf[128];
  fgets(buf, 0x80, stdin);
  system(buf);
}

void set_msg(user_t *user) {
  char buf[1024];
  memset(buf, 0, sizeof(buf));

  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets(buf, sizeof(buf), stdin);

  strncpy(user->msg, buf, user->msg_len);
}

void set_username(user_t *user) {
  char buf[140];
  memset(buf, 0, 128);

  puts(">: Enter your username");
  printf(">>: ");
  fgets(buf, 0x80, stdin);

  // copies up to 40 chars into user->username
  for (int i = 0; i <= 40; i++) {
    if (buf[i] == 0)
      break;
    user->username[i] = buf[i];
  }

  printf(">: Welcome, %s", user->username);
}

void handle_msg(void) {
  user_t user;
  memset(&user, 0, sizeof(user));
  user.msg_len = 0x8c;

  set_username(&user);
  set_msg(&user);

  puts(">: Msg sent!");
}

int main(void) {
  puts("--------------------------------------------\n"
       "|   ~Welcome to l33t-m$n ~    v1337        |\n"
       "--------------------------------------------");
  handle_msg();
  return 0;
}
