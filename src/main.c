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

#include "wordlist.h"
#include "usage.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
    
    if(argc == 1){
        errno = EINVAL;
        perror("No arguments passed!\n");
        return 1;
    }

    const char *hash = NULL;
    const char *hash_type = NULL;
    const char *wordlist = NULL;
    const char *help = NULL;

    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];

        if (strcmp(arg, "--help") == 0 || strcmp(arg, "-help") == 0 || strcmp(arg, "-h") == 0) {
            usage_big_print();
            return 1;
        }

        /* only treat flags starting with '-' as options */
        if (arg[0] == '-') {

            if (strncmp(arg, "--hash-type=", 12) == 0) {
                hash_type = arg + 12;
                continue;
            } else if (strcmp(arg, "--hash-type") == 0 || strcmp(arg, "-m") == 0) {
                if (i + 1 < argc) {
                    hash_type = argv[++i];
                    continue;
                } else {
                    fprintf(stderr, "Option %s requires a value\n", arg);
                    return 1;
                }
            }

            if (strncmp(arg, "--hash=", 7) == 0) {
                hash = arg + 7;
                continue;
            } else if (strcmp(arg, "--hash") == 0 || strcmp(arg, "-H") == 0) {
                if (i + 1 < argc) {
                    hash = argv[++i];
                    continue;
                } else {
                    fprintf(stderr, "Option %s requires a value\n", arg);
                    return 1;
                }
            }

            /* --wordlist=VALUE */
            if (strncmp(arg, "--wordlist=", 11) == 0) {
                wordlist = arg + 11;
                continue;
            } else if (strcmp(arg, "--wordlist") == 0 || strcmp(arg, "-w") == 0) {
                if (i + 1 < argc) {
                    wordlist = argv[++i];
                    continue;
                } else {
                    fprintf(stderr, "Option %s requires a value\n", arg);
                    return 1;
                }
            }

            /* unknown option*/
            fprintf(stderr, "Invalid flag: %s\n", arg);
            usage_mini_print();
            return 1;
        } else {
            /* this is a positional argument (not expected in current design);
                handle or ignore as needed */
            fprintf(stderr, "Unexpected positional argument: %s\n", arg);
            usage_mini_print();
            return 1;
        }
    }

    return 0;

}