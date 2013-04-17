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

void env__cat(char* dest, char* name, char* value) {
  strcat(dest, name);
  strcat(dest, "=");
  strcat(dest, value);
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

  if ((index = env__find(env, name)) == -1)
    return NULL;

  pair = env[index];

  value_length = strlen(pair) - name_length; // -1 for `=` and +1 for \0
  result = malloc(value_length);
  strncpy(result, pair + name_length + 1, value_length);
  return result;
}

char** env_set(char** env, char* name, char* value) {
  int index;
  char* pair;
  unsigned int name_length, value_length, length;

  name_length = strlen(name);
  value_length = strlen(value);

  if ((index = env__find(env, name)) == -1) {
    /*
     * No pair found. Add one. Reallocate memory assigned to env pairs to make
     * place for new environment variable.
     */
    length = env_length(env);
    env = realloc(env, (length + 2) * sizeof(char*));

    pair = malloc(name_length + 1 + value_length + 1);
    env__cat(pair, name, value);

    env[length] = pair;
    env[length + 1] = NULL;

    return env;
  }

  /*
   * This leaks. There's no way to free `(*env)[index]` because we can't tell
   * if it was allocated or put on heap.
   */
  pair = malloc(name_length + 1 + value_length + 1);
  env__cat(pair, name, value);
  env[index] = pair;

  return env;
}

char** env_keys(char** env) {
  int i, index, length;
  char* name;
  char** result;

  length = env_length(env);

  result = malloc((length + 1) * sizeof(char*));
  for (i = 0; i < length; i++) {
    index = strchr(env[i], '=') - env[i];
    if (index > 0) {
      name = malloc(index + 1);
      strncpy(name, env[i], index);
      result[i] = name;
    }
  }
  result[length] = NULL;

  return result;
}

char** env_copy(char** source, char** dest) {
  int i;
  int length = env_length(source);
  int var_length;

  if (dest == NULL) {
    dest = malloc((length + 1) * sizeof(char*));
  }

  for (i = 0; i < length; i++) {
    var_length = strlen(source[i]);
    dest[i] = malloc(var_length + 1);

    if (dest[i] == NULL) {
      return NULL;
    }

    dest[i] = strncpy(dest[i], source[i], var_length);
    dest[i][var_length] = '\0';
  }

  dest[length] = NULL;

  return dest;
}
