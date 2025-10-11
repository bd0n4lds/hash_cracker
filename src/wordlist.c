#include "wordlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct wordlist_t {
  FILE *file_ptr;
  size_t current_line;
};

wordlist_t *wordlist_open(const char *wordlist_path){

  if(wordlist_path == NULL){
    errno = EINVAL;
    return NULL;
  }
  FILE *wordlist_file = fopen(wordlist_path, "r");
  if(wordlist_file == NULL) return NULL;
  
  wordlist_t *handle = malloc(sizeof *handle);
  if(handle == NULL){
    fprintf(stderr, "Memory allocation failed!\n");
    fclose(wordlist_file);
    return NULL;
  }

  handle->file_ptr = wordlist_file;
  handle->current_line = 0;
  return handle;
}

bool wordlist_next_to_buffer(wordlist_t *handle, char *buffer, size_t buffer_len){
  if (!handle || !buffer || buffer_len == 0) return false;
  
  char *res = fgets(buffer, (int)buffer_len, handle->file_ptr);
  if(!res) return false; // EOF or error
  handle->current_line++;

  size_t len = strlen(buffer); // Stripping new line 
  while(len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r')){
    buffer[--len] = '\0';
  }

  return true;

}

void wordlist_close(wordlist_t *handle){
  if(handle == NULL) return;
  if(handle->file_ptr) fclose(handle->file_ptr);
  free(handle);
}
