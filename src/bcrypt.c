#include "bcrypt.h"

#include <stdio.h>
#include <crypt.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BCRYPT_HASH_LEN 64

/**
 * This function below checks if the hash provided by the user is a valid bcrypt hash
 */

bool is_valid_bcrypt_hash(const char *hash) {
    // Check for NULL and minimum length [59 chars total min]
    if (!hash || strlen(hash) < 59) return false;

    // Check prefix $2a$ or $2b$ or $2x$ or $2y$
    if (strncmp(hash, "$2a$", 4) != 0 &&
        strncmp(hash, "$2b$", 4) != 0 &&
        strncmp(hash, "$2x$", 4) != 0 &&
        strncmp(hash, "$2y$", 4) != 0) {
        return false;
    }

    // Validate cost parameter (between 04 and 31)
    if (!isdigit(hash[4]) || !isdigit(hash[5]) || hash[6] != '$') {
        return false;
    }
    int cost = (hash[4] - '0') * 10 + (hash[5] - '0');
    if (cost < 4 || cost > 31) return false;

    // Check salt length (22 chars) and hash length (31 chars)
    size_t len = strlen(hash);
    if (len != 59) return false; // $2x$cc$[22 chars salt][31 chars hash]

    const char *valid_chars = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (size_t i = 7; i < len; i++) {
        if (!strchr(valid_chars, hash[i])) return false;
    }

    return true;
}

int bcrypt_crack_hash(const char *candidate, const char *hash, char *found_password) {
    // Validate inputs
    if (!candidate || !hash || !found_password) {
        fprintf(stderr, "bcrypt_crack_hash: NULL parameter(s)\n");
        return -1;
    }

    // Validate hash format
    if (!is_valid_bcrypt_hash(hash)) {
        fprintf(stderr, "bcrypt_crack_hash: Invalid bcrypt hash format\n");
        return -1;
    }

    // Try to crack
    char *computed = crypt(candidate, hash);
    if (!computed) {
        fprintf(stderr, "bcrypt_crack_hash: crypt() failed\n");
        return -1;
    }

    // Check for match
    if (strcmp(computed, hash) == 0) {
        strncpy(found_password, candidate, BCRYPT_HASH_LEN);
        return 1; // Found!
    }

    return 0; // No match
}

/**
 * Extract bcrypt cost factor from hash
 * Returns cost (4-31) or -1 on error
 */
int bcrypt_get_cost(const char *hash) {
    if (!hash || strlen(hash) < 7) return -1;
    
    // Cost is characters 4-5 in $2a$CC$...
    if (!isdigit(hash[4]) || !isdigit(hash[5])) return -1;
    
    int cost = (hash[4] - '0') * 10 + (hash[5] - '0');
    if (cost < 4 || cost > 31) return -1;
    
    return cost;
}

/**
 * Get a printable description of the bcrypt hash
 * Useful for showing hash details to user
 */
void bcrypt_describe_hash(const char *hash, char *desc, size_t desc_len) {
    if (!hash || !desc || desc_len < 32) {
        if (desc && desc_len > 0) desc[0] = '\0';
        return;
    }

    char version = (hash && strlen(hash) > 3) ? hash[2] : '?';
    int cost = bcrypt_get_cost(hash);

    snprintf(desc, desc_len,
        "bcrypt (2%c) with cost factor %d",
        version, cost);
}