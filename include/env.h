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

/*
 * Gets all keys from env pairs.
 */
char** env_keys(char** env);

/*
 * Copies `source` environment to `dest` environment (full byte copy).
 * If `dest` is `NULL`, it'll be allocated.
 * Returns `dest`.
 */
char** env_copy(char** source, char** dest);

#ifdef __cplusplus
}
#endif

#endif
