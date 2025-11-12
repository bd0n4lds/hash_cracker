#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum{
   UNKNOWN_HASH = 0,
   HASH_MD5,
   HASH_SHA1,
   HASH_SHA256,
   HASH_SHA512,
   HASH_BCRYPT,
   HASH_ARGON2
} hash_type_t;

hash_type_t hash_type_from_string(const char *hash_type);
bool is_valid_hash(hash_type_t type, const char *hash);
int hash_compute_hex(hash_type_t type, const char *candidate, char *out_hex, size_t out_hex_len);
bool hash_verify(hash_type_t type, const char *candidate, const char *target_hash);

#endif