#include <string.h>
#include <stdlib.h>

#include "env.h"

int env__find(char** env, char* name) {
  int i = 0;
  char* pair;
  unsigned int name_length = strlen(name);

  while ((pair = env[i++]) != NULL) {
    if (strncmp(name, pair, name_length) == 0) {
      return i - 1;
    }
  }

  return -1;
}

unsigned int env_length(char** env) {
  unsigned int i = 0;
  while (env[i++] != NULL);
  return i - 1;
}

char* env_get(char** env, char* name) {
  int index;
  char* pair;
  char* result;
  unsigned int name_length, value_length;

  name_length = strlen(name);
  index = env__find(env, name);

  if ((index = env__find(env, name)) == -1)
    return NULL;

  pair = env[index];

  value_length = strlen(pair) - name_length; // -1 for `=` and +1 for \0
  result = malloc(value_length);
  strncpy(result, pair + name_length + 1, value_length);
  return result;
}

void env_set(char*** env, char* name, char* value) {
  int index;
  char* pair;
  unsigned int name_length, value_length, length;

  name_length = strlen(name);
  value_length = strlen(value);

  if ((index = env__find(*env, name)) == -1) {
    /*
     * No pair found. Add one. Reallocate memory assigned to env pairs to make
     * place for new environment variable.
     */
    length = env_length(*env);
    *env = realloc(*env, (length + 2) * sizeof(char*));

    pair = malloc(name_length + 1 + value_length + 1);
    strcat(pair, name);
    strcat(pair, "=");
    strcat(pair, value);

    (*env)[length] = pair;
    (*env)[length + 1] = NULL;
  }

  pair = malloc(name_length + 1 + value_length + 1);
  strcat(pair, name);
  strcat(pair, "=");
  strcat(pair, value);
  (*env)[index] = pair;
}
