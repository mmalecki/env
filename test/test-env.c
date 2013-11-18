#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <env.h>

extern char** environ;

int main(int argc, char** argv) {
  int i;
  char** env = malloc(2 * sizeof(char*));
  char** env_copy_ = NULL;
  char** environ_copy = NULL;
  char** keys;

  env[0] = "NAME=value";
  env[1] = NULL;

  assert(env_length(env) == 1);

  assert(strcmp(env_get(env, "NAME"), "value") == 0);
  assert(env_get(env, "NOT_FOUND") == NULL);

  env = env_set(env, "NAME", "set value");
  assert(strcmp(env[0], "NAME=set value") == 0);
  assert(strcmp(env_get(env, "NAME"), "set value") == 0);
  assert(env_length(env) == 1);

  env = env_set(env, "NEW_NAME", "new value");
  assert(strcmp(env[0], "NAME=set value") == 0);
  assert(strcmp(env[1], "NEW_NAME=new value") == 0);
  assert(strcmp(env_get(env, "NAME"), "set value") == 0);
  assert(strcmp(env_get(env, "NEW_NAME"), "new value") == 0);
  assert(env_length(env) == 2);

  keys = env_keys(env);
  assert(strcmp(keys[0], "NAME") == 0);
  assert(strcmp(keys[1], "NEW_NAME") == 0);
  assert(keys[2] == NULL);
  free(keys);

  assert(env_copy_ = env_copy(env, env_copy_));
  assert(env_length(env) == env_length(env_copy_));
  for (i = 0; i < env_length(env); i++) {
    assert(env[i] != env_copy_[i]);
    assert(strcmp(env[i], env_copy_[i]) == 0);
  }

  // We should be able to copy `environ` and free it.
  environ_copy = env_copy(environ, environ_copy);
  env_free(environ_copy);

  env_free(env);
  env_free(env_copy_);

  return 0;
}
