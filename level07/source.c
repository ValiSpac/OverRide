#include <stdio.h>
#include <string.h>

int read_number(uint32_t *data) {
  printf(" Index: ");
  uint32_t index = get_unum();
  printf(" Number at data[%u] is %u\n", index, data[index]);
  return 0;
}

int store_number(uint32_t *data) {
  printf(" Number: ");
  uint32_t number = get_unum();

  printf(" Index: ");
  uint32_t index = get_unum();

  if (index % 3 == 0 || number >> 24 == 0xb7) {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
  }

  data[index] = number;
  return 0;
}

int main(int argc, char **argv, char **envp) {
  char input[20];
  char storage[400];

  for (char **arg = argv; *arg != NULL; arg++) {
    memset(*arg, 0, strlen(*arg));
  }

  for (char **env = envp; *env != NULL; env++) {
    memset(*env, 0, strlen(*env));
  }

  memset(storage, 0, sizeof(storage));
  memset(input, 0, sizeof(input));

  puts("----------------------------------------------------\n"
       "  Welcome to wil's crappy number storage service!  \n"
       "----------------------------------------------------\n"
       " Commands:                                          \n"
       "    store - store a number into the data storage   \n"
       "    read  - read a number from the data storage    \n"
       "    quit                                           \n");

  while (1) {
    int success = 1;

    printf("Input command: ");
    fgets(input, sizeof(input), stdin);

    // Strip trailing newline
    size_t len = strlen(input);
    if (len > 0)
      input[len - 1] = '\0';

    if (strcmp(input, "store") == 0) {
      success = store_number(storage);
    } else if (strcmp(input, "read") == 0) {
      read_number(storage);
      success = 0;
    } else if (strcmp(input, "quit") == 0) {
      return 0;
    }

    if (success == 0)
      printf(" Completed %s command successfully\n", input);
    else
      printf(" Failed to do %s command\n", input);

    memset(input, 0, sizeof(input));
  }
}
