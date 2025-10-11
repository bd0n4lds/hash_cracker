#include "wordlist.h"
#include "usage.h"

#include <stdio.h>
#include <string.h>

/*
TODO List for main.c:

1. Argument Parsing:
   - Switch to getopt_long() for robust parsing:
     * Long options: --hash, --hash-type, --wordlist, --help, --version
     * Short options: -h (hash), -w (wordlist), -t (type), -? (help)
     * Handle missing required args
   
2. Input Validation:
   - Validate hash format:
     * Check if file or direct hash
     * Verify hash string is valid hex
     * Confirm hash length matches type
   
   - Validate hash type:
     * Support MD5, SHA1, SHA256
     * Case-insensitive matching
     * Unknown type error
   
   - Check wordlist file:
     * File exists and readable
     * Not empty
     * Handle permission errors

3. Core Logic:
   - Initialize components:
     * Open wordlist
     * Setup hash validation
     * Configure thread pool
   
   - Wire up cracking flow:
     * Pass to cracker API
     * Handle found/not-found
     * Show progress
   
   - Cleanup resources:
     * Close files
     * Free memory
     * Join threads

4. User Interface:
   - Improve usage message:
     * Show supported hash types
     * Example commands
     * Version info
   
   - Add error messages:
     * Specific error cases
     * Suggest fixes
     * Return codes

5. Tests to Add:
   - Argument combinations
   - Invalid inputs
   - Resource cleanup
   - Exit codes
*/

void arg_validator(const char *argument);

int main(int argc, char *argv[]){

    if(argc == 1){
        perror("No arguments passed!\n");
        return 1;
    }

    const char *hash = NULL;
    const char *hash_type = NULL;
    const char *wordlist = NULL;
    const char *help = NULL;

    for(int i = 1; i < argc; i++){
        const char *arg = argv[i];

        arg_validator(arg);
        
        if(strncmp(arg, "--help", 6)){
            help = arg+6;
            return 1;
        } else if(strcmp(arg, "--help") == 0){
            usage_big_print();
        }

        if (strncmp(arg, "--hash-type", 11) == 0) {
            hash_type = arg + 11;
            continue;
        } else if (strcmp(arg, "--hash-type") == 0 || strcmp(arg, "-m") == 0) {
            if (i + 1 < argc) hash_type = argv[++i];
            continue;
        }

        if (strncmp(arg, "--hash", 6) == 0) {
            hash = arg + 6;
            continue;
        } else if (strcmp(arg, "--hash") == 0 || strcmp(arg, "-h") == 0) {
            if (i + 1 < argc) hash = argv[++i];
            continue;
        }

        if (strncmp(arg, "--wordlist", 10) == 0) {
            wordlist = arg + 10;
            continue;
        } else if (strcmp(arg, "--wordlist") == 0 || strcmp(arg, "-w") == 0) {
            if (i + 1 < argc) wordlist = argv[++i];
            continue;
        }

    }

    printf("Hash Type: %s \t Hash: %s \t Wordlist: %s \n", hash_type, hash, wordlist);

    return 0;
    
}

void arg_validator(const char *argument){

    if(
        strcmp(argument, "--help") != 0 ||
        strcmp(argument, "--hash-type") != 0 || strcmp(argument, "-m") != 0 || 
        strcmp(argument, "--hash") != 0 || strcmp(argument, "-h") != 0 || 
        strcmp(argument, "--wordlist") != 0 || strcmp(argument, "-w") != 0
      )
      {
        
      fprintf(stderr, "Argument: '%s' is invalid!\n", argument);
      printf("For more help use flag: --help\n");
      return;

    }
}