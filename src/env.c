#include <string.h>
#include <stdlib.h>

#include "env.h"

char* env__find(char** env, char* name) {
  int i = 0;
  char* pair;
  unsigned int name_length = strlen(name);

  while ((pair = env[i++]) != NULL) {
    if (strncmp(name, pair, name_length) == 0) {
      return pair;
    }
  }

  return NULL;
}

char* env_get(char** env, char* name) {
  char* pair;
  char* result;
  unsigned int name_length, value_length;

  name_length = strlen(name);
  pair = env__find(env, name);

  if (pair == NULL)
    return NULL;

  value_length = strlen(pair) - name_length; // -1 for `=` and +1 for \0
  result = malloc(value_length);
  strncpy(result, pair + name_length + 1, value_length);
  return result;
}
