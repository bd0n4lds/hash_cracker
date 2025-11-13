#include "wordlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

struct wordlist_t {
  FILE *file_ptr;
  size_t current_line;
};

wordlist_t *wordlist_open(const char *wordlist_path){

  if(wordlist_path == NULL){
    errno = EINVAL;
    return NULL;
  }

  //Check if the file exists in the directory and if it is a regular file
  struct stat st;
  if(stat(wordlist_path, &st) != 0){
    perror(wordlist_path);
    return NULL;
  }

  if(!S_ISREG(st.st_mode)){
    fprintf(stderr, "Error: '%s' is not a regular file\n", wordlist_path);
    errno = EINVAL;
    return NULL;
  }
  
  // Check if the file is empty
  if (st.st_size == 0){
    fprintf(stderr, "Error: Wordlist '%s' is empty\n", wordlist_path);
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


// Load the entire wordlist into memory
char **wordlist_load_all(const char *wordlist_path, size_t *out_count){
  
  if(!wordlist_path || !out_count){
    return NULL;
  }

  FILE *fp = fopen(wordlist_path, "r");
  if(!fp){
    perror("Failed to open wordlist!\n");
    return NULL;
  }

  size_t line_count = 0;
  char buffer[256];
  while(fgets(buffer, sizeof(buffer), fp)) {
    line_count++;
  }

  if (line_count == 0) {
    fclose(fp);
    *out_count = 0;
    return NULL;
  }

  printf("\nLoading %zu passwords into memory\n", line_count);
  rewind(fp);

  // Allocating array of string pointers
  char **words = malloc(line_count * sizeof(char*));
  if(!words){
    fprintf(stderr, "Memory allocation failed for wordlist!\n");
    fclose(fp);
    return NULL;
  }

  // Reading all words

  size_t i = 0;
  while(fgets(buffer, sizeof(buffer), fp) && i < line_count) {

    // Strip the new lines
    size_t len = strlen(buffer);
    while(len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r')){
      buffer[--len] = '\0'; 
    }

    // Skipping empty lines
    if (len == 0) continue;

    words[i] = strdup(buffer);
    if(!words[i]){
      fprintf(stderr, "Memory allocation failed at line %zu\n", i);

      for(size_t j = 0; j < i; j++){
        free(words[j]);
      }
      free(words);
      fclose(fp);
      return NULL;
    }

    i++;
  }

  fclose(fp);
  *out_count = i;
  printf("Loaded %zu passwords successfully\n", i);
  return words;

}

void wordlist_free_all(char **words, size_t count){
  if(!words){
    return;
  }

  for(size_t i = 0; i < count; i++){
    free(words[i]);
  }
  free(words);
}
