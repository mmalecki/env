#ifndef ENV_H
#define ENV_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Gets environment variable called `name` from list of env pairs `env`.
 */
char* env_get(char** env, char* name);

#ifdef __cplusplus
}
#endif

#endif
