#ifndef BCRYPT_CRACKER_H
#define BCRYPT_CRACKER_H

#include <stdbool.h>

/*
    $2a$12$R9h/cIPz0gi.URNNX3kh2OPST9/PgBkqquzi.Ss7KIUgO2t0jWMUW
    \__/\/ \____________________/\_____________________________/
    Alg Cost      Salt                        Hash
 */

/* Bcrypt struct for holding password candidate and hash */
typedef struct {
    char candidate[128];
    char hash[128];
} bcrypt;

bool is_valid_bcrypt_hash(const char *hash);

/**
    Hash a password using bcrypt with given settings
    @param password The password to hash
    @param settings A complete bcrypt hash string ($2x$nn$[22 chars salt][31 chars hash])
                    that provides the version, cost, and salt to use
    @return The computed hash or NULL on error
 */
char *bcrypt_hash_password(const char *candidate, const char *hash);

/*
    Verify if a password matches a bcrypt hash
    Returns true if match, false otherwise
 */
bool bcrypt_verify(const char *hashed_candidate, const char *hash);

/*
    Try to crack a bcrypt hash with a candidate password
    Returns the matching character if found, 0 otherwise
 */
char bcrypt_cracking(const char *candidate, const char *hash);

#endif