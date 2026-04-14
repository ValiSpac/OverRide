#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char backup_path[100];
  char buf;

  if (argc != 2) {
    printf("Usage: %s filename\n", argv[0]);
  }

  FILE *log = fopen("./backups/.log", "w");
  if (log == NULL) {
    printf("ERROR: Failed to open %s\n", "./backups/.log");
    exit(1);
  }

  log_wrapper(log, "Starting back up: ", argv[1]);

  FILE *src = fopen(argv[1], "r");
  if (src == NULL) {
    printf("ERROR: Failed to open %s\n", argv[1]);
    exit(1);
  }

  strncpy(backup_path, "./backups/", 11);
  strncat(backup_path, argv[1], 99 - strlen(backup_path));

  int dst = open(backup_path, O_WRONLY | O_CREAT | O_TRUNC, 0640);
  if (dst < 0) {
    printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
    exit(1);
  }

  while (true) {
    buf = fgetc(src);

    if (buf == EOF) {
      log_wrapper(log, "Finished back up ", argv[1]);
      fclose(src);
      close(dst);
      return 0;
    }

    write(dst, &buf, 1);
  }
}
