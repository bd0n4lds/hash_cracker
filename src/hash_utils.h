#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define MD5_HEX_LENGTH 32
#define SHA1_HEX_LENGTH 40
#define SHA256_HEX_LENGTH 64
#define SHA512_HEX_LENGTH 128

typedef enum{
   UNKNOWN_HASH = 0,
   HASH_MD5,
   HASH_SHA1,
   HASH_SHA256,
   HASH_SHA512,
   HASH_BCRYPT,
   HASH_ARGON2
} hash_type_t;

hash_type_t hash_type_from_string(const char *hash_type); // converts the user given strings into "md5"; "sha1"; "sha256"; etc
size_t get_hash_length(hash_type_t mode); // gets hash length for md5, sha1, sha256, sha512 since they have fixed hex lengths  


#endif // HASH_UTILS_H

/*
TODO List for hash_utils.h:

1. Hash Types:
   - Define hash_type_t enum:
     * MD5
     * SHA1
     * SHA256
     * Add others as needed

2. Public API:
   - compute_hash(input, type) -> hash string
   - compare_hash(candidate, target, type) -> bool
   - is_valid_hash(string, type) -> bool
   - get_hash_length(type) -> size_t
   - hash_type_from_string(name) -> hash_type_t

3. Error Handling:
   - Define error codes
   - Add get_error_string helper
*/
