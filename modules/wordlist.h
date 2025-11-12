#ifndef WORDLIST_UTILS_H
#define WORDLIST_UTILS_H


#include <stddef.h>
#include <stdbool.h>

typedef struct wordlist_t wordlist_t;

wordlist_t *wordlist_open(const char *wordlist_path);
bool wordlist_next_to_buffer(wordlist_t *handle, char *buffer, size_t buffer_len);
void wordlist_close(wordlist_t *handle);
char **wordlist_load_all(const char *wordlist_path, size_t *out_count);
void wordlist_free_all(char **words, size_t count);

#endif