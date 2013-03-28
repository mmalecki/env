#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <env.h>

int main(int argc, char** argv) {
  char** env = malloc(2 * sizeof(char*));
  char* result;

  env[0] = "NAME=value";
  env[1] = NULL;

  result = env_get(env, "NAME");
  printf("NAME=%s\n", result);
  assert(strcmp(result, "value") == 0);

  return 0;
}
