#include "wordlist.h"
#include "usage.h"
#include "attack.h"
#include "hash_utils.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdbool.h>


static char* read_hash_from_file(const char *filepath);
static bool looks_like_file_path(const char *str);

int main(int argc, char *argv[]){
    
    if(argc == 1){
        usage_big_print();
        return 0;
    }

    const char *hash_input = NULL;
    const char *hash_type_str = NULL;
    const char *wordlist = NULL;
    int attack_mode = 0;
    int num_threads = 4;

    //ARGUMENT PARSING
    
    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];

        if (strcmp(arg, "--help") == 0 || strcmp(arg, "-help") == 0 || strcmp(arg, "-h") == 0) {
            usage_big_print();
            return 0;
        }

        if (strcmp(arg, "--types") == 0) {
            usage_big_hashmodes();
            return 0;
        }

        if (arg[0] == '-') {

            // Hash type
            if (strncmp(arg, "--hash-type=", 12) == 0) {
                hash_type_str = arg + 12;
                continue;
            } else if (strcmp(arg, "--hash-type") == 0 || strcmp(arg, "-m") == 0) {
                if (i + 1 < argc) {
                    hash_type_str = argv[++i];
                    continue;
                } else {
                    fprintf(stderr, "Error: %s requires a value\n", arg);
                    return 1;
                }
            }

            // Hash file path (/path/to/hash.txt)
            if (strncmp(arg, "--hash=", 7) == 0) {
                hash_input = arg + 7;
                continue;
            } else if (strcmp(arg, "--hash") == 0 || strcmp(arg, "-H") == 0) {
                if (i + 1 < argc) {
                    hash_input = argv[++i];
                    continue;
                } else {
                    fprintf(stderr, "Error: %s requires a value\n", arg);
                    return 1;
                }
            }

            // Wordlist path (/path/to/wordlist.txt)
            if (strncmp(arg, "--wordlist=", 11) == 0) {
                wordlist = arg + 11;
                continue;
            } else if (strcmp(arg, "--wordlist") == 0 || strcmp(arg, "-w") == 0) {
                if (i + 1 < argc) {
                    wordlist = argv[++i];
                    continue;
                } else {
                    fprintf(stderr, "Error: %s requires a value\n", arg);
                    return 1;
                }
            }

            // Attack mode
            if (strncmp(arg, "--mode=", 7) == 0) {
                attack_mode = atoi(arg + 7);
                continue;
            } else if (strcmp(arg, "--mode") == 0 || strcmp(arg, "-a") == 0) {
                if (i + 1 < argc) {
                    attack_mode = atoi(argv[++i]);
                    continue;
                } else {
                    fprintf(stderr, "Error: %s requires a value\n", arg);
                    return 1;
                }
            }

            // Threads
            if (strncmp(arg, "--threads=", 10) == 0) {
                num_threads = atoi(arg + 10);
                continue;
            } else if (strcmp(arg, "--threads") == 0 || strcmp(arg, "-t") == 0) {
                if (i + 1 < argc) {
                    num_threads = atoi(argv[++i]);
                    continue;
                } else {
                    fprintf(stderr, "Error: %s requires a value\n", arg);
                    return 1;
                }
            }

            fprintf(stderr, "Error: Unknown option '%s'\n", arg);
            usage_mini_print();
            return 1;
        } else {
            fprintf(stderr, "Error: Unexpected positional argument '%s'\n", arg);
            usage_mini_print();
            return 1;
        }
    }

    // ARGUMENT VALIDATION
    
    if (!hash_input) {
        fprintf(stderr, "Error: --hash/-H is required\n");
        usage_mini_print();
        return 1;
    }
    
    if (!hash_type_str) {
        fprintf(stderr, "Error: --hash-type/-m is required\n");
        usage_mini_print();
        return 1;
    }
    
    if (!wordlist) {
        fprintf(stderr, "Error: --wordlist/-w is required\n");
        usage_mini_print();
        return 1;
    }

    // Parse hash type using hash_utils
    hash_type_t hash_type = hash_type_from_string(hash_type_str);
    if (hash_type == UNKNOWN_HASH) {
        return 1;
    }

    // Handle hash from file or direct input
    const char *hash_value = NULL;
    if (looks_like_file_path(hash_input)) {
        hash_value = read_hash_from_file(hash_input);
        if (!hash_value) {
            fprintf(stderr, "Error: Failed to read hash from file '%s'\n", hash_input);
            return 1;
        }
        printf("Loaded hash from file: %s\n", hash_input);
    } else {
        hash_value = hash_input;
    }

    // Validate hash format using hash_utils
    if (!is_valid_hash(hash_type, hash_value)) {
        fprintf(stderr, "Error: Invalid hash format\n");
        return 1;
    }

    // Validate thread count
    if (num_threads < 1) {
        fprintf(stderr, "Warning: Invalid thread count %d, using 1 thread\n", num_threads);
        num_threads = 1;
    } else if (num_threads > 16) {
        fprintf(stderr, "Warning: Thread count %d too high, limiting to 16\n", num_threads);
        num_threads = 16;
    }

    // Validate the attack mode
    if (attack_mode != 0 && attack_mode != 1) {
        fprintf(stderr, "Error: Invalid attack mode %d (0=dictionary, 1=bruteforce)\n", attack_mode);
        return 1;
    }

    // DISPLAY CONFIG
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║              Hash Cracker - Attack Starting                ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Configuration:\n");
    printf("  Hash Type  : %s\n", hash_type_str);
    printf("  Target Hash: %s\n", hash_value);
    printf("  Wordlist   : %s\n", wordlist);
    printf("  Attack Mode: %s\n", attack_mode == 0 ? "Dictionary" : "Bruteforce");
    printf("  Threads    : %d\n", num_threads);
    printf("\n");

    // HASH CRACKER
    
    if (attack_mode == 0) {
        wordlist_attack_mt(wordlist, hash_value, hash_type, num_threads);
    } else {
        fprintf(stderr, "Error: Bruteforce mode not yet implemented\n");
        return 1;
    }

    return 0;
}


static char* read_hash_from_file(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        perror(filepath);
        return NULL;
    }
    
    static char hash_buffer[256];
    if (!fgets(hash_buffer, sizeof(hash_buffer), fp)) {
        fclose(fp);
        fprintf(stderr, "Error: Failed to read from file '%s'\n", filepath);
        return NULL;
    }
    
    // Strip newline/whitespace
    size_t len = strlen(hash_buffer);
    while (len > 0 && (hash_buffer[len-1] == '\n' || hash_buffer[len-1] == '\r' || hash_buffer[len-1] == ' ' || hash_buffer[len-1] == '\t')) {
        hash_buffer[--len] = '\0';
    }
    
    fclose(fp);
    return hash_buffer;
}

// Check if string looks like a file path
static bool looks_like_file_path(const char *str) {
    if (!str) return false;
    
    // Check for path separators or file extensions
    if (strchr(str, '/') || strchr(str, '\\')) return true;
    
    size_t len = strlen(str);
    if (len > 4) {
        const char *ext = str + len - 4;
        if (strcmp(ext, ".txt") == 0 || strcmp(ext, ".dat") == 0 ||
            strcmp(ext, ".hash") == 0) return true;
    }
    
    // Check if file exists
    struct stat st;
    if (stat(str, &st) == 0 && S_ISREG(st.st_mode)) return true;
    
    return false;
}
