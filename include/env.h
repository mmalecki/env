#ifndef ENV_H
#define ENV_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Gets environment variable called `name` from list of env pairs `env`.
 */
char* env_get(char** env, char* name);

/*
 * Gets number of env pairs from `env`.
 */
unsigned int env_length(char** env);

/*
 * Sets environment variable called `name` to value `value` in list of env
 * pairs `env`.
 * Please note that this needs pointer to `env`, as reallocation might be
 * needed.
 */
void env_set(char*** env, char* name, char* value);

#ifdef __cplusplus
}
#endif

#endif
