#include <string.h>
#include <stdlib.h>

#include "env.h"

char* env_get(char** env, char* name) {
  int i = 0;
  char* pair;
  char* result;
  unsigned int name_length = strlen(name);
  unsigned int value_length;

  while ((pair = env[i++]) != NULL) {
    if (strncmp(name, pair, name_length) == 0) {
      value_length = strlen(pair) - name_length; // -1 for `=` and +1 for \0
      result = malloc(value_length);
      strncpy(result, pair + name_length + 1, value_length);

      return result;
    }
  }

  return NULL;
}
