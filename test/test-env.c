#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <env.h>

int main(int argc, char** argv) {
  char** env = malloc(2 * sizeof(char*));

  env[0] = "NAME=value";
  env[1] = NULL;

  assert(env_length(env) == 1);

  assert(strcmp(env_get(env, "NAME"), "value") == 0);
  assert(env_get(env, "NOT_FOUND") == NULL);

  env_set(&env, "NAME", "set value");
  assert(strcmp(env[0], "NAME=set value") == 0);
  assert(strcmp(env_get(env, "NAME"), "set value") == 0);
  assert(env_length(env) == 1);

  env_set(&env, "NEW_NAME", "new value");
  assert(strcmp(env[0], "NAME=set value") == 0);
  assert(strcmp(env[1], "NEW_NAME=new value") == 0);
  assert(strcmp(env_get(env, "NAME"), "set value") == 0);
  assert(strcmp(env_get(env, "NEW_NAME"), "new value") == 0);
  assert(env_length(env) == 2);

  return 0;
}
