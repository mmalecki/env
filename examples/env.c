#include <stdio.h>

#include <env.h>

extern char** environ;

int main() {
  int i = 0;
  char* key;
  char** keys = env_keys(environ);

  while ((key = keys[i++]) != NULL) {
    printf("%s=%s\n", key, env_get(environ, key));
  }

  return 0;
}
