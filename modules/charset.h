#ifndef CHARSET_H
#define CHARSET_H

#include <stdbool.h>
#include <stddef.h>

/*
TODO List for charset.h:
1. Define charset_t struct to hold:
   - Character set string (e.g., "abcdefg123")
   - Current length
   - Min/max length bounds
   - State for resume support

2. Declare public API functions:
   - charset_new(const char *chars, size_t min_len, size_t max_len)
   - charset_next(charset_t *handle, char *buffer, size_t buflen)
   - charset_reset(charset_t *handle)
   - charset_free(charset_t *handle)
   - charset_get_state(charset_t *handle, void *state, size_t *statelen)
   - charset_set_state(charset_t *handle, const void *state, size_t statelen)

3. Add error codes enum:
   - CHARSET_OK
   - CHARSET_ERROR
   - CHARSET_INVALID_PARAM
   - CHARSET_EXHAUSTED
*/

typedef struct charset charset;


#endif
