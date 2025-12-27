#ifndef WORDLIST_UTILS_H
#define WORDLIST_UTILS_H

  /*
  TODO List for wordlist.h:

  1. Data Structures:
    - Define wordlist_t struct in .c file:
      * FILE* handle
      * Internal buffer
      * Buffer size
      * Current position
      * Error state

  2. Public API Functions:
    - wordlist_open():
      * Opens file, returns opaque handle
      * NULL on error (set errno)
    
    - wordlist_next_to_buffer():
      * Fills provided buffer with next word
      * Returns false at EOF
      * Handles buffer overflow
    
    - wordlist_close():
      * Cleanup resources
      * NULL-safe

  3. Error Handling:
    - Add error codes enum
    - Add get_error() function
    - Document buffer size limits
  */

#include <stddef.h>
#include <stdbool.h>

typedef struct wordlist_t wordlist_t;

wordlist_t *wordlist_open(const char *wordlist_path);
bool wordlist_next_to_buffer(wordlist_t *handle, char *buffer, size_t buffer_len);
char **wordlist_load_all(const char *wordlist_path, size_t *out_count);
void wordlist_free_all(char **words, size_t word_count);
void wordlist_close(wordlist_t *handle);


#endif